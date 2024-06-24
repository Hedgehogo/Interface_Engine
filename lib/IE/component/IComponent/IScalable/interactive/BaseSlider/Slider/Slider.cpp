#include "Slider.hpp"

namespace ie {
	Slider::Make::Make(
		BoxPtr<INonInteractive::Make>&& slider,
		BoxPtr<INonInteractive::Make>&& background,
		MakeDyn<ISMRVec2F> value,
		sf::Vector2f slider_scale,
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
	
	Slider::Make::Make(
		BoxPtr<INonInteractive::Make>&& slider,
		BoxPtr<INonInteractive::Make>&& background,
		MakeDyn<ISMRVec2F> value,
		sf::Vector2i division,
		sf::Vector2f slider_scale,
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
	
	auto Slider::Make::make(InitInfo init_info) -> Slider* {
		return new Slider{std::move(*this), init_info};
	}
	
	Slider::Slider(Make&& make, InitInfo init_info) :
		BaseSlider(
			std::move(make.slider),
			std::move(make.background),
			SliderInteraction::Make{make.key, make.division, make.wheel_horizontal, make.wheel_relativity, make.wheel_sensitivity},
			std::move(make.value),
			init_info
		), scale_(make.slider_scale) {
	}
	
	auto Slider::set_scale(sf::Vector2f scale) -> void {
		this->scale_ = scale;
	}
	
	auto Slider::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		this->position_ = position;
		slider_size_ = {size.x * scale_.x, size.y * scale_.y};
		move_zone_size_ = size - slider_size_;
		background_->resize(size, position);
		resize_slider(value_.get().get());
	}
	
	auto Slider::get_min_size() const -> sf::Vector2f {
		auto min_size{slider_->get_min_size()};
		min_size = {min_size.x / scale_.x, min_size.y / scale_.y};
		return max(min_size, background_->get_min_size());
	}
	
	auto Slider::get_background() const -> INonInteractive const& {
		return *background_;
	}
	
	auto Slider::get_slider() const -> INonInteractive const& {
		return *slider_;
	}
}

auto ieml::Decode<char, ie::Slider::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Slider::Make> {
	auto map{node.get_map_view().except()};
	auto slider{map.at("slider").except().as<ie::BoxPtr<ie::INonInteractive::Make> >().except()};
	auto background{map.at("background").except().as<ie::BoxPtr<ie::INonInteractive::Make> >().except()};
	auto value{map.at("value").except().as<ie::MakeDyn<ie::ISMRVec2F> >().except()};
	auto slider_scale{map.get_as<sf::Vector2f>("slider-scale").except().ok_or({1.0f, 0.5f})};
	auto key{map.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft)};
	auto wheel_horizontal{map.get_as<bool>("wheel-horizontal").except().ok_or(false)};
	for(auto& division_node: map.at("division").ok_or_none()) {
		auto division{division_node.as<sf::Vector2i>().except()};
		return ie::Slider::Make{
			std::move(slider), std::move(background), std::move(value), division, slider_scale, key, wheel_horizontal
		};
	}
	auto wheel_relativity{
		map.get_as<ie::SliderWheelAction::Relativity>("wheel-relativity").except().ok_or(ie::SliderWheelAction::Relativity::RelationArea)
	};
	auto wheel_sensitivity{map.get_as<sf::Vector2f>("wheel-sensitivity").except().ok_or({0.2f, 0.2f})};
	return ie::Slider::Make{
		std::move(slider), std::move(background), std::move(value), slider_scale, key, wheel_horizontal, wheel_relativity, wheel_sensitivity
	};
}
