#include "ObjectCharacter.hpp"

namespace ie {
	ObjectCharacter::ObjectCharacter(BoxPtr<IScalable>&& object, bool fullLine) : object(std::move(object)), special(fullLine ? BaseCharacter::Special::FullLine : BaseCharacter::Special::No) {
	}
	
	char32_t ObjectCharacter::getChar() {
		return '\0';
	}
	
	void ObjectCharacter::setPosition(sf::Vector2f position) {
		position.y -= getHeight();
		BaseCharacter::setPosition(position);
		object->setPosition(position);
	}
	
	void ObjectCharacter::resize(sf::Vector2f position, float endPosition) {
		position.y -= getHeight();
		BaseCharacter::setPosition(position);
		object->resize({endPosition - position.x, object->getSize().y}, position);
	}
	
	void ObjectCharacter::move(sf::Vector2f position) {
		BaseCharacter::move(position);
		object->move(position);
	}
	
	float ObjectCharacter::getHeight() const {
		return object->getAreaSize().y;
	}
	
	float ObjectCharacter::getAdvance() {
		return object->getAreaSize().x;
	}
	
	float ObjectCharacter::getKerning(char32_t) {
		return 0;
	}
	
	BaseCharacter::Special ObjectCharacter::isSpecial() {
		return special;
	}
	
	void ObjectCharacter::draw(bool) {
	}
	
	void ObjectCharacter::drawDebug(sf::RenderTarget& renderTarget, int indentAddition, uint hue, uint hueOffset) {
		object->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
	}
	
	const std::vector<BoxPtr<BaseLine>>& ObjectCharacter::getLine() {
		return lines;
	}
	
	sf::Vector2i ObjectCharacter::getSizeTexture() {
		return sf::Vector2i{object->getAreaSize()};
	}
	
	float ObjectCharacter::getMinAdvance() {
		return special == BaseCharacter::Special::FullLine ? object->getMinSize().x : object->getSize().x;
	}
	
	sf::Vector2f ObjectCharacter::getPosition() const {
		return BaseCharacter::getPosition() + sf::Vector2f{0, getHeight()};
	}
}