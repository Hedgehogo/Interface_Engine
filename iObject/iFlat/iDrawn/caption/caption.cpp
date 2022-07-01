#include "caption.h"

namespace ui {
	sf::Color Caption::defaultColor = sf::Color::Black;
	int Caption::defaultSize = 10;
	
	void Caption::setDefaultColor(sf::Color color) {
		defaultColor = color;
	}
	
	void Caption::setDefaultSize(int size) {
		defaultSize = size;
	}
	
	void Caption::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		this->renderTarget = &renderTarget;
		initObject(background, renderTarget, interactionStack, interactionManager, panelManager);
	}
	
	Caption::Caption(const std::wstring& text, IDrawn *background, sf::Font &font, sf::Vector2f minimumSize, int size, sf::Color color, sf::Text::Style style, float rotation) :
		str(text), background(background), minimumSize(minimumSize) {
		this->text.setString(text);
		this->text.setFont(font);
		this->text.setCharacterSize(size);
		this->text.setFillColor(color);
		this->text.setStyle(style);
		this->text.setRotation(rotation);
	}
	
	Caption::Caption(const std::wstring& text, IDrawn *background, sf::Font &font, int size, sf::Color color, sf::Text::Style style, float rotation) :
		str(text), background(background), minimumSize() {
		this->text.setString(text);
		this->text.setFont(font);
		this->text.setCharacterSize(size);
		this->text.setFillColor(color);
		this->text.setStyle(style);
		this->text.setRotation(rotation);
	}
	
	void Caption::draw() {
		background->draw();
		renderTarget->draw(text);
	}
	
	void Caption::resize(sf::Vector2f size, sf::Vector2f position) {
		background->resize(size, position);
		text.setString(str);
		if(text.getGlobalBounds().width < size.x && text.getGlobalBounds().height < size.y) {
			text.setPosition(position - sf::Vector2f(text.getGlobalBounds().left - text.getPosition().x, text.getGlobalBounds().top - text.getPosition().y));
			return;
		}
		std::wstring writing = this->str + L"...";
		while(text.getGlobalBounds().width > size.x || text.getGlobalBounds().height > size.y) {
			writing.erase(writing.length() - 4, 1);
			text.setString(writing);
		}
		text.setPosition(position - sf::Vector2f(text.getGlobalBounds().left - text.getPosition().x, text.getGlobalBounds().top - text.getPosition().y));
	}
	
	sf::Vector2f Caption::getPosition() {
		return background->getPosition();
	}
	
	sf::Vector2f Caption::getAreaSize() {
		return background->getAreaSize();
	}
	
	sf::Vector2f Caption::getMinSize() {
		return minimumSize;
	}
	
	sf::Vector2f Caption::getNormalSize() {
		sf::FloatRect rect = text.getGlobalBounds();
		return {rect.width, rect.height};
	}
	
	Caption::Caption(sf::Text text, IDrawn *background, std::wstring str, sf::Vector2f minimumSize) : text(text), background(background), str(str), minimumSize(minimumSize) {}
	
	Caption *Caption::copy() {
		Caption* caption{new Caption{text, background, str, minimumSize}};
		IDrawn::copy(caption);
		return caption;
	}
}