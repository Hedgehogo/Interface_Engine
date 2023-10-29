#pragma once

#include "../TextBlock/TextBlock.hpp"
#include "IE/interaction/IInteraction/IInteraction.hpp"

namespace ie {
	class InteractiveTextBlock : public TextBlock {
	public:
		struct Make : public TextBlock::Make {
			BoxPtr<IBaseInteraction> interaction;
			
			Make(BoxPtr<IBaseInteraction>&& interaction,
				 const std::u32string& text,
				 const orl::Option<sf::Color>& text_color = {},
				 const orl::Option<sf::Font*>& font = {},
				 const orl::Option<sf::Text::Style>& style = {},
				 std::vector<BoxPtr<BaseLine::Make>>&& lines = {},
				 const orl::Option<size_t>& size = {},
				 const orl::Option<sf::Color>& text_selection_color = {},
				 const orl::Option<sf::Color>& background_selection_color = {},
				 const orl::Option<sf::Color>& inactive_text_selection_color = {},
				 const orl::Option<sf::Color>& inactive_background_selection_color = {}
			);
			
			InteractiveTextBlock* make(TextBockInitInfo text_block_init_info) override;
		};
		
		InteractiveTextBlock(Make&& make, TextBockInitInfo text_block_init_info);
		
		InteractiveTextBlock(
			BoxPtr<IBaseInteraction>&& interaction,
			std::u32string text,
			orl::Option<sf::Color> text_color = {},
			orl::Option<sf::Font*> font = {},
			orl::Option<sf::Text::Style> style = {},
			std::vector<BoxPtr<BaseLine>>&& lines = {},
			orl::Option<size_t> size = {},
			orl::Option<sf::Color> text_selection_color = {},
			orl::Option<sf::Color> background_selection_color = {},
			orl::Option<sf::Color> inactive_text_selection_color = {},
			orl::Option<sf::Color> inactive_background_selection_color = {}
		);
		
		void init(TextBockInitInfo text_block_init_info);
		
		bool in(sf::Vector2f mouse_position);
		
		void update() override;
		
		bool update_interactions(sf::Vector2f) override;
		
		InteractiveTextBlock* copy() override;
	
	protected:
		InteractionManager* interaction_manager;
		
		bool interact;
		bool old_interact;
		
		BoxPtr<IInteraction> interaction;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<InteractiveTextBlock> {
		static bool decode_pointer(const YAML::Node& node, InteractiveTextBlock*& interactive_text_block);
	};
	*/
}