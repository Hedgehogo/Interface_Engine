#include "TextBockInitInfo.hpp"

namespace ie {
	TextBockInitInfo::TextBockInitInfo(
		sf::RenderWindow& window,
		sf::RenderTarget& render_target,
		DrawManager& draw_manager,
		UpdateManager& update_manager,
		InteractionManager& interaction_manager,
		InteractionStack& interaction_stack,
		IPanelManager& panel_manager,
		sf::RenderTarget& text_render_target,
		DrawManager& text_draw_manager,
		InteractionManager& text_interaction_manager,
		TextVariables& text_variables
	) : InitInfo(
			window,
			render_target,
			draw_manager,
			update_manager,
			interaction_manager,
			interaction_stack,
			panel_manager
		),
		text_render_target(text_render_target),
		text_draw_manager(text_draw_manager),
		text_interaction_manager(text_interaction_manager),
		text_variables(text_variables) {
	}
	
	TextBockInitInfo::TextBockInitInfo(
		InitInfo init_info,
		sf::RenderTarget& text_render_target,
		DrawManager& text_draw_manager,
		InteractionManager& text_interaction_manager,
		TextVariables&& text_variables
	) : InitInfo(init_info),
		text_render_target(text_render_target),
		text_draw_manager(text_draw_manager),
		text_interaction_manager(text_interaction_manager),
		text_variables(text_variables) {
	}
}