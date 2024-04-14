#include "BoxShader.hpp"

namespace ie {
	BoxShader::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		sf::Shader* shader,
		size_t transmission,
		SMakeMap<ISFloat> values_f,
		SMakeMap<ISInt> values_i,
		SMakeMap<ISBool> values_b,
		SMakeMap<ISReadable<sf::Color> > values_c,
		SMakeMap<ISRVec2F> values_v,
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
	
	auto BoxShader::Make::make(InitInfo init_info) -> BoxShader* {
		return new BoxShader{std::move(*this), init_info};
	}
	
	template<typename T>
	auto make_reader_map(BoxShader::SMakeMap<T>&& map, SInitInfo init_info, BoxShader& box_shader) -> BoxShader::SReaderVec<T> {
		BoxShader::SReaderVec<T> reader_map{};
		reader_map.reserve(map.size());
		for(auto& [key, make]: map) {
			reader_map.emplace_back(
				SReader<T>{
					make.make(init_info),
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
		values_f_(make_reader_map(std::move(make.values_f), SInitInfo{init_info}, *this)),
		values_i_(make_reader_map(std::move(make.values_i), SInitInfo{init_info}, *this)),
		values_b_(make_reader_map(std::move(make.values_b), SInitInfo{init_info}, *this)),
		values_c_(make_reader_map(std::move(make.values_c), SInitInfo{init_info}, *this)),
		values_v_(make_reader_map(std::move(make.values_v), SInitInfo{init_info}, *this)) {
	}
	
	BoxShader::~BoxShader() {
		delete shader_;
	}
	
	auto BoxShader::set_uniform(std::string const& name, float var) -> void {
		shader_->setUniform(name, var);
	}
	
	auto BoxShader::set_uniform(std::string const& name, int var) -> void {
		shader_->setUniform(name, var);
	}
	
	auto BoxShader::set_uniform(std::string const& name, bool var) -> void {
		shader_->setUniform(name, var);
	}
	
	auto BoxShader::set_uniform(std::string const& name, sf::Color var) -> void {
		shader_->setUniform(name, sf::Glsl::Vec4{var});
	}
	
	auto BoxShader::set_uniform(std::string const& name, sf::Vector2f var) -> void {
		shader_->setUniform(name, var);
	}
	
	auto BoxShader::set_size(sf::Vector2f size) -> void {
		if(transmission_ & Transmission::Size)
			shader_->setUniform("size", size);
		if(transmission_ & Transmission::AspectRatio)
			shader_->setUniform("aspect_ratio", size.x / size.y);
		layout_.set_size(size);
	}
	
	auto BoxShader::draw() -> void {
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
	
	auto BoxShader::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		if(transmission_ & Transmission::Size)
			shader_->setUniform("size", size);
		if(transmission_ & Transmission::AspectRatio)
			shader_->setUniform("aspect_ratio", size.x / size.y);
		BoxRenderTexture::resize(size, position);
	}
	
	auto BoxShader::handle_event(Event event) -> bool {
		for(auto touch: event.touch()) {
			if(transmission_ & Transmission::MousePosition) {
				shader_->setUniform("mouse_position", sf::Vector2f{touch.position} - layout_.position);
			}
		}
		return BoxRenderTexture::handle_event(event);
	}
}

auto ieml::Decode<char, ie::BoxShader::LoadTransmission>::decode(const ieml::Node& node) -> orl::Option<ie::BoxShader::LoadTransmission> {
	auto& clear_node{node.get_clear()};
	for(auto& list: clear_node.get_list().ok_or_none()) {
		ie::BoxShader::Transmission result{ie::BoxShader::Transmission::None};
		for(auto& item: list) {
			auto item_result{item.as<ie::BoxShader::LoadTransmission>().except().transmission};
			result = static_cast<ie::BoxShader::Transmission>(result | item_result);
		}
		return {{result}};
	}
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
	return {};
}

auto ieml::Decode<char, ie::BoxShader::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxShader::Make> {
	auto map{node.get_map_view().except()};
	sf::Shader* shader{new sf::Shader{}};
	for(auto& shader_node: map.at("shader").ok_or_none()) {
		shader_node.as<ie::LoadShader>().except().load(*shader);
	}
	return ie::BoxShader::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		shader,
		map.at("transmission").except().as<ie::BoxShader::LoadTransmission>().except().transmission,
		map.at("values-f").except().as<ie::BoxShader::SMakeMap<ie::ISFloat> >().except(),
		map.at("values-i").except().as<ie::BoxShader::SMakeMap<ie::ISInt> >().except(),
		map.at("values-b").except().as<ie::BoxShader::SMakeMap<ie::ISBool> >().except(),
		map.at("values-c").except().as<ie::BoxShader::SMakeMap<ie::ISReadable<sf::Color> > >().except(),
		map.at("values-v").except().as<ie::BoxShader::SMakeMap<ie::ISRVec2F> >().except(),
		map.get_as<bool>("optimize").except().ok_or(true),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
