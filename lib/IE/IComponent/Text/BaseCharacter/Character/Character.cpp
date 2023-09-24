#include "Character.hpp"
#include "IE/Modules/hsvToRgb/hsvToRgb.hpp"

namespace ie {
	Character::Character(char32_t character, TextVariables& textVariables, std::vector<BoxPtr<BaseLine>>& lines) :
		character(character), textVariables(textVariables), vertexArray(sf::Quads, 4), selectionVertexArray(sf::Quads, 4), lines(lines) {
		if(isSpecial() != BaseCharacter::Special::Enter) {
			glyph = textVariables.font.some()->getGlyph(character, textVariables.size.some(), textVariables.style.some() & sf::Text::Style::Bold);
			
			texture = textVariables.font.some()->getTexture(textVariables.size.some());
			
			vertexArray[0].texCoords = sf::Vector2f(sf::Vector2i{glyph.textureRect.left, glyph.textureRect.top});
			vertexArray[1].texCoords = sf::Vector2f(sf::Vector2i{glyph.textureRect.left + glyph.textureRect.width, glyph.textureRect.top});
			vertexArray[2].texCoords = sf::Vector2f(sf::Vector2i{glyph.textureRect.left + glyph.textureRect.width, glyph.textureRect.top + glyph.textureRect.height});
			vertexArray[3].texCoords = sf::Vector2f(sf::Vector2i{glyph.textureRect.left, glyph.textureRect.top + glyph.textureRect.height});
			
			vertexArray[0].position = {0, 0};
			vertexArray[1].position = sf::Vector2f{sf::Vector2i{glyph.textureRect.width, 0}};
			vertexArray[2].position = sf::Vector2f{sf::Vector2i{glyph.textureRect.width, glyph.textureRect.height}};
			vertexArray[3].position = sf::Vector2f{sf::Vector2i{0, glyph.textureRect.height}};
			
			selectionVertexArray[0].position = {0, 0};
			selectionVertexArray[1].position = {getAdvance(), 0};
			selectionVertexArray[2].position = {getAdvance(), getHeight()};
			selectionVertexArray[3].position = {0, getHeight()};
			
			if(textVariables.style.some() & sf::Text::Style::Italic) {
				float italicShear = -0.26794;
				
				for(size_t i = 0; i < 4; ++i) {
					vertexArray[i].position.x += (vertexArray[i].position.y + glyph.bounds.top) * italicShear;
				}
			}
			
			for(size_t i = 0; i < 4; ++i) {
				vertexArray[i].position += {glyph.bounds.left, glyph.bounds.top};
				selectionVertexArray[i].position.y -= getHeight();
				
				vertexArray[i].color = textVariables.textColor.some();
				selectionVertexArray[i].color = textVariables.backgroundSelectionColor.some();
			}
		}
	}
	
	void Character::init(sf::RenderTarget& renderTarget) {
		this->renderTarget = &renderTarget;
	}
	
	void Character::setActive(bool active) {
		BaseCharacter::setActive(active);
		if(active) {
			for(int i = 0; i < 4; ++i) {
				vertexArray[i].color = textVariables.textSelectionColor.some();
				selectionVertexArray[i].color = textVariables.backgroundSelectionColor.some();
			}
		} else {
			for(int i = 0; i < 4; ++i) {
				vertexArray[i].color = textVariables.inactiveTextSelectionColor.some();
				selectionVertexArray[i].color = textVariables.inactiveBackgroundSelectionColor.some();
			}
		}
	}
	
	sf::Vector2i Character::getSizeTexture() {
		if(getChar() == U' ')
			return {static_cast<int>(getAdvance()), static_cast<int>(getHeight())};
		return {glyph.textureRect.width, glyph.textureRect.height};
	}
	
	void Character::setSelection(bool selection) {
		BaseCharacter::setSelection(selection);
		auto currentColor{selection ? textVariables.textSelectionColor.some() : textVariables.textColor.some()};
		for(std::size_t i = 0; i < 4; ++i) {
			vertexArray[i].color = currentColor;
		}
	}
	
	void Character::draw(bool selection) {
		if(isSpecial() != BaseCharacter::Special::Enter) {
			if(this->selection && selection)
				renderTarget->draw(selectionVertexArray);
			renderTarget->draw(vertexArray, &texture);
		}
	}
	
	BaseCharacter::Special Character::isSpecial() {
		if(character == L' ')
			return BaseCharacter::Special::Space;
		else if(character == L'\n')
			return BaseCharacter::Special::Enter;
		return BaseCharacter::Special::No;
	}
	
	char32_t Character::getChar() {
		return character;
	}
	
	float Character::getKerning(char32_t character) {
		return textVariables.font.some()->getKerning(this->character, character, textVariables.size.some());
	}
	
	float Character::getAdvance() {
		return glyph.advance;
	}
	
	float Character::getHeight() const {
		return textVariables.size.some();
	}
	
	void Character::setPosition(const sf::Vector2f position) {
		move(position - this->position);
		BaseCharacter::setPosition(position);
	}
	
	void Character::move(sf::Vector2f position) {
		BaseCharacter::move(position);
		for(std::size_t i = 0; i < 4; ++i) {
			selectionVertexArray[i].position += position;
			         vertexArray[i].position += position;
		}
	}
	
	const std::vector<BoxPtr<BaseLine>>& Character::getLine() {
		return lines;
	}
	
	bool Character::in(sf::Vector2f mousePosition) {
		
		return position.x < mousePosition.x && position.x + getAdvance() > mousePosition.x &&
			   position.y - getHeight() < mousePosition.y && position.y > mousePosition.y;
	}
	
	bool Character::debug = false;
	
	void Character::setDebug(bool debug) {
		Character::debug = debug;
	}
	
	void Character::drawDebug(sf::RenderTarget& renderTarget, int, uint hue, uint) {
		if(debug) {
			sf::Vector2f size{getAdvance() - 2.0f, getHeight() - 2.0f};
			sf::Vector2f position{this->getPosition() + sf::Vector2f{1.0f, 1.0f - getHeight()}};
			if(size.x > 0 && size.y > 0) {
				sf::Color color{hsvToRgb(static_cast<float>(hue % 360))};
				
				sf::RectangleShape rectangle{size};
				rectangle.setPosition(position);
				rectangle.setFillColor(sf::Color::Transparent);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(color);
				
				renderTarget.draw(rectangle);
			}
		}
	}
}