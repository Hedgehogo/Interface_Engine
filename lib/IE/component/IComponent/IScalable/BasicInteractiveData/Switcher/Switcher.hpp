#pragma once

#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISValue/ISValue.hpp"
#include "../BasicInteractiveData.hpp"
#include "IE/component/IComponent/IComponentLayout/IComponentLayout.hpp"
#include "../../INonInteractive/INonInteractive.hpp"
#include "../../IScalableLayout/IScalableLayout.hpp"
#include "IE/component/IDrawable/IDrawable/IDrawable.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	class Switcher : public virtual IScalableLayout, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make : public virtual IScalableLayout::Make {
			BoxPtr<IScalable::Make> inactive_background;
			BoxPtr<IScalable::Make> active_background;
			MakeDyn<ISBool> value;
			Key key = Key::MouseLeft;
			
			Make(
				BoxPtr<IScalable::Make>&& inactive_background,
				BoxPtr<IScalable::Make>&& active_background,
				MakeDyn<ISBool> value,
				Key key = Key::MouseLeft
			);
			
			Switcher* make(InitInfo init_info) override;
		};
		
		Switcher(Make&& make, InitInfo init_info);
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		Switcher(
			BoxPtr<IScalable::Make> inactive_background,
			BoxPtr<IScalable::Make> active_background,
			ISBool& value,
			Key key,
			InitInfo init_info
		);
		
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
		LayoutData layout_;
		InteractiveData interactive_;
		DrawManager inactive_draw_manager_;
		DrawManager active_draw_manager_;
		BoxPtr<IScalable> inactive_background_;
		BoxPtr<IScalable> active_background_;
		ISBool& active_;
	};
}

template<>
struct ieml::Decode<char, ie::Switcher::Make> {
	static orl::Option<ie::Switcher::Make> decode(ieml::Node const& node);
};
