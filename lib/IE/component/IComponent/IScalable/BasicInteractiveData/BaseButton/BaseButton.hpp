#pragma once

#include "../BasicInteractiveData.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "../../IUninteractive/IUninteractive.hpp"

namespace ie {
	class BaseButton : public virtual IScalableObject, public virtual IUpdatable {
	public:
		BaseButton(BoxPtr<IScalable::Make>&& background, InitInfo init_info);
		
		BaseButton(BoxPtr<IScalable>&& background);
		
		void init(InitInfo init_info) override;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
		LayoutData layout;
		BoxPtr<IScalable> background;
	};
}
