#pragma once

#include "../BaseButton.hpp"
#include "IE/panel/BasePanel/Panel/Panel.hpp"
#include "IE/panel/IPanelInteraction/IDisplayPanelInteraction/PointingDisplayPanelInteraction/PointingDisplayPanelInteraction.hpp"
#include "IE/panel/IPanelInteraction/IDisplayPanelInteraction/ClickDisplayPanelInteraction/ClickDisplayPanelInteraction.hpp"
#include "IE/panel/IPanelInteraction/IHidePanelInteraction/PointingHidePanelInteraction/PointingHidePanelInteraction.hpp"
#include "IE/panel/IPanelInteraction/IHidePanelInteraction/ClickHidePanelInteraction/ClickHidePanelInteraction.hpp"
#include "IE/panel/IPanelInteraction/IHidePanelInteraction/DontHidePanelInteraction/DontHidePanelInteraction.hpp"
#include "IE/panel/IPanelInteraction/IMovePanelInteraction/DontMovePanelInteraction/DontMovePanelInteraction.hpp"
#include "IE/panel/IPanelInteraction/IMovePanelInteraction/CoefficientMovePanelInteraction/CoefficientMovePanelInteraction.hpp"
#include "IE/panel/IPanelInteraction/IMovePanelInteraction/SideMovePanelInteraction/SideMovePanelInteraction.hpp"

namespace ie {
	class ButtonPanel : public BaseButton {
	public:
		struct Make : public virtual IComponentObject::Make, public virtual IScalable::Make {
			BoxPtr<Panel::Make> panel;
			BoxPtr<IDisplayPanelInteraction::Make> interaction;
			BoxPtr<IScalable::Make> background;
			
			Make(BoxPtr<Panel::Make>&& panel, BoxPtr<IDisplayPanelInteraction::Make>&& interaction, BoxPtr<IScalable::Make>&& background);
			
			auto make(InitInfo init_info) -> ButtonPanel* override;
		};
		
		ButtonPanel(Make&& make, InitInfo init_info);
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_panel() const -> Panel const&;
		
		auto update() -> void override;
		
		auto update_interactions(Event event) -> bool override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		BoxPtr<Panel> panel_;
		BasicInteractiveData<Panel&> interactive_;
	};
}

template<>
struct ieml::Decode<char, ie::ButtonPanel::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ButtonPanel::Make>;
};
