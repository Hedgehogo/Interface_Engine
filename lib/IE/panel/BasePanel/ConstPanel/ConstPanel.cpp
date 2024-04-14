#include "ConstPanel.hpp"
#include "../../IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/component/IDrawable/DrawManager/DrawManager.hpp"

namespace ie {
	ConstPanel::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<ISizing2::Make> sizing, BoxPtr<IPositioning2::Make> positioning, bool displayed) :
		object(std::move(object)), sizing(std::move(sizing)), positioning(std::move(positioning)), displayed(displayed) {
	}
	
	auto ConstPanel::Make::make(InitInfo init_info) -> ConstPanel* {
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
	
	auto ConstPanel::is_independent() -> bool {
		return false;
	}
	
	auto ConstPanel::is_free() -> bool {
		return true;
	}
	
	auto ConstPanel::handle_event(Event event, bool active) -> bool {
		displayed_ = true;
		this->active_ = active;
		return event.touch().map([=](event_system::Touch touch) {
			return in_panel(sf::Vector2f{touch.position});
		}).some_or(true) && object_->handle_event(event);
	}
}

auto ieml::Decode<char, ie::ConstPanel::Make>::decode(ieml::Node const& node) -> orl::Option<ie::ConstPanel::Make> {
	auto map{node.get_map_view().except()};
	return ie::ConstPanel::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("sizing").except().as<ie::BoxPtr<ie::ISizing2::Make> >().except(),
		map.at("positioning").except().as<ie::BoxPtr<ie::IPositioning2::Make> >().except(),
		map.get_as<bool>("displayed").except().ok_or(false)
	};
}
