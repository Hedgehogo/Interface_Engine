#include "BoxRenderTexture.hpp"

namespace ie {
	BoxRenderTexture::Make::Make(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f min_size) :
		object(std::move(object)), optimize(optimize), min_size(min_size) {
	}
	
	BoxRenderTexture* BoxRenderTexture::Make::make(InitInfo init_info) {
		return new BoxRenderTexture{std::move(*this), init_info};
	}
	
	BoxRenderTexture::BoxRenderTexture(Make&& make, InitInfo init_info) :
		BoxRenderTexture(std::move(make.object), make.optimize, make.min_size, init_info) {
	}
	
	BoxRenderTexture::BoxRenderTexture(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f min_size, InitInfo init_info) :
		Box(min_size),
		sprite(render_texture.getTexture()),
		object(object->make(init_info.copy(render_texture).copy(draw_manager))),
		interaction_manager(&init_info.interaction_manager),
		render_target(&init_info.render_target),
		optimize(optimize),
		active(true) {
		init_info.draw_manager.add(*this);
	}
	
	BoxRenderTexture::BoxRenderTexture(BoxPtr<IScalable>&& object, bool optimize, sf::Vector2f min_size) :
		Box(min_size), object(std::move(object)), interaction_manager(nullptr), render_target(nullptr), optimize(optimize), active(true) {
		sprite.setTexture(render_texture.getTexture());
	}
	
	BoxRenderTexture::BoxRenderTexture(const BoxRenderTexture& other) :
		Box(other), object(other.object), render_target(other.render_target), optimize(other.optimize), active(true) {
		sf::Vector2u size = this->render_texture.getSize();
		render_texture.create(size.x, size.y);
	}
	
	void BoxRenderTexture::init(InitInfo init_info) {
		this->render_target = &init_info.render_target;
		this->interaction_manager = &init_info.interaction_manager;
		init_info.draw_manager.add(*this);
		object->init(init_info.copy(render_texture).copy(this->draw_manager));
	}
	
	void BoxRenderTexture::draw() {
		if(!optimize || active || interaction_manager->is_blocked()) {
			render_texture.clear(sf::Color(0, 0, 0, 0));
			draw_manager.draw();
			render_texture.display();
			active = false;
		}
		render_target->draw(sprite);
	}
	
	void BoxRenderTexture::resize(sf::Vector2f size, sf::Vector2f position) {
		IComponentObject::resize(size, position);
		sf::Vector2f start{std::floor(position.x), std::ceil(position.y)};
		sf::Vector2f end{std::floor(position.x + size.x), std::ceil(position.y + size.y)};
		sf::Vector2i texture_size{end - start};
		
		view.reset({start, end - start});
		
		render_texture.create(texture_size.x, texture_size.y);
		render_texture.setView(view);
		
		sprite.setTexture(render_texture.getTexture());
		sprite.setTextureRect({{0, 0}, texture_size});
		sprite.setPosition(start);
		
		active = true;
	}
	
	bool BoxRenderTexture::update_interactions(sf::Vector2f mouse_position) {
		active = true;
		return object->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxRenderTexture::get_min_size() const {
		return max(object->get_min_size(), minimum_size, sf::Vector2f{1, 1});
	}
	
	sf::Vector2f BoxRenderTexture::get_normal_size() const {
		return max(object->get_normal_size(), minimum_size, sf::Vector2f{1, 1});
	}
	
	IScalable& BoxRenderTexture::get_object() {
		return *object;
	}
	
	const IScalable& BoxRenderTexture::get_object() const {
		return *object;
	}
	
	BoxRenderTexture* BoxRenderTexture::copy() {
		return new BoxRenderTexture{*this};
	}
	
	void BoxRenderTexture::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		object->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
	
	bool DecodePointer<BoxRenderTexture>::decode_pointer(const YAML::Node& node, BoxRenderTexture*& box_with_render_texture) {
		box_with_render_texture = new BoxRenderTexture{
			node["object"].as<BoxPtr<IScalable> >(),
			conv_def(node["optimize"], true),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}