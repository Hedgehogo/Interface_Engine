#include "caption.hpp"

namespace ui {
	sf::Color Caption::defaultColor = sf::Color::Black;
	int Caption::defaultSize = 10;
	
	void Caption::setDefaultColor(sf::Color color) {
		defaultColor = color;
	}
	
	void Caption::setDefaultSize(int size) {
		defaultSize = size;
	}
	
	void Caption::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		OnlyDrawable::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		background->init(renderTarget, this->drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	Caption::Caption(sf::String text, OnlyDrawable *background, sf::Font &font, sf::Vector2f minSize, int fontSize, sf::Color color, sf::Text::Style style, float rotation) :
		str(text), background(background), minimumSize(minSize) {
		this->text.setString(text);
		this->text.setFont(font);
		this->text.setCharacterSize(fontSize);
		this->text.setFillColor(color);
		this->text.setStyle(style);
		this->text.setRotation(rotation);
	}
	
	Caption::Caption(sf::String text, OnlyDrawable *background, sf::Font &font, int fontSize, sf::Color color, sf::Text::Style style, float rotation) :
		str(text), background(background), minimumSize() {
		this->text.setString(text);
		this->text.setFont(font);
		this->text.setCharacterSize(fontSize);
		this->text.setFillColor(color);
		this->text.setStyle(style);
		this->text.setRotation(rotation);
	}
	
	void Caption::draw() {
		drawManager.draw();
		renderTarget->draw(text);
	}
	
	void Caption::resize(sf::Vector2f size, sf::Vector2f position) {
		background->resize(size, position);
		text.setString(str);
		if(text.getGlobalBounds().width < size.x && text.getGlobalBounds().height < size.y) {
			text.setPosition(position - sf::Vector2f(text.getGlobalBounds().left - text.getPosition().x, text.getGlobalBounds().top - text.getPosition().y));
			return;
		}
		sf::String string = this->str + sf::String("...");
		while(text.getGlobalBounds().width > size.x || text.getGlobalBounds().height > size.y) {
			string.erase(string.getSize() - 4, 1);
			text.setString(string);
		}
		text.setPosition(position - sf::Vector2f(text.getGlobalBounds().left - text.getPosition().x, text.getGlobalBounds().top - text.getPosition().y));
	}
	
	sf::Vector2f Caption::getAreaPosition() {
		return background->getAreaPosition();
	}
	
	sf::Vector2f Caption::getAreaSize() {
		return background->getAreaSize();
	}
	
	sf::Vector2f Caption::getMinSize() {
		return max(minimumSize, background->getMinSize());
	}
	
	sf::Vector2f Caption::getNormalSize() {
		sf::FloatRect rect = text.getGlobalBounds();
		return max({rect.width, rect.height}, background->getNormalSize());
	}
	
	Caption::Caption(sf::Text text, OnlyDrawable *background, sf::String str, sf::Vector2f minimumSize) : text(text), background(background), str(str), minimumSize(minimumSize) {}
	
	Caption *Caption::copy() {
		Caption* caption{new Caption{text, background, str, minimumSize}};
		OnlyDrawable::copy(caption);
		return caption;
	}
	
	void Caption::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	Caption *Caption::createFromYaml(const YAML::Node &node) {
		sf::String text;
		OnlyDrawable *background;
		sf::Font *font;
		int fontSize{defaultSize};
		sf::Color color{defaultColor};
		sf::Text::Style style{};
		float rotation{0};
		sf::Vector2f minSize{};
		
		node["text"] >> text;
		node["background"] >> background;
		node["font"] >> font;
		if(node["font-size"]) node["font-size"] >> fontSize;
		if(node["color"]) node["color"] >> color;
		if(node["style"]) node["style"] >> style;
		if(node["min-size"]) node["min-size"] >> minSize;
		if(node["rotation"]) node["rotation"] >> rotation;
		
		return new Caption{text, background, *font, minSize, fontSize, color, style, rotation};
	}
}