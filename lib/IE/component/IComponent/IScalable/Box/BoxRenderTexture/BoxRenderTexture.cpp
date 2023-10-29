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
		sprite_(render_texture_.getTexture()),
		object_(object->make(init_info.copy(render_texture_).copy(draw_manager_))),
		interaction_manager_(&init_info.interaction_manager),
		render_target_(&init_info.render_target),
		optimize_(optimize),
		active_(true) {
		init_info.draw_manager.add(*this);
	}
	
	BoxRenderTexture::BoxRenderTexture(BoxPtr<IScalable>&& object, bool optimize, sf::Vector2f min_size) :
		Box(min_size), object_(std::move(object)), interaction_manager_(nullptr), render_target_(nullptr), optimize_(optimize), active_(true) {
		sprite_.setTexture(render_texture_.getTexture());
	}
	
	BoxRenderTexture::BoxRenderTexture(const BoxRenderTexture& other) :
		Box(other), object_(other.object_), render_target_(other.render_target_), optimize_(other.optimize_), active_(true) {
		sf::Vector2u size = this->render_texture_.getSize();
		render_texture_.create(size.x, size.y);
	}
	
	void BoxRenderTexture::init(InitInfo init_info) {
		this->render_target_ = &init_info.render_target;
		this->interaction_manager_ = &init_info.interaction_manager;
		init_info.draw_manager.add(*this);
		object_->init(init_info.copy(render_texture_).copy(this->draw_manager_));
	}
	
	void BoxRenderTexture::draw() {
		if(!optimize_ || active_ || interaction_manager_->is_blocked()) {
			render_texture_.clear(sf::Color(0, 0, 0, 0));
			draw_manager_.draw();
			render_texture_.display();
			active_ = false;
		}
		render_target_->draw(sprite_);
	}
	
	void BoxRenderTexture::resize(sf::Vector2f size, sf::Vector2f position) {
		IComponentObject::resize(size, position);
		sf::Vector2f start{std::floor(position.x), std::ceil(position.y)};
		sf::Vector2f end{std::floor(position.x + size.x), std::ceil(position.y + size.y)};
		sf::Vector2i texture_size{end - start};
		
		view_.reset({start, end - start});
		
		render_texture_.create(texture_size.x, texture_size.y);
		render_texture_.setView(view_);
		
		sprite_.setTexture(render_texture_.getTexture());
		sprite_.setTextureRect({{0, 0}, texture_size});
		sprite_.setPosition(start);
		
		active_ = true;
	}
	
	bool BoxRenderTexture::update_interactions(sf::Vector2f mouse_position) {
		active_ = true;
		return object_->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxRenderTexture::get_min_size() const {
		return max(object_->get_min_size(), minimum_size_, sf::Vector2f{1, 1});
	}
	
	sf::Vector2f BoxRenderTexture::get_normal_size() const {
		return max(object_->get_normal_size(), minimum_size_, sf::Vector2f{1, 1});
	}
	
	IScalable& BoxRenderTexture::get_object() {
		return *object_;
	}
	
	const IScalable& BoxRenderTexture::get_object() const {
		return *object_;
	}
	
	BoxRenderTexture* BoxRenderTexture::copy() {
		return new BoxRenderTexture{*this};
	}
	
	void BoxRenderTexture::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		object_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxRenderTexture>::decode_pointer(const YAML::Node& node, BoxRenderTexture*& box_with_render_texture) {
		box_with_render_texture = new BoxRenderTexture{
			node["object"].as<BoxPtr<IScalable> >(),
			conv_def(node["optimize"], true),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;

	}
	*/
}