#pragma once

#include "../BasicInteractiveData.hpp"
#include "IE/component/IComponent/IComponentLayout/IComponentLayout.hpp"
#include "../../IUninteractive/IUninteractive.hpp"
#include "../../IScalableLayout/IScalableLayout.hpp"
#include "IE/component/IDrawable/IDrawable/IDrawable.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	class Switcher : public virtual IScalableLayout, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make : public virtual IScalableLayout::Make {
			BoxPtr<IScalable::Make> inactive_background;
			BoxPtr<IScalable::Make> active_background;
			PSbool value;
			Key key = Key::MouseLeft;
			
			Make(BoxPtr<IScalable::Make>&& inactive_background, BoxPtr<IScalable::Make>&& active_background, PSbool value, Key key = Key::MouseLeft);
			
			Make(BoxPtr<IScalable::Make>&& inactive_background, BoxPtr<IScalable::Make>&& active_background, Key key = Key::MouseLeft, bool start_active = false);
			
			Switcher* make(InitInfo init_info) override;
		};
		
		Switcher(Make&& make, InitInfo init_info);
		
		Switcher(BoxPtr<IScalable>&& inactive_background, BoxPtr<IScalable>&& active_background, PSbool value, Key key = Key::MouseLeft);
		
		Switcher(BoxPtr<IScalable>&& inactive_background, BoxPtr<IScalable>&& active_background, Key key = Key::MouseLeft, bool start_active = false);
		
		void init(InitInfo init_info) override;
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		Switcher* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) override;
	
	protected:
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
		LayoutData layout;
		InteractiveData interactive;
		DrawManager inactive_draw_manager;
		DrawManager active_draw_manager;
		BoxPtr<IScalable> inactive_background;
		BoxPtr<IScalable> active_background;
		PSbool active;
	};
	
	template<>
	struct DecodePointer<Switcher> {
		static bool decode_pointer(const YAML::Node& node, Switcher*& switcher);
	};
}