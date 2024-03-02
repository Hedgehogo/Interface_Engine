#pragma once

#include "../BasicInteractiveData.hpp"
#include "../../IScalableLayout/IScalableObject/IScalableObject.hpp"
#include "IE/component/IComponent/IScalable/INonInteractive/INonInteractive.hpp"

namespace ie {
	class BaseButton : public virtual IScalableObject, public virtual IUpdatable {
	public:
		BaseButton(BoxPtr<IScalable::Make>&& background, InitInfo init_info);
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		auto layout_get_data() -> LayoutData& override;
		
		auto layout_get_data() const -> LayoutData const& override;
		
		LayoutData layout_;
		BoxPtr<IScalable> background_;
	};
}
