#include "MovableBorder.hpp"
#include "IE/trigger/ITrigger/BasicTouchTrigger/BasicTouchTrigger.hpp"
#include "MovableBorderAction/MovableBorderAction.hpp"

namespace ie {
	MovableBorder::Make::Make(
		BoxPtr<IScalable::Make>&& first_object,
		BoxPtr<IScalable::Make>&& second_object,
		bool is_horizontal_border,
		MakeDyn<ISMRFloat> border_value,
		int border_trigger_size,
		Key key,
		sf::Vector2f min_size
	) :
		make_system::BasicBoxMovableBorder<true>(
			std::move(first_object),
			std::move(second_object),
			is_horizontal_border,
			std::move(border_value),
			min_size
		),
		border_trigger_size(border_trigger_size),
		key(key) {
	}
	
	auto MovableBorder::Make::make(InitInfo init_info) -> MovableBorder* {
		return new MovableBorder{std::move(*this), init_info};
	}
	
	MovableBorder::MovableBorder(Make&& make, InitInfo init_info) :
		BasicBoxMovableBorder<true>(
			{
				std::move(make.first_object),
				std::move(make.second_object),
				make.is_horizontal_border,
				std::move(make.border_value),
				make.min_size
			}, init_info
		),
		trigger_({make_box_ptr<BasicTouchTrigger<MovableBorder&>::Make>(
			make_box_ptr<MovableBorderAction::Make>(border_value_.get()),
			make.key
		)}, {init_info, *this}),
		border_trigger_size_(make.border_trigger_size) {
		init_info.update_manager.add(*this);
		
	}
	
	auto MovableBorder::update() -> void {
		trigger_.update();
	}
	
	auto MovableBorder::handle_event(Event event) -> bool {
		return event.pointer().map([this, event](event_system::Pointer pointer) {
			auto border_position{layout_.position + first_object_->get_size()};
			auto in_border_axis = [=](float point_position, float border_position) {
				return point_position < (border_position + border_trigger_size_) && point_position > (border_position - border_trigger_size_);
			};
			auto in_border{
				is_horizontal_border_ ?
				in_border_axis(pointer.position.y, border_position.y) :
				in_border_axis(pointer.position.x, border_position.x)
			};
			
			return (in_border && trigger_.handle_event(event)) || BasicBoxMovableBorder<true>::handle_event(event);
		}).some_or_else([this, event] {
			return BasicBoxMovableBorder<true>::handle_event(event);
		});
	}
}

auto ieml::Decode<char, ie::MovableBorder::Make>::decode(ieml::Node const& node) -> orl::Option<ie::MovableBorder::Make> {
	auto map{node.get_map_view().except()};
	return ie::MovableBorder::Make{
		map.at("first-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("second-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<bool>("border-horizontal").except().ok_or(false),
		map.at("border-value").except().as<ie::MakeDyn<ie::ISMRFloat> >().except(),
		map.get_as<int>("border-trigger-size").except().ok_or(5),
		map.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
