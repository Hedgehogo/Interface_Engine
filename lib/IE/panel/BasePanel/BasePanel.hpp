#pragma once

#include "IE/component/IComponent/IComponentLayout/IComponentObject/IComponentObject.hpp"
#include "IE/sizing-positioning/IPositioning/Functions/make_position/make_position.hpp"
#include "IE/sizing-positioning/ISizing/Functions/make_size_make/make_size_make.hpp"
#include "IE/sizing-positioning/ISizing2/ISizing2.hpp"
#include "IE/sizing-positioning/ISizing2/Sizing2/Sizing2.hpp"
#include "IE/sizing-positioning/ISizing2/ConstRatioSizing2/ConstRatioSizing2.hpp"
#include "IE/sizing-positioning/ISizing2/FnSizing2/FnSizing2.hpp"
#include "IE/sizing-positioning/IPositioning2/IPositioning2.hpp"
#include "IE/sizing-positioning/IPositioning2/Positioning2/Positioning2.hpp"
#include "IE/sizing-positioning/IPositioning2/InternalPositioning2/InternalPositioning2.hpp"
#include "IE/sizing-positioning/IPositioning2/FnPositioning2/FnPositioning2.hpp"
#include "IE/event/KeyHandler/KeyHandler.hpp"

namespace ie {
	class BasePanel : public virtual ILayoutObject, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make {
			virtual ~Make() = default;
			
			virtual auto make(InitInfo init_info) -> BasePanel* = 0;
		};
		
		BasePanel(
			BoxPtr<IScalable::Make>&& object,
			BoxPtr<ISizing2::Make> sizing,
			BoxPtr<IPositioning2::Make> positioning,
			bool displayed,
			InitInfo object_init_info,
			InitInfo init_info
		);
		
		virtual ~BasePanel() = default;
		
		virtual auto is_independent() -> bool = 0;
		
		virtual auto is_free() -> bool = 0;
		
		virtual auto set_displayed() -> void;
		
		virtual auto set_parent_processed(bool parent_processed) -> void;
		
		virtual auto get_parent_processed() -> bool;
		
		virtual auto in_panel(sf::Vector2f point_position) -> bool;
		
		auto in_area(sf::Vector2f point_position) -> bool;
		
		auto in(sf::Vector2f point_position) -> bool;
		
		auto draw() -> void override;
		
		auto set_position(sf::Vector2f position) -> void;
		
		auto move(sf::Vector2f offset) -> void;
		
		auto resize(sf::Vector2f parent_size, sf::Vector2f parent_position) -> void;
		
		auto update() -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool;
		
		virtual auto update_interactions(sf::Vector2f mouse_position, bool active) -> bool;
		
		auto get_area_position() const -> sf::Vector2f;
		
		auto get_area_size() const -> sf::Vector2f;
		
		auto get_min_size() const -> sf::Vector2f;
		
		auto get_normal_size() const -> sf::Vector2f;
		
		auto get_object() -> IScalable& override;
		
		auto get_object() const -> IScalable const& override;
		
		static auto set_full_debug(bool full_debug) -> void;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void;
	
	protected:
		auto layout_get_data() -> LayoutData& override;
		
		auto layout_get_data() const -> LayoutData const& override;
		
		LayoutData layout_;
		DrawManager draw_manager_;
		UpdateManager update_manager_;
		BoxPtr<IScalable> object_;
		BoxPtr<ISizing2> sizing_;
		BoxPtr<IPositioning2> positioning_;
		bool parent_processed_;
		bool old_displayed_;
		bool displayed_;
		bool active_;
		
		static bool full_debug_;
	};
}