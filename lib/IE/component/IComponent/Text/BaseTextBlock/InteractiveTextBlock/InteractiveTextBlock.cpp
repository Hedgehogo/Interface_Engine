#include "InteractiveTextBlock.hpp"

#include <utility>

namespace ie {
	InteractiveTextBlock::Make::Make(
		BoxPtr<IBaseInteraction::Make>&& interaction,
		const std::u32string& text,
		const orl::Option<sf::Color>& text_color,
		const orl::Option<sf::Font*>& font,
		const orl::Option<sf::Text::Style>& style,
		std::vector<BoxPtr<BaseLine::Make>>&& lines,
		const orl::Option<size_t>& size,
		const orl::Option<sf::Color>& text_selection_color,
		const orl::Option<sf::Color>& background_selection_color,
		const orl::Option<sf::Color>& inactive_text_selection_color,
		const orl::Option<sf::Color>& inactive_background_selection_color
	) : TextBlock::Make(
			text,
			text_color,
			font,
			style,
			std::move(lines),
			size,
			text_selection_color,
			background_selection_color,
			inactive_text_selection_color,
			inactive_background_selection_color
		),
		interaction(std::move(interaction)) {
	}
	
	InteractiveTextBlock* InteractiveTextBlock::Make::make(TextBockInitInfo init_info) {
		return new InteractiveTextBlock{std::move(*this), init_info};
	}
	
	InteractiveTextBlock::InteractiveTextBlock(
		Make&& make,
		TextBockInitInfo init_info
	) : TextBlock(
		TextBlock::Make{
				std::move(make.text),
				make.text_color,
				make.font,
				make.style,
				std::move(make.lines),
				make.size,
				make.text_selection_color,
				make.background_selection_color,
				make.inactive_text_selection_color,
				make.inactive_background_selection_color
			},
		init_info
		),
		interact(false),
		old_interact(false),
		interaction(make.interaction->make({static_cast<InitInfo>(init_info), std::monostate()})) {
		this->interaction_manager = &init_info.text_interaction_manager;
	}
	
	InteractiveTextBlock::InteractiveTextBlock(
		BoxPtr<IBaseInteraction>&& interaction,
		std::u32string text,
		orl::Option<sf::Color> text_color,
		orl::Option<sf::Font*> font,
		orl::Option<sf::Text::Style> style,
		std::vector<BoxPtr<BaseLine>>&& lines,
		orl::Option<size_t> size,
		orl::Option<sf::Color> text_selection_color,
		orl::Option<sf::Color> background_selection_color,
		orl::Option<sf::Color> inactive_text_selection_color,
		orl::Option<sf::Color> inactive_background_selection_color
	) : TextBlock(
			std::move(text),
			text_color,
			font,
			style,
			std::move(lines),
			size,
			text_selection_color,
			background_selection_color,
			inactive_text_selection_color,
			inactive_background_selection_color
		),
		interact(false),
		old_interact(false),
		interaction(std::move(interaction)) {
	}
	
	void InteractiveTextBlock::init(TextBockInitInfo text_block_init_info) {
		TextBlock::init(text_block_init_info);
		this->interaction_manager = &text_block_init_info.interaction_manager;
	}
	
	void InteractiveTextBlock::update() {
		if(interact != old_interact) {
			old_interact = interact;
			if(interact) {
				interaction_manager->add_interaction(*interaction);
			} else {
				interaction_manager->delete_interaction(*interaction);
			}
		}
		interact = false;
	}
	
	bool InteractiveTextBlock::update_interactions(sf::Vector2f) {
		interact = true;
		return true;
	}
	
	bool InteractiveTextBlock::in(sf::Vector2f mouse_position) {
		for(auto& character: text_characters) {
			if(character->in(mouse_position)) {
				return true;
			}
		}
		return false;
	}
	
	InteractiveTextBlock* InteractiveTextBlock::copy() {
		return nullptr;
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<InteractiveTextBlock>::decode_pointer(const YAML::Node& node, InteractiveTextBlock*& interactive_text_block) {
		interactive_text_block = new InteractiveTextBlock{
			node["interaction"].as < BoxPtr < IBaseInteraction > > (),
			node["text"].as<std::u32string>(),
			conv_def<orl::Option<sf::Color> >(node["text-color"], {}),
			conv_def<orl::Option<sf::Font*> >(node["font"], {}),
			conv_def<orl::Option<sf::Text::Style> >(node["style"], {}),
			node["line"] ? make_vector(node["line"].as < BoxPtr < BaseLine >> ()) : node["line"].as<std::vector<BoxPtr<BaseLine>>>(),
			conv_def<orl::Option<size_t>>(node["size"], {}),
			conv_def<orl::Option<sf::Color> >(node["text-selection-color"], {}),
			conv_def<orl::Option<sf::Color> >(node["background-selection-color"], {}),
			conv_def<orl::Option<sf::Color> >(node["inactive-text-selection-color"], {}),
			conv_def<orl::Option<sf::Color> >(node["inactive-background-selection-color"], {})
		};
		return true;

	}
	*/
}
