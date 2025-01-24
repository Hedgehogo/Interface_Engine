#include "Panel.hpp"
#include "../../IPanelTrigger/IMovePanelTrigger/DontMovePanelTrigger/DontMovePanelTrigger.hpp"

namespace ie {
	Panel::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<IHidePanelTrigger::Make> hide_trigger,
		BoxPtr<IMovePanelTrigger::Make> move_trigger,
		BoxPtr<ISizing2::Make> sizing,
		BoxPtr<IPositioning2::Make> positioning,
		bool displayed
	) :
		object(std::move(object)),
		hide_trigger(std::move(hide_trigger)),
		move_trigger(std::move(move_trigger)),
		sizing(std::move(sizing)),
		positioning(std::move(positioning)),
		displayed(displayed) {
	}
	
	Panel::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<IHidePanelTrigger::Make> hide_trigger,
		BoxPtr<ISizing2::Make> sizing,
		BoxPtr<IPositioning2::Make> positioning,
		bool displayed
	) :
		object(std::move(object)),
		hide_trigger(std::move(hide_trigger)),
		move_trigger(make_box_ptr<DontMovePanelTrigger::Make>()),
		sizing(std::move(sizing)),
		positioning(std::move(positioning)),
		displayed(displayed) {
	}
	
	auto Panel::Make::make(InitInfo init_info) -> Panel* {
		return new Panel{std::move(*this), init_info};
	}
	
	Panel::Panel(Make&& make, InitInfo init_info) :
		BasePanel(
			std::move(make.object),
			std::move(make.sizing),
			std::move(make.positioning),
			make.displayed,
			init_info.copy(panel_manager_),
			init_info
		),
		trigger_manager_(&init_info.trigger_manager),
		hide_trigger_(make.hide_trigger->make({init_info, *this})),
		move_trigger_(make.move_trigger->make({init_info, *this})) {
	}
	
	auto Panel::set_displayed() -> void {
		displayed_ = true;
	}
	
	auto Panel::is_independent() -> bool {
		return true;
	}
	
	auto Panel::is_free() -> bool {
		return panel_manager_.is_free();
	}
	
	auto Panel::in_const_panels(sf::Vector2f point_position) -> bool {
		return panel_manager_.in_const_panels(point_position);
	}
	
	auto Panel::draw() -> void {
		BasePanel::draw();
		panel_manager_.draw();
	}
	
	auto Panel::update() -> void {
		panel_manager_.update();
		hide_trigger_->update();
		move_trigger_->update();
		BasePanel::update();
	}
	
	auto Panel::handle_event(Event event, bool active) -> bool {
		displayed_ = true;
		this->active_ = active;
		auto updated{hide_trigger_->handle_event(event) || move_trigger_->handle_event(event)};
		return
			panel_manager_.handle_event(event, active) ||
			event.pointer().map([=](event_system::Pointer pointer) {
				return in_panel(sf::Vector2f{pointer.position});
			}).some_or(true) && object_->handle_event(event) || updated;
	}
}

auto ieml::Decode<char, ie::Panel::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Panel::Make> {
	auto map{node.get_map_view().except()};
	return ie::Panel::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("hide-trigger").except().as<ie::BoxPtr<ie::IHidePanelTrigger::Make> >().except(),
		map.get_as<ie::BoxPtr<ie::IMovePanelTrigger::Make> >("move-trigger").except().ok_or_else([] {
			return ie::make_box_ptr<ie::IMovePanelTrigger::Make, ie::DontMovePanelTrigger::Make>();
		}),
		map.at("sizing").except().as<ie::BoxPtr<ie::ISizing2::Make> >().except(),
		map.at("positioning").except().as<ie::BoxPtr<ie::IPositioning2::Make> >().except(),
		map.get_as<bool>("displayed").except().ok_or(false),
	};
}
