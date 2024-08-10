#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "IE/component/IComponent/InitInfo/InitInfo.hpp"
#include "IE/component/IComponent/Text/TextStyle/TextStyle.hpp"
#include "IE/ieml/Indexed/Indexed.hpp"

namespace ie {
	struct TextBockInitInfo : public InitInfo {
		sf::RenderTarget& text_render_target;
		DrawManager& text_draw_manager;
		InteractionManager& text_interaction_manager;
		
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
			absl::flat_hash_set<bp::BoxPtr<Indexed<TextStyle> > >& text_style_buffer
		);
		
		TextBockInitInfo(
			InitInfo init_info,
			sf::RenderTarget& text_render_target,
			DrawManager& text_draw_manager,
			InteractionManager& text_interaction_manager
		);
	};
}
