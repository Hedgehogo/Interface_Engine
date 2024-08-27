#include "InitInfo.hpp"
#include "IE/ieml/Indexed/Indexed.hpp"
#include "IE/component/IComponent/Text/TextStyle/TextStyle.hpp"

namespace ie {
	InitInfo::InitInfo(
		sf::RenderWindow& window_,
		sf::RenderTarget& render_target_,
		DynBuffer& dyn_buffer,
		absl::flat_hash_set<Indexed<TextStyle> >& text_style_buffer_,
		EventHandler& event_handler_,
		DrawManager& draw_manager_,
		UpdateManager& update_manager_,
		InteractionManager& interaction_manager_,
		IPanelManager& panel_manager_
	) :
		window(window_),
		render_target(render_target_),
		dyn_buffer(dyn_buffer),
		text_style_buffer(text_style_buffer_),
		event_handler(event_handler_),
		draw_manager(draw_manager_),
		update_manager(update_manager_),
		interaction_manager(interaction_manager_),
		panel_manager(panel_manager_) {
	}
	
	auto InitInfo::copy(sf::RenderWindow& window_) const -> InitInfo {
		return {window_, render_target, dyn_buffer, text_style_buffer, event_handler, draw_manager, update_manager, interaction_manager, panel_manager};
	}
	
	auto InitInfo::copy(sf::RenderTarget& render_target_) const -> InitInfo {
		return {window, render_target_, dyn_buffer, text_style_buffer, event_handler, draw_manager, update_manager, interaction_manager, panel_manager};
	}
	
	auto InitInfo::copy(DynBuffer& dyn_buffer_) const -> InitInfo {
		return {window, render_target, dyn_buffer_, text_style_buffer, event_handler, draw_manager, update_manager, interaction_manager, panel_manager};
	}
	
	auto InitInfo::copy(absl::flat_hash_set<Indexed<TextStyle> >& text_style_buffer_) const -> InitInfo {
		return {window, render_target, dyn_buffer, text_style_buffer_, event_handler, draw_manager, update_manager, interaction_manager, panel_manager};
	}
	
	auto InitInfo::copy(EventHandler& event_handler_) const -> InitInfo {
		return {window, render_target, dyn_buffer, text_style_buffer, event_handler_, draw_manager, update_manager, interaction_manager, panel_manager};
	}
	
	auto InitInfo::copy(DrawManager& draw_manager_) const -> InitInfo {
		return {window, render_target, dyn_buffer, text_style_buffer, event_handler, draw_manager_, update_manager, interaction_manager, panel_manager};
	}
	
	auto InitInfo::copy(UpdateManager& update_manager_) const -> InitInfo {
		return {window, render_target, dyn_buffer, text_style_buffer, event_handler, draw_manager, update_manager_, interaction_manager, panel_manager};
	}
	
	auto InitInfo::copy(InteractionManager& interaction_manager_) const -> InitInfo {
		return {window, render_target, dyn_buffer, text_style_buffer, event_handler, draw_manager, update_manager, interaction_manager_, panel_manager};
	}
	
	auto InitInfo::copy(IPanelManager& panel_manager_) const -> InitInfo {
		return {window, render_target, dyn_buffer, text_style_buffer, event_handler, draw_manager, update_manager, interaction_manager, panel_manager_};
	}
}