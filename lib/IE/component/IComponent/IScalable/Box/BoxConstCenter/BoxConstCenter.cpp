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
		const_object_(make.const_object->make(init_info)),
		background_(make.background->make(init_info)),
		const_size_(make.const_size) {
	}
	
	auto BoxConstCenter::set_position(sf::Vector2f position) -> void {
		Box::set_position(position);
		if(resized_) {
			const_object_->move(const_size_);
		} else {
			resized_ = true;
			const_object_->resize(const_size_, layout_.position + position);
		}
		const_object_->set_position(position + (layout_.size / 2.f) - (const_size_ / 2.f));
		background_->set_position(position);
	}
	
	auto BoxConstCenter::move(sf::Vector2f position) -> void {
		Box::move(position);
		if(resized_) {
			const_object_->move(const_size_);
		} else {
			resized_ = true;
			const_object_->resize(const_size_, layout_.position + position);
		}
		background_->move(position);
	}
	
	auto BoxConstCenter::set_size(sf::Vector2f size) -> void {
		Box::set_size(size);
		if(!resized_) {
			resized_ = true;
			const_object_->set_size(const_size_);
		}
		background_->set_size(size);
	}
	
	auto BoxConstCenter::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		if(resized_) {
			const_object_->set_position(position + (size / 2.f) - (const_size_ / 2.f));
		} else {
			resized_ = true;
			const_object_->resize(const_size_, position + (size / 2.f) - (const_size_ / 2.f));
		}
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
	
	auto BoxConstCenter::update_interactions(Event event) -> bool {
		return event.touch().map([=](event_system::Touch touch) {
			if(const_object_->in(sf::Vector2f{touch.position})) {
				return const_object_->update_interactions(event);
			}
			return background_->update_interactions(event);
		}).some_or_else([=] {
			return const_object_->update_interactions(event) || background_->update_interactions(event);
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
