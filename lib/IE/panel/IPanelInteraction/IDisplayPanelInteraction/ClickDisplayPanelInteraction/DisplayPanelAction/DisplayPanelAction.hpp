#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../../../ClickPanelInteraction/PanelAction/PanelAction.hpp"

namespace ie {
	class DisplayPanelAction : public PanelAction {
	public:
		struct Make : public virtual PanelAction::Make {
			DisplayPanelAction* make(PanelActionInitInfo init_info) override;
		};
		
		DisplayPanelAction(Make&& make, PanelActionInitInfo init_info);
		
		DisplayPanelAction() = default;
		
		DisplayPanelAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void while_pressed() override;
		
		void stop_pressed() override;
		
		void while_not_pressed() override;
	};
}

template<>
struct ieml::Decode<char, ie::DisplayPanelAction::Make> {
	static orl::Option<ie::DisplayPanelAction::Make> decode(ieml::Node const& node);
};
