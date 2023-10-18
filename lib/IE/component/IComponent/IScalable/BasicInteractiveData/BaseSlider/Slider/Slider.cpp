#include "Slider.hpp"

namespace ie {
	Slider::Make::Make(
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		const PSRVec2f& value,
		sf::Vector2f slider_scale,
		Key key,
		bool wheel_horizontal,
		SliderWheelAction::Relativity wheel_relativity,
		sf::Vector2f wheel_sensitivity
	) :
		slider(std::move(slider)),
		background(std::move(background)),
		value(value),
		slider_scale(slider_scale),
		key(key),
		wheel_horizontal(wheel_horizontal),
		wheel_relativity(wheel_relativity),
		wheel_sensitivity(wheel_sensitivity) {
	}
	
	Slider::Make::Make(
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		const PSRVec2f& value,
		sf::Vector2i division,
		sf::Vector2f slider_scale,
		Key key,
		bool wheel_horizontal
	) :
		slider(std::move(slider)),
		background(std::move(background)),
		value(value),
		division(division),
		slider_scale(slider_scale),
		key(key),
		wheel_horizontal(wheel_horizontal),
		wheel_relativity(SliderWheelAction::Relativity::RelationArea),
		wheel_sensitivity(1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)) {
	}
	
	Slider* Slider::Make::make(InitInfo init_info) {
		return new Slider{std::move(*this), init_info};
	}
	
	Slider::Slider(Make&& make, InitInfo init_info) :
		BaseSlider(
			std::move(make.slider),
			std::move(make.background),
			make_box_ptr<SliderInteraction::Make>(
				make.key, make.division, make.wheel_horizontal, make.wheel_relativity, make.wheel_sensitivity
			),
			make.value,
			init_info
		), scale(make.slider_scale) {
	}
	
	Slider::Slider(
		BoxPtr<IUninteractive>&& slider,
		BoxPtr<IUninteractive>&& background,
		const PSRVec2f& value,
		sf::Vector2f slider_scale,
		Key key,
		bool wheel_horizontal,
		SliderWheelAction::Relativity wheel_relativity,
		sf::Vector2f wheel_sensitivity
	) :
		BaseSlider(
			std::move(slider),
			std::move(background),
			make_box_ptr<SliderInteraction>(
				key, wheel_horizontal, wheel_relativity, wheel_sensitivity
			),
			value
		), scale(slider_scale) {
	}
	
	Slider::Slider(
		BoxPtr<IUninteractive>&& slider,
		BoxPtr<IUninteractive>&& background,
		const PSRVec2f& value,
		sf::Vector2i division,
		sf::Vector2f slider_scale,
		Key key,
		bool wheel_horizontal
	) :
		BaseSlider(
			std::move(slider),
			std::move(background),
			make_box_ptr<SliderInteraction>(
				key, division, wheel_horizontal
			),
			value
		), scale(slider_scale) {
	}
	
	void Slider::init(InitInfo init_info) {
		BaseSlider::init(init_info);
		interactive.init(init_info, *this);
	}
	
	void Slider::set_scale(sf::Vector2f scale) {
		this->scale = scale;
	}
	
	void Slider::resize(sf::Vector2f size, sf::Vector2f position) {
		this->position = position;
		slider_size = {size.x * scale.x, size.y * scale.y};
		move_zone_size = size - slider_size;
		background->resize(size, position);
		resize_slider(value->get_value());
	}
	
	sf::Vector2f Slider::get_min_size() const {
		sf::Vector2f min_size{slider->get_min_size()};
		min_size = {min_size.x / scale.x, min_size.y / scale.y};
		return max(min_size, background->get_min_size());
	}
	
	const IUninteractive& Slider::get_background() const {
		return *background;
	}
	
	const IUninteractive& Slider::get_slider() const {
		return *slider;
	}
	
	Slider* Slider::copy() {
		return new Slider{*this};
	}
	
	bool DecodePointer<Slider>::decode_pointer(const YAML::Node& node, Slider*& slider_zone) {
		auto slider{node["slider"].as<BoxPtr<IUninteractive> >()};
		auto background{node["background"].as<BoxPtr<IUninteractive> >()};
		auto value{Buffer::get<SRVec2f>(node["value"])};
		auto slider_scale{conv_def(node["slider-scale"], sf::Vector2f{1.0f, 0.5f})};
		auto key{conv_def(node["key"], Key::MouseLeft)};
		auto wheel_horizontal{conv_bool_def(node["default-wheel"], "horizontal", "vertical", false)};
		
		if(!node["division"]) {
			auto wheel_relativity{conv_def(node["wheel-relativity"], SliderWheelAction::Relativity::RelationArea)};
			auto wheel_sensitivity{conv_def(node["wheel-sensitivity"], sf::Vector2f{0.2f, 0.2f})};
			
			slider_zone = new Slider{std::move(slider), std::move(background), value, slider_scale, key, wheel_horizontal, wheel_relativity, wheel_sensitivity};
		} else {
			auto division{node["division"].as<sf::Vector2i>()};
			
			slider_zone = new Slider{std::move(slider), std::move(background), value, division, slider_scale, key, wheel_horizontal};
		}
		return true;
	}
}
