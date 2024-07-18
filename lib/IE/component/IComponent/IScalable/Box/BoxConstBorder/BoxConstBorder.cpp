#include "BoxConstBorder.hpp"

namespace ie {
	BoxConstBorder::Make::Make(
		BoxPtr<IScalable::Make>&& const_object,
		BoxPtr<IScalable::Make>&& second_object,
		float border_distance,
		Side side,
		sf::Vector2f min_size
	) :
		const_object(std::move(const_object)),
		second_object(std::move(second_object)),
		border_distance(border_distance),
		side(side),
		min_size(min_size) {
	}
	
	auto BoxConstBorder::Make::make(InitInfo init_info) -> BoxConstBorder* {
		return new BoxConstBorder{std::move(*this), init_info};
	}
	
	BoxConstBorder::BoxConstBorder(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		const_object_(make.const_object->make(init_info)),
		second_object_(make.second_object->make(init_info)),
		border_distance_(make.border_distance),
		side_(make.side) {
	}
	
	auto BoxConstBorder::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		
		switch(side_) {
			case Side::Up:
				const_object_->resize({size.x, border_distance_}, position);
				second_object_->resize({size.x, size.y - border_distance_}, position + sf::Vector2f(0, border_distance_));
				break;
			case Side::Down:
				const_object_->resize({size.x, border_distance_}, {position.x, position.y + size.y - border_distance_});
				second_object_->resize({size.x, size.y - border_distance_}, position);
				break;
			case Side::Left:
				const_object_->resize({border_distance_, size.y}, position);
				second_object_->resize({size.x - border_distance_, size.y}, position + sf::Vector2f(border_distance_, 0));
				break;
			case Side::Right:
				const_object_->resize({border_distance_, size.y}, {position.x + size.x - border_distance_, position.y});
				second_object_->resize({size.x - border_distance_, size.y}, position);
				break;
		}
	}
	
	auto BoxConstBorder::handle_event(Event event) -> bool {
		return event.pointer().map([=](event_system::Pointer pointer) {
			if(const_object_->in_area(sf::Vector2f{pointer.position})) {
				return const_object_->handle_event(event);
			}
			return second_object_->handle_event(event);
		}).some_or_else([=] {
			auto const_updated{const_object_->handle_event(event)};
			auto second_updated{second_object_->handle_event(event)};
			return const_updated || second_updated;
		});
	}
	
	auto BoxConstBorder::get_min_size() const -> sf::Vector2f {
		auto const_min_size{const_object_->get_min_size()};
		auto second_min_size{second_object_->get_min_size()};
		if(side_ == Side::Down || side_ == Side::Up) {
			return {std::max(const_min_size.x, second_min_size.x), second_min_size.y + border_distance_};
		} else {
			return {second_min_size.x + border_distance_, std::max(const_min_size.y, second_min_size.y)};
		}
	}
	
	auto BoxConstBorder::get_normal_size() const -> sf::Vector2f {
		auto const_normal_size{const_object_->get_normal_size()};
		auto second_normal_size{second_object_->get_normal_size()};
		if(side_ == Side::Down || side_ == Side::Up) {
			return {std::max(const_normal_size.x, second_normal_size.x), second_normal_size.y + border_distance_};
		} else {
			return {second_normal_size.x + border_distance_, std::max(const_normal_size.y, second_normal_size.y)};
		}
	}
	
	auto BoxConstBorder::get_first_object() -> IScalable& {
		return *const_object_;
	}
	
	auto BoxConstBorder::get_first_object() const -> IScalable const& {
		return *const_object_;
	}
	
	auto BoxConstBorder::get_second_object() -> IScalable& {
		return *second_object_;
	}
	
	auto BoxConstBorder::get_second_object() const -> IScalable const& {
		return *second_object_;
	}
	
	auto BoxConstBorder::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		const_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}

auto ieml::Decode<char, ie::BoxConstBorder::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxConstBorder::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxConstBorder::Make{
		map.at("const-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("second-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("border-distance").except().as<float>().except(),
		map.at("side").except().as<ie::Side>().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
