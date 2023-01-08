#include "caption.hpp"
#include <algorithm>
#include "../../../../../../modules/appendix/HSVtoRGB/HsVtoRgb.hpp"
#include <iostream>

typedef unsigned uint;

namespace ui {
	sf::Color Caption::defaultColor = sf::Color::Black;
	int Caption::defaultSize = 10;
	
	void Caption::setDefaultColor(sf::Color color) {
		defaultColor = color;
	}
	
	void Caption::setDefaultSize(int size) {
		defaultSize = size;
	}
	
	sf::Color Caption::getDefaultColor() {
		return defaultColor;
	}
	
	int Caption::getDefaultSize() {
		return defaultSize;
	}
	
	void Caption::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
        OnlyDrawable::init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		background->init(renderTarget, this->drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	Caption::Caption(sf::String text, IUninteractive *background, sf::Font &font, sf::Vector2f minSize, int fontSize, sf::Color color, sf::Text::Style style, float rotation, InternalPositioning2 internalPositioning2,
                     bool cutBack) :
		str(text), background(background), minimumSize(minSize), internalPositioning2(internalPositioning2), cutBack(cutBack){
		this->text.setString(text);
		this->text.setFont(font);
		this->text.setCharacterSize(fontSize);
		this->text.setFillColor(color);
		this->text.setStyle(style);
		this->text.setRotation(rotation);
	}
	
	Caption::Caption(sf::String text, IUninteractive *background, sf::Font &font, int fontSize, sf::Color color, sf::Text::Style style, float rotation, InternalPositioning2 internalPositioning2, bool cutBack) :
		str(text), background(background), minimumSize(), internalPositioning2(internalPositioning2), cutBack(cutBack){
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

    sf::FloatRect Caption::getBounds() {
        sf::FloatRect localBounds = text.getLocalBounds();

        float countEnter{(static_cast<float>(std::count(text.getString().begin(), text.getString().end(), '\n')))};
        float characterSize{static_cast<float>(text.getFont()->getLineSpacing(text.getCharacterSize()))};

        sf::FloatRect bounds{
	        {0, 0},
            {
                localBounds.left + localBounds.width,
                text.getCharacterSize() + (countEnter * text.getLineSpacing() * characterSize)
            }
        };
        return text.getTransform().transformRect(bounds);
    }
	
	void Caption::resize(sf::Vector2f size, sf::Vector2f position) {
		background->resize(size, position);
		text.setString(str);

        sf::FloatRect bounds = getBounds();
        if (cutBack){
            sf::String string = this->str + sf::String("...");
            while (bounds.width > size.x || bounds.height > size.y) {
                string.erase(string.getSize() - 4, 1);
                text.setString(string);
                bounds = getBounds();
            }
        }
        text.setPosition(internalPositioning2.findPosition(position, size, {bounds.width, bounds.height}) - sf::Vector2f(getBounds().left - text.getPosition().x, getBounds().top - text.getPosition().y));
	}
	
	sf::Vector2f Caption::getAreaPosition() {
		return background->getAreaPosition();
	}
	
	sf::Vector2f Caption::getAreaSize() {
		return background->getAreaSize();
	}
	
	sf::Vector2f Caption::getMinSize() {
		sf::String str{text.getString()};
		text.setString("...");
		sf::FloatRect bounds{getBounds()};
		text.setString(str);
		return max(max(minimumSize, (cutBack ? sf::Vector2f{bounds.width, bounds.height} : sf::Vector2f{0.f, 0.f})), background->getMinSize());
	}
	
	sf::Vector2f Caption::getNormalSize() {
		sf::FloatRect rect = text.getGlobalBounds();
		return max({rect.width, rect.height}, background->getNormalSize());
	}
	
	Caption::Caption(sf::Text text, IUninteractive *background, sf::String str, sf::Vector2f minimumSize, InternalPositioning2 internalPositioning2, bool cutBack) :
        text(text), background(background), str(str), minimumSize(minimumSize), internalPositioning2(internalPositioning2), cutBack(cutBack) {}
	
	Caption *Caption::copy() {
		Caption* caption{new Caption{text, background, str, minimumSize, internalPositioning2, cutBack}};
		OnlyDrawable::copy(caption);
		return caption;
	}
	
	void Caption::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
        {
            sf::FloatRect bounds{text.getGlobalBounds()};
            sf::Vector2f size{bounds.width, bounds.height};
            sf::Vector2f position{bounds.left, bounds.top};
            if (size.x > 0 && size.y > 0) {
                sf::Color color{HSVtoRGB(static_cast<float>(hue + hueOffset*2 % 360))};

                sf::RectangleShape rectangle{size};
                rectangle.setPosition(position);
                rectangle.setFillColor(sf::Color::Transparent);
                rectangle.setOutlineThickness(1);
                rectangle.setOutlineColor(color);

                renderTarget.draw(rectangle);

                sf::CircleShape circle{2, 4};
                circle.setPosition(position + size * 0.5f - sf::Vector2f{2.0f, 2.0f});
                circle.setFillColor(color);

                renderTarget.draw(circle);
            }
        }
        {
            sf::FloatRect bounds{getBounds()};
            sf::Vector2f size{bounds.width, bounds.height};
            sf::Vector2f position{bounds.left, bounds.top};
            if (size.x > 0 && size.y > 0) {
                sf::Color color{HSVtoRGB(static_cast<float>(hue + hueOffset % 360))};

                sf::RectangleShape rectangle{size};
                rectangle.setPosition(position);
                rectangle.setFillColor(sf::Color::Transparent);
                rectangle.setOutlineThickness(1);
                rectangle.setOutlineColor(color);

                renderTarget.draw(rectangle);

                sf::CircleShape circle{2, 4};
                circle.setPosition(position + size * 0.5f - sf::Vector2f{2.0f, 2.0f});
                circle.setFillColor(color);

                renderTarget.draw(circle);
            }
        }
	}
	
	bool convertPointer(const YAML::Node &node, Caption *&caption) {
		sf::String text;
		IUninteractive *background;
		sf::Font *font;
		int fontSize{Caption::getDefaultSize()};
		sf::Color color{Caption::getDefaultColor()};
		sf::Text::Style style{};
		float rotation{0};
		sf::Vector2f minSize{};
        InternalPositioning2 internalPositioning2{{0.5, 0.5}};
        bool cutBack = true;
		
		node["text"] >> text;
		node["background"] >> background;
		node["font"] >> font;
		if(node["font-size"]) node["font-size"] >> fontSize;
		if(node["color"]) node["color"] >> color;
		if(node["style"]) node["style"] >> style;
		if(node["min-size"]) node["min-size"] >> minSize;
		if(node["rotation"]) node["rotation"] >> rotation;
        if(node["cut-back"]) node["cut-back"] >> cutBack;
		
		{ caption = new Caption{text, background, *font, minSize, fontSize, color, style, rotation, internalPositioning2, cutBack}; return true; }
	}

}