#pragma once

#include <filesystem>

#include "../IScalable.hpp"
#include "IE/panel/IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "IE/interaction/InteractionStack/InteractionStack.hpp"
#include "IE/interaction/IAction/WheelAction/WheelAction.hpp"

namespace ie {
	class Interface : public virtual IScalable, public virtual IDrawable, public virtual IUpdatable {
	protected:
		bool is_in_window(sf::Vector2f position);
	
	public:
		struct Make : public virtual IScalable::Make {
			BoxPtr<IScalable::Make> object;
			AnimationManager animation_manager = AnimationManager{{}};
			BoxPtr<InteractionStack> interaction_stack = make_box_ptr<InteractionStack>();
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				AnimationManager animation_manager = AnimationManager{{}},
				BoxPtr<InteractionStack>&& interaction_stack = make_box_ptr<InteractionStack>()
			);
			
			Interface* make(InitInfo init_info) override;
		};
		
		Interface(Make&& make, InitInfo init_info);
		
		explicit Interface(
			BoxPtr<IScalable>&& object,
			AnimationManager animation_manager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interaction_stack = make_box_ptr<InteractionStack>()
		);
		
		/*old_yaml
		explicit Interface(
			const std::string& file_path,
			AnimationManager animation_manager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interaction_stack = make_box_ptr<InteractionStack>()
		);
		*/
		
		explicit Interface(
			sf::RenderWindow& window,
			BoxPtr<IScalable>&& object,
			AnimationManager animation_manager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interaction_stack = make_box_ptr<InteractionStack>()
		);
		
		/*old_yaml
		explicit Interface(
			sf::RenderWindow& window,
			const std::string& file_path,
			AnimationManager animation_manager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interaction_stack = make_box_ptr<InteractionStack>()
		);
		*/
		
		explicit Interface(
			sf::RenderWindow& window,
			BoxPtr<IScalable::Make>&& object,
			AnimationManager animation_manager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interaction_stack = make_box_ptr<InteractionStack>()
		);
		
		void init(InitInfo init_info) override;
		
		void init(sf::RenderWindow& window);
		
		[[nodiscard]] sf::RenderTarget& get_render_target();
		
		[[nodiscard]] DrawManager& get_draw_manager();
		
		[[nodiscard]] UpdateManager& get_update_manager();
		
		[[nodiscard]] InteractionManager& get_interaction_manager();
		
		[[nodiscard]] InteractionStack& get_interaction_stack();
		
		[[nodiscard]] PanelManager& get_panel_manager();
		
		[[nodiscard]] IScalable& get_object();
		
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
		
		Interface* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue = 0, size_t hue_offset = 36) override;
	
	protected:
		sf::RenderWindow* window_;
		sf::RenderTarget* render_target_;
		DrawManager draw_manager_;
		UpdateManager update_manager_;
		InteractionManager interaction_manager_;
		BoxPtr<InteractionStack> interaction_stack_;
		PanelManager panel_manager_;
		AnimationManager animation_manager_;
		BoxPtr<IScalable> object_;
		sf::Vector2f mouse_position_;
		bool initialized_;
		bool active_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<Interface> {
		static bool decode_pointer(const YAML::Node& node, Interface*& interface);
	};
	
	Interface make_interface(const std::filesystem::path& file_path, int argc = 0, char* argv[] = {});
	
	Interface make_interface(sf::RenderWindow& window, const std::filesystem::path& file_path, int argc = 0, char* argv[] = {});
	
	Interface* make_prt_interface(sf::RenderWindow& window, const std::filesystem::path& file_path, int argc = 0, char* argv[] = {});
	*/
}