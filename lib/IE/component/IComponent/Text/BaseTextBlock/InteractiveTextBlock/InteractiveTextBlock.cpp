#include "InteractiveTextBlock.hpp"

#include <utility>
#include "IE/modules/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ie {
	InteractiveTextBlock::Make::Make(
		BoxPtr<IBaseInteraction>&& interaction,
		const std::u32string& text,
		const orl::Option<sf::Color>& textColor,
		const orl::Option<sf::Font*>& font,
		const orl::Option<sf::Text::Style>& style,
		std::vector<BoxPtr<BaseLine::Make>>&& lines,
		const orl::Option<uint>& size,
		const orl::Option<sf::Color>& textSelectionColor,
		const orl::Option<sf::Color>& backgroundSelectionColor,
		const orl::Option<sf::Color>& inactiveTextSelectionColor,
		const orl::Option<sf::Color>& inactiveBackgroundSelectionColor
	) : TextBlock::Make(
			text,
			textColor,
			font,
			style,
			std::move(lines),
			size,
			textSelectionColor,
			backgroundSelectionColor,
			inactiveTextSelectionColor,
			inactiveBackgroundSelectionColor
		),
		interaction(std::move(interaction)) {
	}
	
	InteractiveTextBlock* InteractiveTextBlock::Make::make(TextBockInitInfo textBlockInitInfo) {
		return new InteractiveTextBlock{std::move(*this), textBlockInitInfo};
	}
	
	InteractiveTextBlock::InteractiveTextBlock(
		Make&& make,
		TextBockInitInfo textBlockInitInfo
	) : TextBlock(
			TextBlock::Make{
				std::move(make.text),
				make.textColor,
				make.font,
				make.style,
				std::move(make.lines),
				make.size,
				make.textSelectionColor,
				make.backgroundSelectionColor,
				make.inactiveTextSelectionColor,
				make.inactiveBackgroundSelectionColor
			},
			textBlockInitInfo
		),
		interact(false),
		oldInteract(false),
		interaction(std::move(make.interaction)) {
		this->interactionManager = &textBlockInitInfo.textInteractionManager;
	}
	
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
	) : TextBlock(
			std::move(text),
			textColor,
			font,
			style,
			std::move(lines),
			size,
			textSelectionColor,
			backgroundSelectionColor,
			inactiveTextSelectionColor,
			inactiveBackgroundSelectionColor
		),
		interact(false),
		oldInteract(false),
		interaction(std::move(interaction)) {
	}
	
	void InteractiveTextBlock::init(TextBockInitInfo textBlockInitInfo) {
		TextBlock::init(textBlockInitInfo);
		this->interactionManager = &textBlockInitInfo.interactionManager;
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
			node["interaction"].as < BoxPtr < IBaseInteraction > > (),
			node["text"].as<std::u32string>(),
			convDef<orl::Option<sf::Color> >(node["text-color"], {}),
			convDef<orl::Option<sf::Font*> >(node["font"], {}),
			convDef<orl::Option<sf::Text::Style> >(node["style"], {}),
			node["line"] ? makeVector(node["line"].as < BoxPtr < BaseLine >> ()) : node["line"].as<std::vector<BoxPtr<BaseLine>>>(),
			convDef<orl::Option<uint>>(node["size"], {}),
			convDef<orl::Option<sf::Color> >(node["text-selection-color"], {}),
			convDef<orl::Option<sf::Color> >(node["background-selection-color"], {}),
			convDef<orl::Option<sf::Color> >(node["inactive-text-selection-color"], {}),
			convDef<orl::Option<sf::Color> >(node["inactive-background-selection-color"], {})
		};
		return true;
	}
}
