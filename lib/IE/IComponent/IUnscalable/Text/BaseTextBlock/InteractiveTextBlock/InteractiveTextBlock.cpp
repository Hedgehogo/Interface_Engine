#include "InteractiveTextBlock.hpp"
#include "IE/Modules/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ie {
	InteractiveTextBlock::InteractiveTextBlock(
		BoxPtr<IBaseInteraction>&& interaction, std::u32string text, sf::Color textColor, sf::Font* font, sf::Text::Style style, std::vector<BoxPtr<BaseLine>>&& lines, int size, sf::Color textSelectionColor,
		sf::Color backgroundSelectionColor, sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor
	) :
		TextBlock(text, textColor, font, style, std::move(lines), size, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor),
		interact(false), oldInteract(false), interaction(std::move(interaction)) {
	}
	
	void InteractiveTextBlock::init(InitInfo textInitInfo, InitInfo initInfo) {
		TextBlock::init(textInitInfo, initInfo);
		this->interactionManager = &textInitInfo.interactionManager;
	}
	
	void InteractiveTextBlock::update() {
		if(interact != oldInteract) {
			oldInteract = interact;
			if(interact) {
				interactionManager->addInteraction(*interaction);
			} else {
				interactionManager->deleteInteraction(*interaction);
			}
		}
		interact = false;
	}
	
	bool InteractiveTextBlock::updateInteractions(sf::Vector2f) {
		interact = true;
		return true;
	}
	
	bool InteractiveTextBlock::in(sf::Vector2f mousePosition) {
		for(auto& character: textCharacters) {
			if(character->in(mousePosition)) {
				return true;
			}
		}
		return false;
	}
	
	InteractiveTextBlock* InteractiveTextBlock::copy() {
		return nullptr;
	}
	
	bool DecodePointer<InteractiveTextBlock>::decodePointer(const YAML::Node& node, InteractiveTextBlock*& interactiveTextBlock) {
		std::u32string text;
		sf::Color textColor = nullColor;
		sf::Font* font = nullptr;
		sf::Text::Style style = {};
		std::vector<BoxPtr<BaseLine>> lines = {};
		int size = 0;
		sf::Color textSelectionColor = nullColor;
		sf::Color backgroundSelectionColor = nullColor;
		sf::Color inactiveTextSelectionColor = nullColor;
		sf::Color inactiveBackgroundSelectionColor = nullColor;
		
		node["text"] >> text;
		if(node["text-color"])
			node["text-color"] >> textColor;
		if(node["text-color"])
			node["text-color"] >> textColor;
		if(node["font"])
			node["font"] >> font;
		if(node["style"])
			node["style"] >> style;
		if(node["size"])
			node["size"] >> size;
		if(node["text-selection-color"])
			node["text-selection-color"] >> textSelectionColor;
		if(node["background-selection-color"])
			node["background-selection-color"] >> backgroundSelectionColor;
		if(node["inactive-text-selection-color"])
			node["inactive-text-selection-color"] >> inactiveTextSelectionColor;
		if(node["inactive-background-selection-color"])
			node["inactive-background-selection-color"] >> inactiveBackgroundSelectionColor;
		
		if(node["interaction"]) {
			interactiveTextBlock = new InteractiveTextBlock{
				node["interaction"].as<BoxPtr<IBaseInteraction> >(),
				text,
				textColor,
				font,
				style,
				node["line"] ? makeVector(node["line"].as<BoxPtr<BaseLine>>()) : node["line"].as<std::vector<BoxPtr<BaseLine>>>(),
				size,
				textSelectionColor,
				backgroundSelectionColor,
				inactiveTextSelectionColor,
				inactiveBackgroundSelectionColor
			};
		}
		return true;
	}
}

