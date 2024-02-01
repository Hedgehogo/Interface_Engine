#include "ObjectCharacter.hpp"

namespace ie {
	ObjectCharacter::ObjectCharacter(BoxPtr<IScalable>&& object, ObjectSpecial special) : object(std::move(object)), special(static_cast<BaseCharacter::Special>(special)) {
	}
	
	ObjectCharacter::ObjectCharacter(const ObjectCharacter& other) : object(nullptr), special(other.special) {
	}
	
	void ObjectCharacter::set_position(sf::Vector2f position) {
		position.y -= get_height();
		BaseCharacter::set_position(position);
		object->set_position(position);
	}
	
	void ObjectCharacter::resize(sf::Vector2f position, float end_position) {
		position.y -= get_height();
		BaseCharacter::set_position(position);
		object->resize({is_special() == BaseCharacter::Special::FullLine ?  end_position - position.x : object->get_size().x, object->get_size().y}, position);
	}
	
	void ObjectCharacter::move(sf::Vector2f position) {
		BaseCharacter::move(position);
		object->move(position);
	}
	
	bool ObjectCharacter::update_interactions(sf::Vector2f mouse_position) {
		return object->update_interactions(mouse_position);
	}
	
	char32_t ObjectCharacter::get_char() {
		return '\0';
	}
	
	float ObjectCharacter::get_height() const {
		return object->get_area_size().y;
	}
	
	float ObjectCharacter::get_advance() {
		return object->get_area_size().x;
	}
	
	float ObjectCharacter::get_kerning(char32_t) {
		return 0;
	}
	
	BaseCharacter::Special ObjectCharacter::is_special() {
		return special;
	}
	
	void ObjectCharacter::draw() {
	}
	
	void ObjectCharacter::draw_debug(sf::RenderTarget& render_target, int indent_addition, size_t hue, size_t hue_offset) {
		object->draw_debug(render_target, 0, indent_addition, hue, hue_offset);
	}
	
	const std::vector<BoxPtr<BaseLine>>& ObjectCharacter::get_line() {
		return lines;
	}
	
	sf::Vector2i ObjectCharacter::get_size_texture() {
		return sf::Vector2i{object->get_area_size()};
	}
	
	float ObjectCharacter::get_min_advance() {
		return special == BaseCharacter::Special::FullLine ? object->get_min_size().x : object->get_size().x;
	}
	
	sf::Vector2f ObjectCharacter::get_position() const {
		return BaseCharacter::get_position() + sf::Vector2f{0, get_height()};
	}
}