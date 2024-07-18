#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "IE/component/IComponent/InitInfo/InitInfo.hpp"
#include "IE/component/IComponent/InitInfo/InitInfo.hpp"
#include "../../TextVariables/TextVariables.hpp"

namespace ie {
	struct TextBockInitInfo : public InitInfo {
		struct TextVariables {
			sf::Color
				text_color,
				text_selection_color,
				background_selection_color,
				inactive_text_selection_color,
				inactive_background_selection_color;
			sf::Font& font;
			sf::Text::Style style;
			size_t size;
		};
		sf::RenderTarget& text_render_target;
		DrawManager& text_draw_manager;
		InteractionManager& text_interaction_manager;
		TextVariables& text_variables;
		
		TextBockInitInfo(
			sf::RenderWindow& window,
			sf::RenderTarget& render_target,
			DynBuffer& dyn_buffer,
			EventHandler& event_handler,
			DrawManager& draw_manager,
			UpdateManager& update_manager,
			InteractionManager& interaction_manager,
			IPanelManager& panel_manager,
			sf::RenderTarget& text_render_target,
			DrawManager& text_draw_manager,
			InteractionManager& text_interaction_manager,
			TextVariables& text_variables
		);
		
		TextBockInitInfo(
			InitInfo init_info,
			sf::RenderTarget& text_render_target,
			DrawManager& text_draw_manager,
			InteractionManager& text_interaction_manager,
			TextVariables&& text_variables
		);
	};
}
