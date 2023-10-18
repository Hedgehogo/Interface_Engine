#include "ClickDisplayPanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	ClickDisplayPanelInteraction::Make::Make(Key key) : key(key) {
	}
	
	ClickDisplayPanelInteraction* ClickDisplayPanelInteraction::Make::make(PanelActionInitInfo init_info) {
		return new ClickDisplayPanelInteraction{std::move(*this), init_info};
	}
	
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(Make&& make, PanelActionInitInfo init_info) :
		ClickPanelInteraction(make_box_ptr<DisplayPanelAction::Make>(), make.key, init_info) {
	}
	
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(Key key) :
		ClickPanelInteraction(make_box_ptr<DisplayPanelAction>(), key) {
	}
	
	void ClickDisplayPanelInteraction::start(sf::Vector2i) {
		dynamic_cast<PanelAction&>(*action).get_panel()->set_parent_processed(true);
	}
	
	void ClickDisplayPanelInteraction::finish(sf::Vector2i mouse_position) {
		BasicOneKeyInteraction<Panel&>::finish(mouse_position);
		dynamic_cast<PanelAction&>(*action).get_panel()->set_parent_processed(false);
	}
	
	ClickDisplayPanelInteraction* ClickDisplayPanelInteraction::copy() {
		return new ClickDisplayPanelInteraction{*this};
	}
	
	bool DecodePointer<ClickDisplayPanelInteraction>::decode_pointer(const YAML::Node& node, ClickDisplayPanelInteraction*& click_display_panel_interaction) {
		click_display_panel_interaction = new ClickDisplayPanelInteraction{node["key"].as<Key>()};
		return true;
	}
}