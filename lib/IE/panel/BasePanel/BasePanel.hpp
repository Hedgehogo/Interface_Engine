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
#include "IE/enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	class BasePanel : public virtual ILayoutObject, public virtual IDrawable, public virtual IUpdatable {
	public:
		struct Make {
			virtual ~Make() = default;
			
			virtual BasePanel* make(InitInfo init_info) = 0;
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
		
		virtual bool is_independent() = 0;
		
		virtual bool is_free() = 0;
		
		virtual void set_displayed();
		
		virtual void set_parent_processed(bool parent_processed);
		
		virtual bool get_parent_processed();
		
		virtual bool in_panel(sf::Vector2f point_position);
		
		bool in_area(sf::Vector2f point_position);
		
		bool in(sf::Vector2f point_position);
		
		void draw() override;
		
		void set_position(sf::Vector2f position);
		
		void move(sf::Vector2f offset);
		
		void resize(sf::Vector2f parent_size, sf::Vector2f parent_position);
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position);
		
		virtual bool update_interactions(sf::Vector2f mouse_position, bool active);
		
		sf::Vector2f get_area_position() const;
		
		sf::Vector2f get_area_size() const;
		
		sf::Vector2f get_min_size() const;
		
		sf::Vector2f get_normal_size() const;
		
		IScalable& get_object() override;
		
		const IScalable& get_object() const override;
		
		static void set_full_debug(bool full_debug);
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset);
	
	protected:
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
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