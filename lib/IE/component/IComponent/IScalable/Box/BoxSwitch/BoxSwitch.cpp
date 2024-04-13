#include "BoxSwitch.hpp"

namespace ie {
	BoxSwitch::Make::Make(
		BoxPtr<IScalable::Make>&& inactive_object,
		BoxPtr<IScalable::Make>&& active_object,
		MakeDyn<ISBool> value,
		const sf::Vector2f& min_size
	) :
		inactive_object(std::move(inactive_object)), active_object(std::move(active_object)), value(std::move(value)), min_size(min_size) {
	}
	
	auto BoxSwitch::Make::make(InitInfo init_info) -> BoxSwitch* {
		return new BoxSwitch{std::move(*this), init_info};
	}
	
	BoxSwitch::BoxSwitch(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		inactive_object_(make.inactive_object->make(init_info.copy(inactive_draw_manager_))),
		active_object_(make.active_object->make(init_info.copy(active_draw_manager_))),
		value_(make.value.make(SInitInfo{init_info})) {
		init_info.draw_manager.add(*this);
	}
	
	auto BoxSwitch::set_position(sf::Vector2f position) -> void {
		layout_.set_position(position);
		inactive_object_->set_position(position);
		active_object_->set_position(position);
	}
	
	auto BoxSwitch::move(sf::Vector2f position) -> void {
		layout_.move(position);
		inactive_object_->move(position);
		active_object_->move(position);
	}
	
	auto BoxSwitch::set_size(sf::Vector2f size) -> void {
		layout_.set_size(size);
		inactive_object_->set_size(size);
		active_object_->set_size(size);
	}
	
	auto BoxSwitch::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		inactive_object_->resize(size, position);
		active_object_->resize(size, position);
	}
	
	auto BoxSwitch::draw() -> void {
		if(value_.get()) {
			active_draw_manager_.draw();
		} else {
			inactive_draw_manager_.draw();
		}
	}
	
	auto BoxSwitch::update_interactions(Event event) -> bool {
		return value_.get() ? active_object_->update_interactions(event) : inactive_object_->update_interactions(event);
	}
	
	auto BoxSwitch::get_first_object() -> IScalable& {
		return *inactive_object_;
	}
	
	auto BoxSwitch::get_first_object() const -> const IScalable& {
		return *inactive_object_;
	}
	
	auto BoxSwitch::get_second_object() -> IScalable& {
		return *active_object_;
	}
	
	auto BoxSwitch::get_second_object() const -> const IScalable& {
		return *active_object_;
	}
}

auto ieml::Decode<char, ie::BoxSwitch::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxSwitch::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxSwitch::Make{
		map.at("inactive-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("active-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("value").except().as<ie::MakeDyn<ie::ISBool> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({}),
	};
}
