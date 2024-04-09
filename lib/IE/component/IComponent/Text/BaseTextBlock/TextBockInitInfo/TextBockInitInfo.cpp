#include "TextBockInitInfo.hpp"

namespace ie {
	TextBockInitInfo::TextBockInitInfo(
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
	) : InitInfo(
			window,
			render_target,
			dyn_buffer,
			event_handler,
			draw_manager,
			update_manager,
			interaction_manager,
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