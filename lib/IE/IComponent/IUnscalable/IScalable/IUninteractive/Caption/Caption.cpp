#include "Caption.hpp"
#include <algorithm>
#include "../../../../../Modules/hsvToRgb/hsvToRgb.hpp"
#include "../OnlyDrawable/Capsule/Capsule.hpp"

using uint = unsigned;

namespace ie {
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
	
	Caption::Make::Make(
		sf::String text,
		BoxPtr<IUninteractive::Make>&& background,
		sf::Font& font,
		sf::Vector2f minSize,
		int fontSize,
		sf::Color color,
		sf::Text::Style style,
		float rotation,
		InternalPositioning2::Make positioning,
		bool cutBack
	) :
		text(text),
		background(std::move(background)),
		font(font),
		fontSize(fontSize),
		color(color),
		style(style),
		rotation(rotation),
		positioning(positioning),
		cutBack(cutBack),
		minSize(minSize) {
	}
	
	Caption::Make::Make(
		sf::String text,
		BoxPtr<IUninteractive::Make>&& background,
		sf::Font& font,
		int fontSize,
		sf::Color color,
		sf::Text::Style style,
		float rotation,
		InternalPositioning2::Make positioning,
		bool cutBack
	) :
		text(text),
		background(std::move(background)),
		font(font),
		fontSize(fontSize),
		color(color),
		style(style),
		rotation(rotation),
		positioning(positioning),
		cutBack(cutBack) {
	}
	
	Caption* Caption::Make::make(InitInfo initInfo) {
		return new Caption{std::move(*this), initInfo};
	}
	
	Caption::Caption(Make&& make, InitInfo initInfo) :
		OnlyDrawable(initInfo),
		cutBack(make.cutBack),
		str(make.text),
		background(make.background->make(initInfo.copy(drawManager))),
		minimumSize(make.minSize),
		positioning(std::move(make.positioning), {initInfo.renderTarget}) {
		this->text.setString(make.text);
		this->text.setFont(make.font);
		this->text.setCharacterSize(make.fontSize);
		this->text.setFillColor(make.color);
		this->text.setStyle(make.style);
		this->text.setRotation(make.rotation);
	}
	
	Caption::Caption(
		sf::String text,
		BoxPtr<IUninteractive>&& background,
		sf::Font& font,
		sf::Vector2f minSize,
		int fontSize,
		sf::Color color,
		sf::Text::Style style,
		float rotation,
		InternalPositioning2 positioning,
		bool cutBack
	) : cutBack(cutBack), str(text), background(std::move(background)), minimumSize(minSize), positioning(positioning) {
		this->text.setString(text);
		this->text.setFont(font);
		this->text.setCharacterSize(fontSize);
		this->text.setFillColor(color);
		this->text.setStyle(style);
		this->text.setRotation(rotation);
	}
	
	Caption::Caption(
		sf::String text,
		BoxPtr<IUninteractive>&& background,
		sf::Font& font,
		int fontSize,
		sf::Color color,
		sf::Text::Style style,
		float rotation,
		InternalPositioning2 positioning,
		bool cutBack
	) : cutBack(cutBack), str(text), background(background), minimumSize(), positioning(positioning) {
		this->text.setString(text);
		this->text.setFont(font);
		this->text.setCharacterSize(fontSize);
		this->text.setFillColor(color);
		this->text.setStyle(style);
		this->text.setRotation(rotation);
	}
	
	void Caption::init(InitInfo initInfo) {
		OnlyDrawable::init(initInfo);
		background->init(initInfo.copy(this->drawManager));
	}
	
	void Caption::draw() {
		drawManager.draw();
		renderTarget->draw(text);
	}
	
	sf::FloatRect Caption::getBounds(const sf::Text& text) const {
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
		
		sf::FloatRect bounds = getBounds(text);
		if(cutBack) {
			sf::String string = this->str + sf::String("...");
			while(bounds.width > size.x || bounds.height > size.y) {
				string.erase(string.getSize() - 4, 1);
				text.setString(string);
				bounds = getBounds(text);
			}
		}
		sf::Vector2f findPosition{positioning.findPosition(position, size, {bounds.width, bounds.height})};
		text.setPosition(findPosition - sf::Vector2f(getBounds(text).left - text.getPosition().x, getBounds(text).top - text.getPosition().y));
	}
	
	sf::Vector2f Caption::getAreaPosition() const {
		return background->getAreaPosition();
	}
	
	sf::Vector2f Caption::getAreaSize() const {
		return background->getAreaSize();
	}
	
	sf::Vector2f Caption::getMinSize() const {
		sf::FloatRect bounds{getBounds(sf::Text{"...", *text.getFont(), text.getCharacterSize()})};
		return max(
			max(
				minimumSize,
				(cutBack ?
				 sf::Vector2f{bounds.width, bounds.height} :
				 sf::Vector2f{})
			),
			background->getMinSize()
		);
	}
	
	sf::Vector2f Caption::getNormalSize() const {
		sf::FloatRect rect = text.getGlobalBounds();
		return max({rect.width, rect.height}, background->getNormalSize());
	}
	
	Caption* Caption::copy() {
		return new Caption{*this};
	}
	
	void Caption::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		{
			sf::FloatRect bounds{text.getGlobalBounds()};
			sf::Vector2f size{bounds.width, bounds.height};
			sf::Vector2f position{bounds.left, bounds.top};
			if(size.x > 0 && size.y > 0) {
				sf::Color color{hsvToRgb(static_cast<float>(hue + hueOffset * 2 % 360))};
				
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
			sf::FloatRect bounds{getBounds(text)};
			sf::Vector2f size{bounds.width, bounds.height};
			sf::Vector2f position{bounds.left, bounds.top};
			if(size.x > 0 && size.y > 0) {
				sf::Color color{hsvToRgb(static_cast<float>(hue + hueOffset % 360))};
				
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
	
	bool DecodePointer<Caption>::decodePointer(const YAML::Node& node, Caption*& caption) {
		caption = new Caption{
			node["text"].as<sf::String>(),
			node["background"].as<BoxPtr<IUninteractive> >(),
			*node["background"].as<sf::Font*>(),
			convDef(node["min-size"], sf::Vector2f{}),
			convDef(node["font-size"], Caption::getDefaultSize()),
			convDef(node["color"], Caption::getDefaultColor()),
			convDef(node["style"], sf::Text::Style{}),
			convDef(node["rotation"], 0.f),
			InternalPositioning2{{0.5, 0.5}},
			convDef(node["cut-back"], true)
		};
		return true;
	}
}