#include "IE/interaction/IAction/IBasicActivityAction/BasicAddInteractionAction/BasicAddPrioritisedInteractionAction/BasicAddPrioritisedInteractionAction.hpp"
#include <algorithm>

namespace ie {
	namespace make_system {
		template<bool mutable_>
		BasicBoxMovableBorder<mutable_>::BasicBoxMovableBorder(
			BoxPtr<IScalable::Make>&& first_object,
			BoxPtr<IScalable::Make>&& second_object,
			bool is_horizontal_border,
			MakeDyn<Value_> border_value,
			sf::Vector2f min_size
		) :
			first_object(std::move(first_object)),
			second_object(std::move(second_object)),
			is_horizontal_border(is_horizontal_border),
			border_value(std::move(border_value)),
			min_size(min_size) {
		}
		
		template<bool mutable_>
		auto BasicBoxMovableBorder<mutable_>::make(InitInfo init_info) -> ie::BasicBoxMovableBorder<mutable_>* {
			return new ie::BasicBoxMovableBorder{std::move(*this), init_info};
		}
	}
	
	template<bool mutable_>
	BasicBoxMovableBorder<mutable_>::BasicBoxMovableBorder(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		first_object_(make.first_object->make(init_info)),
		second_object_(make.second_object->make(init_info)),
		is_horizontal_border_(make.is_horizontal_border),
		border_value_(
			DynBuffer::get(std::move(make.border_value), SInitInfo{init_info}),
			[this](const float& value) {
				this->set_border_position(value);
			}
		) {
		border_value_.get().set_bounds(0, 1);
	}
	
	template<bool mutable_>
	auto BasicBoxMovableBorder<mutable_>::set_border_position(float value) -> void {
		resize(get_size(), get_position());
	}
	
	template<bool mutable_>
	auto BasicBoxMovableBorder<mutable_>::get_is_horizontal_border() -> bool {
		return is_horizontal_border_;
	}
	
	template<bool mutable_>
	auto BasicBoxMovableBorder<mutable_>::handle_event(Event event) -> bool {
		return event.pointer().map([=](event_system::Pointer pointer) {
			auto handle_event_objects{
				[=](float first_object_size, float position) {
					if(first_object_size > position) {
						return first_object_->handle_event(event);
					}
					return second_object_->handle_event(event);
				}
			};
			
			if(is_horizontal_border_) {
				return handle_event_objects(first_object_->get_size().x, pointer.position.x);
			}
			return handle_event_objects(first_object_->get_size().y, pointer.position.x);
		}).some_or_else([=] {
			auto first_updated{first_object_->handle_event(event)};
			auto second_updated{second_object_->handle_event(event)};
			return first_updated || second_updated;
		});
	}
	
	template<bool mutable_>
	auto BasicBoxMovableBorder<mutable_>::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		
		auto border_resize_fn{
			[this](float size, std::pair<float, float> min_sizes) -> std::pair<float, float> {
				auto border{border_value_.get().get()};
				auto result{std::pair<float, float>{border * size, (1 - border) * size}};
				if(result.first < min_sizes.first) {
					result.second -= min_sizes.first - result.first;
					result.first = min_sizes.first;
				} else if(result.second < min_sizes.second) {
					result.first -= min_sizes.second - result.second;
					result.second = min_sizes.second;
				}
				return {floor(result.first), ceil(result.second)};
			}
		};
		
		if(is_horizontal_border_) {
			auto child_size{border_resize_fn(size.y, {first_object_->get_min_size().y, second_object_->get_min_size().y})};
			first_object_->resize({size.x, child_size.first}, position);
			second_object_->resize({size.x, child_size.second}, {position.x, position.y + child_size.first});
		} else {
			auto child_size{border_resize_fn(size.x, {first_object_->get_min_size().x, second_object_->get_min_size().x})};
			first_object_->resize({child_size.first, size.y}, position);
			second_object_->resize({child_size.second, size.y}, {position.x + child_size.first, position.y});
		}
	}
	
	template<bool mutable_>
	auto BasicBoxMovableBorder<mutable_>::get_first_object() -> IScalable& {
		return *first_object_;
	}
	
	template<bool mutable_>
	auto BasicBoxMovableBorder<mutable_>::get_first_object() const -> IScalable const& {
		return *first_object_;
	}
	
	template<bool mutable_>
	auto BasicBoxMovableBorder<mutable_>::get_second_object() -> IScalable& {
		return *second_object_;
	}
	
	template<bool mutable_>
	auto BasicBoxMovableBorder<mutable_>::get_second_object() const -> IScalable const& {
		return *second_object_;
	}
	
	template<bool mutable_>
	auto BasicBoxMovableBorder<mutable_>::draw_debug(
		sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset
	) -> void {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		first_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}