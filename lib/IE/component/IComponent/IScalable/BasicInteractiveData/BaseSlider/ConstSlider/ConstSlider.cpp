#include "ConstSlider.hpp"

namespace ie {
	ConstSlider::Make::Make(
		BoxPtr<INonInteractive::Make>&& slider,
		BoxPtr<INonInteractive::Make>&& background,
		MakeDyn<ISMRVec2F> value,
		float slider_scale,
		Key key,
		bool wheel_horizontal,
		SliderWheelAction::Relativity wheel_relativity,
		sf::Vector2f wheel_sensitivity
	) :
		slider(std::move(slider)),
		background(std::move(background)),
		value(std::move(value)),
		slider_scale(slider_scale),
		key(key),
		wheel_horizontal(wheel_horizontal),
		wheel_relativity(wheel_relativity),
		wheel_sensitivity(wheel_sensitivity) {
	}
	
	ConstSlider::Make::Make(
		BoxPtr<INonInteractive::Make>&& slider,
		BoxPtr<INonInteractive::Make>&& background,
		MakeDyn<ISMRVec2F> value,
		sf::Vector2i division,
		float slider_scale,
		Key key,
		bool wheel_horizontal
	) :
		slider(std::move(slider)),
		background(std::move(background)),
		value(std::move(value)),
		division(division),
		slider_scale(slider_scale),
		key(key),
		wheel_horizontal(wheel_horizontal),
		wheel_relativity(SliderWheelAction::Relativity::RelationArea),
		wheel_sensitivity(1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)) {
	}
	
	ConstSlider* ConstSlider::Make::make(InitInfo init_info) {
		return new ConstSlider{std::move(*this), init_info};
	}
	
	float get_aspect_ratio(sf::Vector2f size) {
		return size.x / size.y;
	}
	
	ConstSlider::ConstSlider(Make&& make, InitInfo init_info) :
		BaseSlider(
			std::move(make.slider),
			std::move(make.background),
			make_box_ptr<SliderInteraction::Make>(
				make.key, make.division, make.wheel_horizontal, make.wheel_relativity, make.wheel_sensitivity
			),
			std::move(make.value),
			init_info
		),
		aspect_ratio_(get_aspect_ratio(max(slider_->get_normal_size(), {1, 1}))),
		slider_scale_(make.slider_scale) {
	}
	
	void ConstSlider::resize(sf::Vector2f size, sf::Vector2f position) {
		this->position_ = position;
		if(size.x / aspect_ratio_ < size.y) {
			slider_size_ = sf::Vector2f{size.x, size.x / aspect_ratio_} * slider_scale_;
		} else {
			slider_size_ = sf::Vector2f{size.y * aspect_ratio_, size.y} * slider_scale_;
		}
		move_zone_size_ = size - slider_size_;
		background_->resize(size, position);
		resize_slider(value_.get().get());
	}
}

orl::Option<ie::ConstSlider::Make> ieml::Decode<char, ie::ConstSlider::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	auto slider{map.at("slider").except().as < ie::BoxPtr < ie::INonInteractive::Make > > ().except()};
	auto background{map.at("background").except().as < ie::BoxPtr < ie::INonInteractive::Make > > ().except()};
	auto value{map.at("value").except().as<ie::MakeDyn<ie::ISMRVec2F> >().except()};
	auto slider_scale{map.get_as<float>("slider-scale").ok_or(1.0)};
	auto key{map.get_as<ie::Key>("key").ok_or(ie::Key::MouseLeft)};
	bool wheel_horizontal{map.get_as<bool>("wheel-horizontal").ok_or(false)};
	for(auto& division_node: map.at("division").ok_or_none()) {
		auto division{division_node.as<sf::Vector2i>().except()};
		return {{std::move(slider), std::move(background), std::move(value), division, slider_scale, key, wheel_horizontal}};
	}
	return ie::ConstSlider::Make{
		std::move(slider),
		std::move(background),
		std::move(value),
		slider_scale,
		key,
		wheel_horizontal,
		map.get_as<ie::SliderWheelAction::Relativity>("wheel-relativity").ok_or(ie::SliderWheelAction::Relativity::RelationArea),
		map.get_as<sf::Vector2f>("wheel-sensitivity").ok_or({0.2, 0.2})
	};
}
