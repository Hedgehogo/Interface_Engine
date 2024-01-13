#include "BoxShader.hpp"

namespace ie {
	BoxShader::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		sf::Shader* shader,
		size_t transmission,
		SMakeMap<ISFloat> values_f,
		SMakeMap<ISInt> values_i,
		SMakeMap<ISBool> values_b,
		SMakeMap<ISValue<sf::Color> > values_c,
		SMakeMap<SRVec2F> values_v,
		bool optimize,
		sf::Vector2f min_size
	) :
		BoxRenderTexture::Make(std::move(object), optimize, min_size),
		shader(shader),
		transmission(transmission),
		values_f(std::move(values_f)),
		values_i(std::move(values_i)),
		values_b(std::move(values_b)),
		values_c(std::move(values_c)),
		values_v(std::move(values_v)) {
	}
	
	BoxShader* BoxShader::Make::make(InitInfo init_info) {
		return new BoxShader{std::move(*this), init_info};
	}
	
	template<typename T>
	BoxShader::SReaderVec<T> make_reader_map(BoxShader::SMakeMap<T>&& map, DynBuffer& dyn_buffer, BoxShader& box_shader) {
		BoxShader::SReaderVec<T> reader_map{};
		reader_map.reserve(map.size());
		for(auto& [key, make]: map) {
			reader_map.emplace_back(
				SReader<T>{
					make.make(dyn_buffer),
					[key = std::move(key), &box_shader](auto const& value) {
						box_shader.set_uniform(key, value);
					}
				}
			);
		}
		return reader_map;
	}
	
	BoxShader::BoxShader(Make&& make, InitInfo init_info) :
		BoxRenderTexture(std::move(make.object), make.optimize, make.min_size, init_info),
		shader_(make.shader),
		transmission_(make.transmission),
		values_f_(make_reader_map(std::move(make.values_f), init_info.dyn_buffer, *this)),
		values_i_(make_reader_map(std::move(make.values_i), init_info.dyn_buffer, *this)),
		values_b_(make_reader_map(std::move(make.values_b), init_info.dyn_buffer, *this)),
		values_c_(make_reader_map(std::move(make.values_c), init_info.dyn_buffer, *this)),
		values_v_(make_reader_map(std::move(make.values_v), init_info.dyn_buffer, *this)) {
	}
	
	BoxShader::~BoxShader() {
		delete shader_;
	}
	
	void BoxShader::set_uniform(std::string const& name, float var) {
		shader_->setUniform(name, var);
	}
	
	void BoxShader::set_uniform(std::string const& name, int var) {
		shader_->setUniform(name, var);
	}
	
	void BoxShader::set_uniform(std::string const& name, bool var) {
		shader_->setUniform(name, var);
	}
	
	void BoxShader::set_uniform(std::string const& name, sf::Color var) {
		shader_->setUniform(name, sf::Glsl::Vec4{var});
	}
	
	void BoxShader::set_uniform(std::string const& name, sf::Vector2f var) {
		shader_->setUniform(name, var);
	}
	
	void BoxShader::set_size(sf::Vector2f size) {
		if(transmission_ & Transmission::Size)
			shader_->setUniform("size", size);
		if(transmission_ & Transmission::AspectRatio)
			shader_->setUniform("aspect_ratio", size.x / size.y);
		layout_.set_size(size);
	}
	
	void BoxShader::draw() {
		if(!optimize_ || active_ || interaction_manager_->is_blocked()) {
			render_texture_.clear(sf::Color(0, 0, 0, 0));
			draw_manager_.draw();
			render_texture_.display();
			sprite_.setTexture(render_texture_.getTexture());
			active_ = false;
		}
		if(transmission_ & Transmission::Time)
			shader_->setUniform("time", clock_.getElapsedTime().asSeconds());
		if(transmission_ & Transmission::Texture)
			shader_->setUniform("texture", render_texture_.getTexture());
		render_target_->draw(sprite_, shader_);
	}
	
	void BoxShader::resize(sf::Vector2f size, sf::Vector2f position) {
		if(transmission_ & Transmission::Size)
			shader_->setUniform("size", size);
		if(transmission_ & Transmission::AspectRatio)
			shader_->setUniform("aspect_ratio", size.x / size.y);
		BoxRenderTexture::resize(size, position);
	}
	
	bool BoxShader::update_interactions(sf::Vector2f mouse_position) {
		if(transmission_ & Transmission::MousePosition)
			shader_->setUniform("mouse_position", mouse_position - layout_.position);
		return BoxRenderTexture::update_interactions(mouse_position);
	}
	
	BoxShader* BoxShader::copy() {
		return new BoxShader{*this};
	}
	
	/*old_yaml_decode_pointer_impl
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
	*/
}

orl::Option<ie::BoxShader::LoadTransmission>
ieml::Decode<char, ie::BoxShader::LoadTransmission>::decode(const ieml::Node& node) {
	auto& clear_node{node.get_clear()};
	if(auto list{clear_node.get_list()}) {
		ie::BoxShader::Transmission result{ie::BoxShader::Transmission::None};
		for(auto& item: list.ok()) {
			auto item_result{item.as<ie::BoxShader::LoadTransmission>().except().transmission};
			result = static_cast<ie::BoxShader::Transmission>(result | item_result);
		}
		return {{result}};
	} else {
		auto& str{clear_node.get_string().except()};
		if(str == "size") {
			return {{ie::BoxShader::Transmission::Size}};
		} else if(str == "texture") {
			return {{ie::BoxShader::Transmission::Texture}};
		} else if(str == "aspect_ratio") {
			return {{ie::BoxShader::Transmission::AspectRatio}};
		} else if(str == "mouse_position") {
			return {{ie::BoxShader::Transmission::MousePosition}};
		} else if(str == "time") {
			return {{ie::BoxShader::Transmission::Time}};
		}
	}
	return {};
}
