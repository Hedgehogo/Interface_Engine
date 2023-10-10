#include "Character.hpp"
#include "IE/Modules/hsvToRgb/hsvToRgb.hpp"

namespace ie {
	template<typename T>
	void makeRectBonesPosition(sf::Rect<T> rect, sf::VertexArray& vertexArray){
		vertexArray[0].position = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top}};
		vertexArray[1].position = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top}};
		vertexArray[2].position = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top + rect.height}};
		vertexArray[3].position = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top + rect.height}};
	}
	
	template<typename T>
	void makeRectBonesTexCoords(sf::Rect<T> rect, sf::VertexArray& vertexArray){
		vertexArray[0].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top}};
		vertexArray[1].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top}};
		vertexArray[2].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left + rect.width, rect.top + rect.height}};
 		vertexArray[3].texCoords = sf::Vector2f{sf::Vector2<T>{rect.left, rect.top + rect.height}};
	}
	
	Character::Character(
		char32_t character,
		TextVariables& textVariables,
		std::vector<BoxPtr<BaseLine>>& lines,
		orl::Option<sf::RenderTarget&> renderTarget
	) : renderTarget(character == '\n' ? orl::Option<sf::RenderTarget&>{} : renderTarget),
		character(character),
		advance(0),
		kerning(0),
		textVariables(textVariables),
		vertexArray(sf::Quads, 4),
		selectionVertexArray(sf::Quads, 4),
		lines(lines) {
		if(renderTarget) {
			glyph = textVariables.font.some()->getGlyph(character, textVariables.size.some(), textVariables.style.some() & sf::Text::Style::Bold);
			advance = glyph.advance;
			texture = textVariables.font.some()->getTexture(textVariables.size.some());
			
			makeRectBonesTexCoords(glyph.textureRect, vertexArray);
			
			makeRectBonesPosition<int>({0, 0, glyph.textureRect.width, glyph.textureRect.height}, vertexArray);
			
			makeRectBonesPosition<float>({0, 0, getAdvance(), getHeight()}, selectionVertexArray);
			
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
		if(renderTarget) {
			if(this->selection && selection)
				renderTarget.some().draw(selectionVertexArray);
			renderTarget.some().draw(vertexArray, &texture);
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
		return advance;
	}
	
	float Character::getHeight() const {
		return textVariables.size.some();
	}
	
	void Character::setPosition(sf::Vector2f position) {
		position.x += kerning;
		move(position - this->position);
		BaseCharacter::setPosition(position);
	}
	
	void Character::setKerning(float kerning) {
		advance -= this->kerning;
		advance += kerning;
		this->kerning = kerning;
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