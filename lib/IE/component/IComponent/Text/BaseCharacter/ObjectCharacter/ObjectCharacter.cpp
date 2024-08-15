#include "ObjectCharacter.hpp"

namespace ie {
	ObjectCharacter::ObjectCharacter(BoxPtr<IScalable>&& object, ObjectSpecial special) :
		object_(std::move(object)), special_(static_cast<BaseCharacter::Special>(special)) {
	}
	
	ObjectCharacter::ObjectCharacter(const ObjectCharacter& other) : object_(nullptr), special_(other.special_) {
	}
	
	void ObjectCharacter::set_position(sf::Vector2f position) {
		position.y -= get_height();
		BaseCharacter::set_position(position);
		object_->set_position(position);
	}
	
	void ObjectCharacter::resize(sf::Vector2f position, float end_position) {
		position.y -= get_height();
		BaseCharacter::set_position(position);
		object_->resize(
			{
				is_special() == BaseCharacter::Special::FullLine ?
				end_position - position.x :
				object_->get_size().x, object_->get_size().y
			}, position
		);
	}
	
	void ObjectCharacter::move(sf::Vector2f offset) {
		BaseCharacter::move(offset);
		object_->move(offset);
	}
	
	bool ObjectCharacter::handle_event(Event event) {
		return object_->handle_event(event);
	}
	
	char32_t ObjectCharacter::get_char() {
		return '\0';
	}
	
	float ObjectCharacter::get_height() const {
		return object_->get_area_size().y;
	}
	
	float ObjectCharacter::get_advance() {
		return object_->get_area_size().x;
	}
	
	float ObjectCharacter::get_kerning(char32_t) {
		return 0;
	}
	
	BaseCharacter::Special ObjectCharacter::is_special() {
		return special_;
	}
	
	void ObjectCharacter::draw() {
	}
	
	void ObjectCharacter::draw_debug(sf::RenderTarget& render_target, int indent_addition, size_t hue, size_t hue_offset) {
		object_->draw_debug(render_target, 0, indent_addition, hue, hue_offset);
	}
	
	const std::vector<BoxPtr<BaseLine::MainLine>>& ObjectCharacter::get_line() {
		return lines_;
	}
	
	sf::Vector2i ObjectCharacter::get_size_texture() {
		return sf::Vector2i{object_->get_area_size()};
	}
	
	float ObjectCharacter::get_min_advance() {
		return special_ == BaseCharacter::Special::FullLine ? object_->get_min_size().x : object_->get_size().x;
	}
	
	sf::Vector2f ObjectCharacter::get_position() const {
		return BaseCharacter::get_position() + sf::Vector2f{0, get_height()};
	}
}