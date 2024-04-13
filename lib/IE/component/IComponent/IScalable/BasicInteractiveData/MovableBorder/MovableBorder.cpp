#include "MovableBorder.hpp"
#include "IE/interaction/IAction/BasicKeyAction/BasicAddInteractionAction/BasicAddBlockInteractionAction/BasicAddBlockInteractionAction.hpp"
#include "MovableBorderAction/MovableBorderAction.hpp"

namespace ie {
	MovableBorder::Make::Make(
		BoxPtr<IScalable::Make>&& first_object,
		BoxPtr<IScalable::Make>&& second_object,
		bool is_horizontal_border,
		MakeDyn<ISMRFloat> border_value,
		int border_interaction_size,
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
		border_interaction_size(border_interaction_size),
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
			},
			init_info
		),
		interactive_(
			make_box_ptr<BasicOneKeyInteraction<MovableBorder&>::Make>(
				make_box_ptr<BasicAddBlockInteractionAction<MovableBorder&>::Make>(
					make_box_ptr<BasicPressedInteraction<MovableBorder&>::Make>(
						make_box_ptr<MovableBorderAction::Make>(
							border_value_.get()
						),
						make.key
					)
				),
				make.key
			),
			init_info,
			*this
		),
		border_interaction_size_(make.border_interaction_size) {
		init_info.update_manager.add(*this);
		
	}
	
	auto MovableBorder::update() -> void {
		interactive_.update();
	}
	
	auto MovableBorder::update_interactions(Event event) -> bool {
		return event.touch().map([=](event_system::Touch touch) {
			auto border_position{layout_.position + first_object_->get_size()};
			auto in_border_axis = [=](float point_position, float border_position) {
				return point_position < (border_position + border_interaction_size_) && point_position > (border_position - border_interaction_size_);
			};
			auto in_border{
				is_horizontal_border_ ?
				in_border_axis(touch.position.y, border_position.y) :
				in_border_axis(touch.position.x, border_position.x)
			};
			
			if(in_border) {
				interactive_.update_interactions();
				return true;
			}
			return BasicBoxMovableBorder<true>::update_interactions(event);
		}).some_or_else([=] {
			return BasicBoxMovableBorder<true>::update_interactions(event);
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
		map.get_as<int>("border-interaction-size").except().ok_or(5),
		map.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
