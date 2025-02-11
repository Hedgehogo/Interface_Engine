#include "TextBockInitInfo.hpp"
#include "IE/ieml/Indexed/Indexed.hpp"

namespace ie {
	TextBockInitInfo::TextBockInitInfo(
		sf::RenderWindow& window,
		sf::RenderTarget& render_target,
		DynBuffer& dyn_buffer,
		EventHandler& event_handler,
		DrawManager& draw_manager,
		UpdateManager& update_manager,
		TriggerManager& trigger_manager,
		IPanelManager& panel_manager,
		sf::RenderTarget& text_render_target,
		DrawManager& text_draw_manager,
		TriggerManager& text_trigger_manager,
		absl::flat_hash_set<Indexed<TextStyle> >& text_style_buffer
	) :
		InitInfo(
			window,
			render_target,
			dyn_buffer,
			text_style_buffer,
			event_handler,
			draw_manager,
			update_manager,
			trigger_manager,
			panel_manager
		),
		text_render_target(text_render_target),
		text_draw_manager(text_draw_manager),
		text_trigger_manager(text_trigger_manager) {
	}
	
	TextBockInitInfo::TextBockInitInfo(
		InitInfo init_info,
		sf::RenderTarget& text_render_target,
		DrawManager& text_draw_manager,
		TriggerManager& text_trigger_manager
	) :
		InitInfo(init_info),
		text_render_target(text_render_target),
		text_draw_manager(text_draw_manager),
		text_trigger_manager(text_trigger_manager) {
	}
}