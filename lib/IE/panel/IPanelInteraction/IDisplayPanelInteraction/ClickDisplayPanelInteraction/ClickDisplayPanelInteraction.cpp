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
	
	void ClickDisplayPanelInteraction::start(sf::Vector2i) {
		dynamic_cast<PanelAction&>(*action_).get_panel()->set_parent_processed(true);
	}
	
	void ClickDisplayPanelInteraction::finish(sf::Vector2i mouse_position) {
		BasicOneKeyInteraction<Panel&>::finish(mouse_position);
		dynamic_cast<PanelAction&>(*action_).get_panel()->set_parent_processed(false);
	}
}

orl::Option<ie::ClickDisplayPanelInteraction::Make> ieml::Decode<char, ie::ClickDisplayPanelInteraction::Make>::decode(ieml::Node const& node) {
	return {{node.at("key").except().as<ie::Key>().except()}};
}
