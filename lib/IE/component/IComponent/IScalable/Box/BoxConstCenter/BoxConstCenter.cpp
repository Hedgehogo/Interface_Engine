#include "BoxConstCenter.hpp"

namespace ie {
	BoxConstCenter::Make::Make(
		BoxPtr<IScalable::Make>&& const_object,
		BoxPtr<IScalable::Make>&& background,
		sf::Vector2f const_size,
		sf::Vector2f min_size
	) :
		const_object(std::move(const_object)), background(std::move(background)), const_size(const_size), min_size(min_size) {
	}
	
	auto BoxConstCenter::Make::make(InitInfo init_info) -> BoxConstCenter* {
		return new BoxConstCenter{std::move(*this), init_info};
	}
	
	BoxConstCenter::BoxConstCenter(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		background_(make.background->make(init_info)),
		const_object_(make.const_object->make(init_info)),
		const_size_(make.const_size) {
	}
	
	auto BoxConstCenter::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		const_object_->resize(const_size_, position + (size / 2.f) - (const_size_ / 2.f));
		background_->resize(size, position);
	}
	
	auto BoxConstCenter::get_min_size() const -> sf::Vector2f {
		return max(IComponentTwoObjects::get_min_size(), const_size_);
	}
	
	auto BoxConstCenter::get_normal_size() const -> sf::Vector2f {
		return max(IComponentTwoObjects::get_normal_size(), const_size_);
	}
	
	auto BoxConstCenter::get_first_object() -> IScalable& {
		return *const_object_;
	}
	
	auto BoxConstCenter::get_first_object() const -> IScalable const& {
		return *const_object_;
	}
	
	auto BoxConstCenter::get_second_object() -> IScalable& {
		return *background_;
	}
	
	auto BoxConstCenter::get_second_object() const -> IScalable const& {
		return *background_;
	}
	
	auto BoxConstCenter::handle_event(Event event) -> bool {
		return event.pointer().map([=](event_system::Pointer pointer) {
			if(const_object_->in(sf::Vector2f{pointer.position})) {
				return const_object_->handle_event(event);
			}
			return background_->handle_event(event);
		}).some_or_else([=] {
			return const_object_->handle_event(event) || background_->handle_event(event);
		});
	}
}

auto ieml::Decode<char, ie::BoxConstCenter::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxConstCenter::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxConstCenter::Make{
		map.at("const-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("background").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("const-size").except().as<sf::Vector2f>().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
