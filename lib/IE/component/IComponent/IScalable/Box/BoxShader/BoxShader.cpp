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
		} else if(str == "aspect-ratio") {
			return {{ie::BoxShader::Transmission::AspectRatio}};
		} else if(str == "mouse-position") {
			return {{ie::BoxShader::Transmission::MousePosition}};
		} else if(str == "time") {
			return {{ie::BoxShader::Transmission::Time}};
		}
	}
	return {};
}

orl::Option<ie::BoxShader::Make> ieml::Decode<char, ie::BoxShader::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	sf::Shader* shader{new sf::Shader{}};
	if(auto shader_node{map.at("shader")}) {
		shader_node.ok().as<ie::LoadShader>().except().load(*shader);
	}
	return ie::BoxShader::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		shader,
		map.at("transmission").except().as<ie::BoxShader::LoadTransmission>().except().transmission,
		map.at("values-f").except().as<ie::BoxShader::SMakeMap<ie::ISFloat> >().move_except(),
		map.at("values-i").except().as<ie::BoxShader::SMakeMap<ie::ISInt> >().move_except(),
		map.at("values-b").except().as<ie::BoxShader::SMakeMap<ie::ISBool> >().move_except(),
		map.at("values-c").except().as<ie::BoxShader::SMakeMap<ie::ISValue<sf::Color> > >().move_except(),
		map.at("values-v").except().as<ie::BoxShader::SMakeMap<ie::SRVec2F> >().move_except(),
		map.get_as<bool>("optimize").ok_or(true),
		map.get_as<sf::Vector2f>("min-size").ok_or({})
	};
}
