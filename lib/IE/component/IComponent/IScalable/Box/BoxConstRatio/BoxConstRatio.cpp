#include "BoxConstRatio.hpp"

namespace ie {
	BoxConstRatio::Make::Make(
		BoxPtr<IScalable::Make>&& const_object,
		BoxPtr<IScalable::Make>&& second_object,
		BoxPtr<INonInteractive::Make>&& background,
		float aspect_ratio,
		Corner corner,
		sf::Vector2f min_size
	) :
		const_object(std::move(const_object)),
		second_object(std::move(second_object)),
		background(std::move(background)),
		aspect_ratio(aspect_ratio),
		corner(corner),
		min_size(min_size) {
	}
	
	auto BoxConstRatio::Make::make(InitInfo init_info) -> BoxConstRatio* {
		return new BoxConstRatio{std::move(*this), init_info};
	}
	
	BoxConstRatio::BoxConstRatio(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		background_(make.background->make(init_info)),
		const_object_(make.const_object->make(init_info)),
		second_object_(make.second_object->make(init_info.copy(second_draw_manager_))),
		vertical_side_(make.corner == Corner::UpLeft || make.corner == Corner::UpRight),
		horizontal_side_(make.corner == Corner::UpLeft || make.corner == Corner::DownLeft),
		render_second_(true),
		aspect_ratio_(make.aspect_ratio) {
		init_info.draw_manager.add(*this);
	}
	
	auto BoxConstRatio::get_corner() -> Corner {
		if(vertical_side_) {
			if(horizontal_side_) {
				return Corner::UpLeft;
			}
			return Corner::UpRight;
		} else {
			if(horizontal_side_) {
				return Corner::DownLeft;
			}
			return Corner::DownRight;
		}
	}
	
	auto BoxConstRatio::draw() -> void {
		if(render_second_) {
			second_draw_manager_.draw();
		}
	}
	
	auto BoxConstRatio::set_position(sf::Vector2f position) -> void {
		BoxConstRatio::move(position - layout_.position);
	}
	
	auto BoxConstRatio::move(sf::Vector2f offset) -> void {
		layout_.move(offset);
		background_->move(offset);
		const_object_->move(offset);
		second_object_->move(offset);
	}
	
	auto BoxConstRatio::set_size(sf::Vector2f size) -> void {
		resize(size, layout_.position);
	}
	
	auto BoxConstRatio::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		
		auto const_size{
			size.x / size.y > aspect_ratio_ ?
			sf::Vector2f{size.y * aspect_ratio_, size.y} :
			sf::Vector2f{size.x, size.x / aspect_ratio_}
		};
		auto second_size{
			size.x / size.y > aspect_ratio_ ?
			sf::Vector2f{size.x - const_size.x, size.y} :
			sf::Vector2f{size.x, size.y - const_size.y}
		};
		
		auto const_position{sf::Vector2f{0, 0}};
		auto second_position{sf::Vector2f{0, 0}};
		
		auto second_min_size{second_object_->get_min_size()};
		render_second_ = second_size.x > second_min_size.x && second_size.y > second_min_size.y;
		if(render_second_) {
			if(size.x / size.y > aspect_ratio_) {
				if(horizontal_side_) {
					second_position.x = const_size.x;
				} else {
					const_position.x = second_size.x;
				}
			} else {
				if(vertical_side_) {
					second_position.y = const_size.y;
				} else {
					const_position.y = second_size.y;
				}
			}
		} else {
			const_position = (layout_.size - const_size) / 2.0f;
		}
		
		const_position += position;
		second_position += position;
		
		const_object_->resize(const_size, const_position);
		second_object_->resize(second_size, second_position);
		background_->resize(size, position);
	}
	
	auto BoxConstRatio::handle_event(Event event) -> bool {
		return event.pointer().map([=](event_system::Pointer pointer) {
			if(render_second_ && second_object_->in_area(sf::Vector2f{pointer.position})) {
				return second_object_->handle_event(event);
			}
			if(const_object_->in_area(sf::Vector2f{pointer.position})) {
				return const_object_->handle_event(event);
			}
			return background_->handle_event(event);
		}).some_or_else([=] {
			auto second_updated{render_second_ && second_object_->handle_event(event)};
			auto const_updated{const_object_->handle_event(event)};
			auto background{background_->handle_event(event)};
			return second_updated || const_updated || background;
		});
	}
	
	auto BoxConstRatio::get_min_size() const -> sf::Vector2f {
		auto const_min_size{const_object_->get_min_size()};
		const_min_size = {
			std::max(const_min_size.x, const_min_size.y * aspect_ratio_),
			std::max(const_min_size.y, const_min_size.x / aspect_ratio_)
		};
		return max(const_min_size, background_->get_min_size(), minimum_size_);
	}
	
	auto BoxConstRatio::get_normal_size() const -> sf::Vector2f {
		auto const_normal_size{const_object_->get_normal_size()};
		auto second_normal_size{second_object_->get_normal_size()};
		//sf::Vector2f normal_size{std::max(const_normal_size.x, const_normal_size.y * aspect_ratio), std::max(const_normal_size.y, const_normal_size.x / aspect_ratio)};
		auto normal_size{sf::Vector2f{const_normal_size.x + second_normal_size.x, std::max(const_normal_size.y, second_normal_size.y)}};
		return max(normal_size, background_->get_normal_size());
	}
	
	auto BoxConstRatio::get_background() -> INonInteractive& {
		return *background_;
	}
	
	auto BoxConstRatio::get_background() const -> const INonInteractive& {
		return *background_;
	}
	
	auto BoxConstRatio::get_first_object() -> IScalable& {
		return *const_object_;
	}
	
	auto BoxConstRatio::get_first_object() const -> IScalable const& {
		return *const_object_;
	}
	
	auto BoxConstRatio::get_second_object() -> IScalable& {
		return *second_object_;
	}
	
	auto BoxConstRatio::get_second_object() const -> IScalable const& {
		return *second_object_;
	}
	
	auto BoxConstRatio::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		const_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}

auto ieml::Decode<char, ie::BoxConstRatio::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxConstRatio::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxConstRatio::Make{
		map.at("const-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("second-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<ie::BoxPtr<ie::INonInteractive::Make> >("background").except().ok_or_else([] {
			return ie::make_box_ptr<ie::INonInteractive::Make, ie::Empty::Make>();
		}),
		map.at("aspect-ratio").except().as<float>().except(),
		map.get_as<ie::Corner>("corner").except().ok_or(ie::Corner::UpLeft),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
