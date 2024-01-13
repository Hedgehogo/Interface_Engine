#include "ConstSlider.hpp"

namespace ie {
	ConstSlider::Make::Make(
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		MakeDyn<SRVec2F> value,
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
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		MakeDyn<SRVec2F> value,
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
	
	void ConstSlider::init(InitInfo init_info) {
		BaseSlider::init(init_info);
		interactive_.init(init_info, *this);
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
	
	ConstSlider* ConstSlider::copy() {
		return nullptr;
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<ConstSlider>::decode_pointer(const YAML::Node& node, ConstSlider*& const_slider) {
		auto slider{node["slider"].as<BoxPtr<IUninteractive> >()};
		auto background{node["background"].as<BoxPtr<IUninteractive> >()};
		auto value{Buffer::get<SRVec2f>(node["value"])};
		auto slider_scale{conv_def(node["slider-scale"], 1.0f)};
		auto key{conv_def(node["key"], Key::MouseLeft)};
		bool wheel_horizontal{conv_bool_def(node["default-wheel"], "horizontal", "vertical", false)};
		
		if(!node["division"]) {
			auto wheel_relativity{conv_def(node["wheel-relativity"], SliderWheelAction::Relativity::RelationArea)};
			auto wheel_sensitivity{conv_def(node["wheel-sensitivity"], sf::Vector2f{0.2f, 0.2f})};
			
			const_slider = new ConstSlider{std::move(slider), std::move(background), value, slider_scale, key, wheel_horizontal, wheel_relativity, wheel_sensitivity};
		} else {
			auto division{node["division"].as<sf::Vector2i>()};
			
			const_slider = new ConstSlider{std::move(slider), std::move(background), value, division, slider_scale, key, wheel_horizontal};
		}
		return true;

	}
	*/
}
