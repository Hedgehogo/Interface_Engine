#pragma once

#include <filesystem>

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/panel/IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "IE/interaction/IAction/IBasicWheelAction/IBasicWheelAction.hpp"
#include "IE/shared/DynBuffer/DynBuffer.hpp"
#include "../IScalable.hpp"
#include "IE/ieml/Indexed/Indexed.hpp"
#include "IE/component/IComponent/Text/TextStyle/TextStyle.hpp"

namespace ie {
	class Interface : public virtual IScalable, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make : public virtual IScalable::Make {
			BoxPtr<IScalable::Make> object;
			
			Make(BoxPtr<IScalable::Make>&& object);
			
			auto make(InitInfo init_info) -> Interface* override;
		};
		
		Interface(Make&& make, InitInfo init_info);
		
		explicit Interface(
			sf::RenderWindow& window,
			DynBuffer& dyn_buffer,
			absl::flat_hash_set<bp::BoxPtr<Indexed<TextStyle> > >& text_style_buffer,
			EventHandler& event_handler,
			BoxPtr<IScalable::Make>&& object
		);
		
		auto get_render_target() -> sf::RenderTarget&;
		
		auto get_draw_manager() -> DrawManager&;
		
		auto get_update_manager() -> UpdateManager&;
		
		auto get_interaction_manager() -> InteractionManager&;
		
		auto get_panel_manager() -> PanelManager&;
		
		auto get_object() -> IScalable&;
		
		auto set_render_window_size(sf::RenderWindow& window) -> void;
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto get_area_position() const -> sf::Vector2f override;
		
		auto get_area_size() const -> sf::Vector2f override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto update() -> void override;
		
		auto update(std::vector<Event> const& events, bool active) -> void;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue = 0, size_t hue_offset = 36) -> void override;
	
	protected:
		auto is_in_window(sf::Vector2f position) -> bool;
		
		auto update_cluster() -> void;
		
		sf::RenderWindow* window_;
		sf::RenderTarget* render_target_;
		DrawManager draw_manager_;
		UpdateManager update_manager_;
		InteractionManager interaction_manager_;
		PanelManager panel_manager_;
		BoxPtr<IScalable> object_;
		sf::Vector2f mouse_position_;
		bool active_;
	};
	
	auto make_interface(std::filesystem::path file_path, int argc = 0, char* argv[] = {}) -> Interface::Make;
	
	auto make_interface(
		sf::RenderWindow& window,
		DynBuffer& dyn_buffer,
		absl::flat_hash_set<bp::BoxPtr<Indexed<TextStyle> > >& text_style_buffer,
		EventHandler& event_handler,
		std::filesystem::path file_path,
		int argc = 0,
		char* argv[] = {}
	) -> Interface;
}

template<>
struct ieml::Decode<char, ie::Interface::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Interface::Make>;
};
