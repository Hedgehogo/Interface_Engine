#include "BoxConstRatioCenter.hpp"

namespace ie {
	BoxConstRatioCenter::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<INonInteractive::Make>&& background,
		float aspect_ratio,
		sf::Vector2f min_size
	) :
		object(std::move(object)),
		first_object(new Empty::Make),
		second_object(new Empty::Make),
		background(std::move(background)),
		aspect_ratio(aspect_ratio),
		min_size(min_size) {
	}
	
	BoxConstRatioCenter::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<IScalable::Make>&& first_object,
		BoxPtr<IScalable::Make>&& second_object,
		BoxPtr<INonInteractive::Make>&& background,
		float aspect_ratio,
		sf::Vector2f min_size
	) :
		object(std::move(object)),
		first_object(std::move(first_object)),
		second_object(std::move(second_object)),
		background(std::move(background)),
		aspect_ratio(aspect_ratio),
		min_size(min_size) {
	}
	
	auto BoxConstRatioCenter::Make::make(InitInfo init_info) -> BoxConstRatioCenter* {
		return new BoxConstRatioCenter{std::move(*this), init_info};
	}
	
	BoxConstRatioCenter::BoxConstRatioCenter(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		background_(make.background->make(init_info)),
		object_(make.object->make(init_info)),
		first_object_(make.first_object->make(init_info.copy(first_draw_manager_))),
		second_object_(make.second_object->make(init_info.copy(second_draw_manager_))),
		aspect_ratio_(make.aspect_ratio) {
		init_info.draw_manager.add(*this);
	}
	
	auto BoxConstRatioCenter::set_aspect_ratio(float aspect_ratio) -> void {
		this->aspect_ratio_ = aspect_ratio;
		this->set_position(layout_.position);
	}
	
	auto BoxConstRatioCenter::set_position(sf::Vector2f position) -> void {
		BoxConstRatioCenter::move(position - layout_.position);
	}
	
	auto BoxConstRatioCenter::move(sf::Vector2f offset) -> void {
		layout_.move(offset);
		object_->move(offset);
		background_->move(offset);
		first_object_->move(offset);
		second_object_->move(offset);
	}
	
	auto BoxConstRatioCenter::set_size(sf::Vector2f size) -> void {
		resize(size, layout_.position);
	}
	
	auto BoxConstRatioCenter::draw() -> void {
		if(render_first_) {
			first_draw_manager_.draw();
		}
		if(render_second_) {
			second_draw_manager_.draw();
		}
	}
	
	auto BoxConstRatioCenter::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		
		auto first_min_size{first_object_->get_min_size()};
		auto second_min_size{second_object_->get_min_size()};
		auto second_position{position};
		auto objects_size{size};
		
		background_->resize(size, position);
		auto size_aspect_ratio = size.x / size.y;
		if(size_aspect_ratio > aspect_ratio_) {
			size.x = size.y * aspect_ratio_;
			objects_size.x = (layout_.size.x - size.x) / 2.0f;
			second_position.x += objects_size.x + size.x;
		} else {
			size.y = size.x / aspect_ratio_;
			objects_size.y = (layout_.size.y - size.y) / 2.0f;
			second_position.y += objects_size.y + size.y;
		}
		render_first_ = first_min_size.x < objects_size.x && first_min_size.y < objects_size.y;
		render_second_ = second_min_size.x < objects_size.x && second_min_size.y < objects_size.y;
		
		object_->resize(size, position + (layout_.size - size) / 2.0f);
		
		if(render_first_)
			first_object_->resize(objects_size, position);
		if(render_second_)
			second_object_->resize(objects_size, second_position);
	}
	
	auto BoxConstRatioCenter::update_interactions(Event event) -> bool {
		return event.touch().map([=](event_system::Touch touch) {
			if(object_->in_area(sf::Vector2f{touch.position})) {
				return object_->update_interactions(event);
			}
			if(render_first_ && first_object_->in_area(sf::Vector2f{touch.position})) {
				return first_object_->update_interactions(event);
			}
			if(render_second_ && second_object_->in_area(sf::Vector2f{touch.position})) {
				return second_object_->update_interactions(event);
			}
			return background_->update_interactions(event);
		}).some_or_else([=] {
			auto object_updated{object_->update_interactions(event)};
			auto first_updated{render_first_ && first_object_->update_interactions(event)};
			auto second_updated{render_second_ && second_object_->update_interactions(event)};
			auto background_updated{background_->update_interactions(event)};
			return object_updated || first_updated || second_updated || background_updated;
		});
	}
	
	auto BoxConstRatioCenter::get_min_size() const -> sf::Vector2f {
		auto object_min_size{object_->get_min_size()};
		object_min_size = {
			std::max(object_min_size.x, object_min_size.y * aspect_ratio_),
			std::max(object_min_size.y, object_min_size.x / aspect_ratio_)
		};
		return max(object_min_size, background_->get_min_size(), minimum_size_);
	}
	
	auto BoxConstRatioCenter::get_normal_size() const -> sf::Vector2f {
		auto object_normal_size{object_->get_normal_size()};
		object_normal_size = {
			std::max(object_normal_size.x, object_normal_size.y * aspect_ratio_),
			std::max(object_normal_size.y, object_normal_size.x / aspect_ratio_)
		};
		return max(object_normal_size, background_->get_normal_size());
	}
	
	auto BoxConstRatioCenter::get_background() -> INonInteractive& {
		return *background_;
	}
	
	auto BoxConstRatioCenter::get_background() const -> INonInteractive const& {
		return *background_;
	}
	
	auto BoxConstRatioCenter::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BoxConstRatioCenter::get_object() const -> IScalable const& {
		return *object_;
	}
	
	auto BoxConstRatioCenter::get_first_object() -> IScalable& {
		return *first_object_;
	}
	
	auto BoxConstRatioCenter::get_first_object() const -> IScalable const& {
		return *first_object_;
	}
	
	auto BoxConstRatioCenter::get_second_object() -> IScalable& {
		return *second_object_;
	}
	
	auto BoxConstRatioCenter::get_second_object() const -> IScalable const& {
		return *second_object_;
	}
	
	auto BoxConstRatioCenter::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		first_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}

auto ieml::Decode<char, ie::BoxConstRatioCenter::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxConstRatioCenter::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxConstRatioCenter::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<ie::BoxPtr<ie::IScalable::Make> >("first-object").except().ok_or_else([] {
			return ie::make_box_ptr<ie::IScalable::Make, ie::Empty::Make>();
		}),
		map.get_as<ie::BoxPtr<ie::IScalable::Make> >("second-object").except().ok_or_else([] {
			return ie::make_box_ptr<ie::IScalable::Make, ie::Empty::Make>();
		}),
		map.get_as<ie::BoxPtr<ie::INonInteractive::Make> >("background").except().ok_or_else([] {
			return ie::make_box_ptr<ie::INonInteractive::Make, ie::Empty::Make>();
		}),
		map.at("aspect-ratio").except().as<float>().except(),
		map.at("min-size").except().as<sf::Vector2f>().except(),
	};
}
