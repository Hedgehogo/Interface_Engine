#include "BoxShader.hpp"

namespace ie {
	uint convert_transmission_def(const YAML::Node& node) {
		uint transmission{};
		if(node) {
			std::map<std::string, BoxShader::Transmission> transmission_map{
				{"size",          BoxShader::Transmission::Size},
				{"texture",       BoxShader::Transmission::Texture},
				{"aspect_ratio",   BoxShader::Transmission::AspectRatio},
				{"mouse_position", BoxShader::Transmission::MousePosition},
				{"time",          BoxShader::Transmission::Time},
			};
			
			if(node.IsScalar()) {
				std::string str_transmission = node.as<std::string>();
				transmission = transmission_map[str_transmission];
			} else if(node.IsSequence()) {
				std::string str_transmission;
				for(const auto& item: node) {
					str_transmission = item.as<std::string>();
					transmission = static_cast<BoxShader::Transmission>(transmission | transmission_map[str_transmission]);
				}
			}
		}
		return transmission;
	}
	
	BoxShader::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		sf::Shader* shader,
		uint transmission,
		std::map<std::string, PISfloat> values_f,
		std::map<std::string, PISint> values_i,
		std::map<std::string, PISbool> values_b,
		std::map<std::string, PISValue<sf::Color>> values_c,
		std::map<std::string, PSRVec2f> values_v,
		bool optimize,
		sf::Vector2f min_size
	) :
		BoxRenderTexture::Make(std::move(object), optimize, min_size),
		shader(shader),
		transmission(transmission),
		values_f(values_f),
		values_i(values_i),
		values_b(values_b),
		values_c(values_c),
		values_v(values_v) {
	}
	
	BoxShader* BoxShader::Make::make(InitInfo init_info) {
		return new BoxShader{std::move(*this), init_info};
	}
	
	BoxShader::BoxShader(Make&& make, InitInfo init_info) :
		BoxRenderTexture(std::move(make.object), make.optimize, make.min_size, init_info),
		shader(make.shader),
		transmission(make.transmission) {
		auto add_setters = [&](auto& values) {
			for(auto& pair: values) {
				pair.second->add_setter([&](auto var) {
					set_uniform(pair.first, var);
				});
			}
		};
		
		add_setters(make.values_f);
		add_setters(make.values_i);
		add_setters(make.values_b);
		add_setters(make.values_c);
		add_setters(make.values_v);
	}
	
	BoxShader::BoxShader(
		BoxPtr<IScalable>&& object, sf::Shader* shader, uint transmission,
		std::map<std::string, PISfloat> values_f,
		std::map<std::string, PISint> values_i,
		std::map<std::string, PISbool> values_b,
		std::map<std::string, PISValue<sf::Color>> values_c,
		std::map<std::string, PSRVec2f> values_v,
		bool optimize, sf::Vector2f min_size
	) : BoxRenderTexture(std::move(object), optimize, min_size), shader(shader), transmission(transmission) {
		auto add_setters = [&](auto& values) {
			for(auto& pair: values) {
				pair.second->add_setter([&](auto var) {
					set_uniform(pair.first, var);
				});
			}
		};
		
		add_setters(values_f);
		add_setters(values_i);
		add_setters(values_b);
		add_setters(values_c);
		add_setters(values_v);
	}
	
	BoxShader::~BoxShader() {
		delete shader;
	}
	
	void BoxShader::set_uniform(std::string name, float var) {
		shader->setUniform(name, var);
	}
	
	void BoxShader::set_uniform(std::string name, int var) {
		shader->setUniform(name, var);
	}
	
	void BoxShader::set_uniform(std::string name, bool var) {
		shader->setUniform(name, var);
	}
	
	void BoxShader::set_uniform(std::string name, sf::Color var) {
		shader->setUniform(name, sf::Glsl::Vec4{var});
	}
	
	void BoxShader::set_uniform(std::string name, sf::Vector2f var) {
		shader->setUniform(name, var);
	}
	
	void BoxShader::set_size(sf::Vector2f size) {
		if(transmission & Transmission::Size)
			shader->setUniform("size", size);
		if(transmission & Transmission::AspectRatio)
			shader->setUniform("aspect_ratio", size.x / size.y);
		layout.set_size(size);
	}
	
	void BoxShader::draw() {
		if(!optimize || active || interaction_manager->is_blocked()) {
			render_texture.clear(sf::Color(0, 0, 0, 0));
			draw_manager.draw();
			render_texture.display();
			sprite.setTexture(render_texture.getTexture());
			active = false;
		}
		if(transmission & Transmission::Time)
			shader->setUniform("time", clock.getElapsedTime().asSeconds());
		if(transmission & Transmission::Texture)
			shader->setUniform("texture", render_texture.getTexture());
		render_target->draw(sprite, shader);
	}
	
	void BoxShader::resize(sf::Vector2f size, sf::Vector2f position) {
		if(transmission & Transmission::Size)
			shader->setUniform("size", size);
		if(transmission & Transmission::AspectRatio)
			shader->setUniform("aspect_ratio", size.x / size.y);
		BoxRenderTexture::resize(size, position);
	}
	
	bool BoxShader::update_interactions(sf::Vector2f mouse_position) {
		if(transmission & Transmission::MousePosition)
			shader->setUniform("mouse_position", mouse_position - layout.position);
		return BoxRenderTexture::update_interactions(mouse_position);
	}
	
	BoxShader* BoxShader::copy() {
		return new BoxShader{*this};
	}
	
	template<typename T>
	auto get_s_values_def(const YAML::Node& node) {
		std::map<std::string, std::shared_ptr<T> > result;
		if(node) {
			for(auto& pair: node) {
				result.insert(std::make_pair(pair.first.as<std::string>(), Buffer::get<T>(pair.second)));
			}
		}
		return result;
	}
	
	bool DecodePointer<BoxShader>::decode_pointer(const YAML::Node& node, BoxShader*& box_with_shader) {
		sf::Shader* shader{new sf::Shader{}};
		if(node["shader"]) {
			node["shader"] >> *shader;
		}
		box_with_shader = new BoxShader{
			node["object"].as < BoxPtr < IScalable > > (),
			shader,
			convert_transmission_def(node["transmission"]),
			get_s_values_def<ISfloat>(node["values-f"]),
			get_s_values_def<ISint>(node["values-i"]),
			get_s_values_def<ISbool>(node["values-b"]),
			get_s_values_def<ISValue<sf::Color> >(node["values-c"]),
			get_s_values_def<SRVec2f>(node["values-v"]),
			conv_def(node["optimize"], true),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}