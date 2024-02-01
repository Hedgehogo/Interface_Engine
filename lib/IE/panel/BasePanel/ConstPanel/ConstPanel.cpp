#include "ConstPanel.hpp"
#include "../../IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/component/IDrawable/DrawManager/DrawManager.hpp"

namespace ie {
	ConstPanel::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<ISizing2::Make> sizing, BoxPtr<IPositioning2::Make> positioning, bool displayed) :
		object(std::move(object)), sizing(std::move(sizing)), positioning(std::move(positioning)), displayed(displayed) {
	}
	
	ConstPanel* ConstPanel::Make::make(InitInfo init_info) {
		return new ConstPanel{std::move(*this), init_info};
	}
	
	ConstPanel::ConstPanel(Make&& make, InitInfo init_info) :
		BasePanel(
			std::move(make.object),
			std::move(make.sizing),
			std::move(make.positioning),
			make.displayed,
			init_info,
			init_info
		) {
		init_info.panel_manager.display_panel(this);
	}
	
	bool ConstPanel::is_independent() {
		return false;
	}
	
	bool ConstPanel::is_free() {
		return true;
	}
}

orl::Option<ie::ConstPanel::Make> ieml::Decode<char, ie::ConstPanel::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::ConstPanel::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.at("sizing").except().as<ie::BoxPtr<ie::ISizing2::Make> >().move_except(),
		map.at("positioning").except().as<ie::BoxPtr<ie::IPositioning2::Make> >().move_except(),
		map.get_as<bool>("displayed").ok_or(false)
	};
}
