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
			
			ButtonPanel* make(InitInfo init_info) override;
		};
		
		ButtonPanel(Make&& make, InitInfo init_info);
		
		ButtonPanel(BoxPtr<Panel>&& panel, BoxPtr<IDisplayPanelInteraction>&& interaction, BoxPtr<IScalable>&& background);
		
		ButtonPanel(const ButtonPanel& other);
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_min_size() const override;
		
		const Panel& get_panel() const;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		ButtonPanel* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		BoxPtr<Panel> panel;
		BasicInteractiveData<Panel&> interactive;
	};
	
	template<>
	struct DecodePointer<ButtonPanel> {
		static bool decode_pointer(const YAML::Node& node, ButtonPanel*& button_with_panel);
	};
}