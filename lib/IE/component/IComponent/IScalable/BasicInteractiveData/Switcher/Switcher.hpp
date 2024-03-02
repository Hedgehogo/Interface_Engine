#pragma once

#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISReadable.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include "IE/component/IDrawable/IDrawable/IDrawable.hpp"
#include "IE/component/IComponent/IComponentLayout/IComponentLayout.hpp"
#include "../BasicInteractiveData.hpp"
#include "../../INonInteractive/INonInteractive.hpp"
#include "../../IScalableLayout/IScalableLayout.hpp"

namespace ie {
	class Switcher : public virtual IScalableLayout, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make : public virtual IScalableLayout::Make {
			BoxPtr<IScalable::Make> inactive_background;
			BoxPtr<IScalable::Make> active_background;
			MakeDyn<ISMBool> value;
			Key key = Key::MouseLeft;
			
			Make(
				BoxPtr<IScalable::Make>&& inactive_background,
				BoxPtr<IScalable::Make>&& active_background,
				MakeDyn<ISMBool> value,
				Key key = Key::MouseLeft
			);
			
			auto make(InitInfo init_info) -> Switcher* override;
		};
		
		Switcher(Make&& make, InitInfo init_info);
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto move(sf::Vector2f position) -> void override;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update() -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		Switcher(
			BoxPtr<IScalable::Make> inactive_background,
			BoxPtr<IScalable::Make> active_background,
			ISMBool& value,
			Key key,
			InitInfo init_info
		);
		
		auto layout_get_data() -> LayoutData& override;
		
		auto layout_get_data() const -> LayoutData const& override;
		
		LayoutData layout_;
		InteractiveData interactive_;
		DrawManager inactive_draw_manager_;
		DrawManager active_draw_manager_;
		BoxPtr<IScalable> inactive_background_;
		BoxPtr<IScalable> active_background_;
		ISMBool& active_;
	};
}

template<>
struct ieml::Decode<char, ie::Switcher::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Switcher::Make>;
};
