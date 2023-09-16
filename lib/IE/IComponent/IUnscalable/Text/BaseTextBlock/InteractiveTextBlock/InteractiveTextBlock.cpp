#include "InteractiveTextBlock.hpp"

#include <utility>
#include "IE/Modules/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ie {
	InteractiveTextBlock::InteractiveTextBlock(
		BoxPtr<IBaseInteraction>&& interaction,
		std::u32string text,
		orl::Option<sf::Color> textColor,
		orl::Option<sf::Font*> font,
		orl::Option<sf::Text::Style> style,
		std::vector<BoxPtr<BaseLine>>&& lines,
		orl::Option<uint> size,
		orl::Option<sf::Color> textSelectionColor,
		orl::Option<sf::Color> backgroundSelectionColor,
		orl::Option<sf::Color> inactiveTextSelectionColor,
		orl::Option<sf::Color> inactiveBackgroundSelectionColor
	) :
		TextBlock(std::move(text), textColor, font, style, std::move(lines), size, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor),
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
		interactiveTextBlock = new InteractiveTextBlock{
			node["interaction"].as<BoxPtr<IBaseInteraction> >(),
			node["text"].as<std::u32string>(),
			convDef<orl::Option<sf::Color> >(node["text-color"], {}),
			convDef<orl::Option<sf::Font*> >(node["font"], {}),
			convDef<orl::Option<sf::Text::Style> >(node["style"], {}),
			node["line"] ? makeVector(node["line"].as<BoxPtr<BaseLine>>()) : node["line"].as<std::vector<BoxPtr<BaseLine>>>(),
			convDef<orl::Option<uint>>(node["size"], {}),
			convDef<orl::Option<sf::Color> >(node["text-selection-color"], {}),
			convDef<orl::Option<sf::Color> >(node["background-selection-color"], {}),
			convDef<orl::Option<sf::Color> >(node["inactive-text-selection-color"], {}),
			convDef<orl::Option<sf::Color> >(node["inactive-background-selection-color"], {})
		};
		return true;
	}
}

