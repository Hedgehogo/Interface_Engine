#include "BoxBackground.hpp"

namespace ie {
	BoxBackground::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, sf::Vector2f offset, sf::Vector2f min_size) :
		object(std::move(object)), background(std::move(background)), offset(offset), min_size(min_size) {
	}
	
	BoxBackground* BoxBackground::Make::make(InitInfo init_info) {
		return new BoxBackground{std::move(*this), init_info};
	}
	
	BoxBackground::BoxBackground(Make&& make, InitInfo init_info) :
		Box(make.min_size), background_(make.background->make(init_info)), object_(make.object->make(init_info)), offset_(make.offset) {
	}
	
	BoxBackground::BoxBackground(BoxPtr<IScalable>&& object, BoxPtr<IUninteractive>&& background, sf::Vector2f offset, sf::Vector2f min_size) :
		Box(min_size), background_(std::move(background)), object_(std::move(object)), offset_(offset) {
	}
	
	void BoxBackground::init(InitInfo init_info) {
		background_->init(init_info);
		object_->init(init_info);
	}
	
	void BoxBackground::set_position(sf::Vector2f position) {
		layout_.set_position(position);
		background_->set_position(position);
		object_->set_position(position);
	}
	
	void BoxBackground::move(sf::Vector2f position) {
		layout_.move(position);
		background_->move(position);
		object_->move(position);
	}
	
	void BoxBackground::set_size(sf::Vector2f size) {
		layout_.set_size(size);
		background_->set_size(size);
		object_->set_size(size);
	}
	
	sf::Vector2f BoxBackground::get_min_size() const {
		return max(object_->get_min_size() + offset_ * 2.f, background_->get_min_size(), minimum_size_);
	}
	
	sf::Vector2f BoxBackground::get_normal_size() const {
		return max(object_->get_normal_size() + offset_ * 2.f, background_->get_normal_size());
	}
	
	IUninteractive& BoxBackground::get_background() {
		return *background_;
	}
	
	const IUninteractive& BoxBackground::get_background() const {
		return *background_;
	}
	
	IScalable& BoxBackground::get_object() {
		return *object_;
	}
	
	const IScalable& BoxBackground::get_object() const {
		return *object_;
	}
	
	void BoxBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		background_->resize(size, position);
		object_->resize(size - offset_ * 2.f, position + offset_);
	}
	
	bool BoxBackground::update_interactions(sf::Vector2f mouse_position) {
		return object_->update_interactions(mouse_position);
	}
	
	BoxBackground* BoxBackground::copy() {
		return new BoxBackground{*this};
	}
	
	void BoxBackground::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxBackground>::decode_pointer(const YAML::Node& node, BoxBackground*& box_with_background) {
		box_with_background = new BoxBackground{
			node["object"].as<BoxPtr<IScalable> >(),
			node["background"].as<BoxPtr<IUninteractive> >(),
			conv_def(node["offset"], sf::Vector2f{}),
			conv_def(node["min-size"], sf::Vector2f{}),
		};
		return true;

	}
	*/
}