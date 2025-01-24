#pragma once

#include "../BaseButton.hpp"
#include "IE/panel/BasePanel/Panel/Panel.hpp"
#include "IE/panel/IPanelTrigger/IDisplayPanelTrigger/PointingDisplayPanelTrigger/PointingDisplayPanelTrigger.hpp"
#include "IE/panel/IPanelTrigger/IDisplayPanelTrigger/ClickDisplayPanelTrigger/ClickDisplayPanelTrigger.hpp"
#include "IE/panel/IPanelTrigger/IHidePanelTrigger/PointingHidePanelTrigger/PointingHidePanelTrigger.hpp"
#include "IE/panel/IPanelTrigger/IHidePanelTrigger/ClickHidePanelTrigger/ClickHidePanelTrigger.hpp"
#include "IE/panel/IPanelTrigger/IHidePanelTrigger/DontHidePanelTrigger/DontHidePanelTrigger.hpp"
#include "IE/panel/IPanelTrigger/IMovePanelTrigger/DontMovePanelTrigger/DontMovePanelTrigger.hpp"
#include "IE/panel/IPanelTrigger/IMovePanelTrigger/CoefficientMovePanelTrigger/CoefficientMovePanelTrigger.hpp"
#include "IE/panel/IPanelTrigger/IMovePanelTrigger/SideMovePanelTrigger/SideMovePanelTrigger.hpp"

namespace ie {
	class ButtonPanel : public BaseButton {
	public:
		struct Make : public virtual IComponentObject::Make, public virtual IScalable::Make {
			BoxPtr<Panel::Make> panel;
			BoxPtr<IDisplayPanelTrigger::Make> trigger;
			BoxPtr<IScalable::Make> background;
			
			Make(BoxPtr<Panel::Make>&& panel, BoxPtr<IDisplayPanelTrigger::Make>&& trigger, BoxPtr<IScalable::Make>&& background);
			
			auto make(InitInfo init_info) -> ButtonPanel* override;
		};
		
		ButtonPanel(Make&& make, InitInfo init_info);
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_panel() const -> Panel const&;
		
		auto update() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BoxPtr<Panel> panel_;
		BoxPtr<IDisplayPanelTrigger> trigger_;
	};
}

template<>
struct ieml::Decode<char, ie::ButtonPanel::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ButtonPanel::Make>;
};
