#pragma once

#include <filesystem>

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/panel/IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "IE/interaction/IAction/WheelAction/WheelAction.hpp"
#include "IE/shared/DynBuffer/DynBuffer.hpp"
#include "../IScalable.hpp"

namespace ie {
	class Interface : public virtual IScalable, public virtual IDrawable, public virtual IUpdatable {
	protected:
		bool is_in_window(sf::Vector2f position);
	
	public:
		struct Make : public virtual IScalable::Make {
			BoxPtr<IScalable::Make> object;
			
			Make(BoxPtr<IScalable::Make>&& object);
			
			Interface* make(InitInfo init_info) override;
		};
		
		Interface(Make&& make, InitInfo init_info);
		
		explicit Interface(
			sf::RenderWindow& window,
			DynBuffer& dyn_buffer,
			BoxPtr<IScalable::Make>&& object
		);
		
		sf::RenderTarget& get_render_target();
		
		DrawManager& get_draw_manager();
		
		UpdateManager& get_update_manager();
		
		InteractionManager& get_interaction_manager();
		
		PanelManager& get_panel_manager();
		
		IScalable& get_object();
		
		void set_render_window_size(sf::RenderWindow& window);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
	
	protected:
		void update_cluster(sf::Vector2f mouse_position);
	
	public:
		void update() override;
		
		void update(sf::Vector2f mouse_position, bool active);
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue = 0, size_t hue_offset = 36) override;
	
	protected:
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
	
	Interface::Make make_interface(std::filesystem::path file_path, int argc = 0, char* argv[] = {});
	
	Interface make_interface(sf::RenderWindow& window, DynBuffer& dyn_buffer, std::filesystem::path file_path, int argc = 0, char* argv[] = {});
}

template<>
struct ieml::Decode<char, ie::Interface::Make> {
	static orl::Option<ie::Interface::Make> decode(ieml::Node const& node);
};
