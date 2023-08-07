#include "constSlider.hpp"

namespace ui {
	ConstSlider::Make::Make(
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		const PSRVec2f& value,
		float sliderScale,
		Key key,
		bool wheelHorizontal,
		SliderWheelEvent::Relativity wheelRelativity,
		sf::Vector2f wheelSensitivity
	) :
		slider(std::move(slider)),
		background(std::move(background)),
		value(value),
		sliderScale(sliderScale),
		key(key),
		wheelHorizontal(wheelHorizontal),
		wheelRelativity(wheelRelativity),
		wheelSensitivity(wheelSensitivity) {
	}
	
	ConstSlider::Make::Make(
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		const PSRVec2f& value,
		sf::Vector2i division,
		float sliderScale,
		Key key,
		bool wheelHorizontal
	) :
		slider(std::move(slider)),
		background(std::move(background)),
		value(value),
		division(division),
		sliderScale(sliderScale),
		key(key),
		wheelHorizontal(wheelHorizontal),
		wheelRelativity(SliderWheelEvent::Relativity::relationArea),
		wheelSensitivity(1.0f / static_cast<float>(division.x), 1.0f / static_cast<float>(division.y)) {
	}
	
	ConstSlider* ConstSlider::Make::make(InitInfo initInfo) {
		return new ConstSlider{std::move(*this), initInfo};
	}
	
	float getAspectRatio(sf::Vector2f size) {
		return size.x / size.y;
	}
	
	ConstSlider::ConstSlider(Make&& make, InitInfo initInfo) :
		BaseSlider(std::move(make.slider), std::move(make.background), make.value, BoxPtr{
			new SliderInteraction{*this, make.key, make.division, make.wheelHorizontal, make.wheelRelativity, make.wheelSensitivity}
		}, initInfo),
		aspectRatio(getAspectRatio(slider->getNormalSize())),
		sliderScale(make.sliderScale) {
	}
	
	ConstSlider::ConstSlider(
		BoxPtr<IUninteractive>&& slider,
		BoxPtr<IUninteractive>&& background,
		const PSRVec2f& value,
		float sliderScale,
		Key key,
		bool wheelHorizontal,
		SliderWheelEvent::Relativity wheelRelativity,
		sf::Vector2f wheelSensitivity
	) :
		BaseSlider(
			std::move(slider), std::move(background), value,
			BoxPtr{new SliderInteraction{*this, key, wheelHorizontal, wheelRelativity, wheelSensitivity}}
		), sliderScale(sliderScale) {
		sliderSize = slider->getNormalSize();
		aspectRatio = sliderSize.x / sliderSize.y;
	}
	
	ConstSlider::ConstSlider(
		BoxPtr<IUninteractive>&& slider,
		BoxPtr<IUninteractive>&& background,
		const PSRVec2f& value,
		sf::Vector2i division,
		float sliderScale,
		Key key,
		bool wheelHorizontal
	) :
		BaseSlider(
			std::move(slider), std::move(background), value,
			BoxPtr{new SliderInteraction{*this, key, division, wheelHorizontal}}
		), sliderScale(sliderScale) {
		sliderSize = slider->getNormalSize();
		aspectRatio = sliderSize.x / sliderSize.y;
	}
	
	void ConstSlider::resize(sf::Vector2f size, sf::Vector2f position) {
		this->position = position;
		if(size.x / aspectRatio < size.y) {
			sliderSize = sf::Vector2f{size.x, size.x / aspectRatio} * sliderScale;
		} else {
			sliderSize = sf::Vector2f{size.y * aspectRatio, size.y} * sliderScale;
		}
		moveZoneSize = size - sliderSize;
		background->resize(size, position);
		resizeSlider(value->getValue());
	}
	
	ConstSlider* ConstSlider::copy() {
		return new ConstSlider{*this};
	}
	
	bool DecodePointer<ConstSlider>::decodePointer(const YAML::Node& node, ConstSlider*& constSlider) {
		auto slider{node["slider"].as<BoxPtr<IUninteractive> >()};
		auto background{node["background"].as<BoxPtr<IUninteractive> >()};
		auto value{Buffer::get<SRVec2f>(node["value"])};
		auto sliderScale{convDef(node["slider-scale"], 1.0f)};
		auto key{convDef(node["key"], Key::mouseLeft)};
		bool wheelHorizontal{convBoolDef(node["default-wheel"], "horizontal", "vertical", false)};
		
		if(!node["division"]) {
			auto wheelRelativity{convDef(node["wheel-relativity"], SliderWheelEvent::Relativity::relationArea)};
			auto wheelSensitivity{convDef(node["wheel-sensitivity"], sf::Vector2f{0.2f, 0.2f})};
			
			constSlider = new ConstSlider{std::move(slider), std::move(background), value, sliderScale, key, wheelHorizontal, wheelRelativity, wheelSensitivity};
		} else {
			auto division{node["division"].as<sf::Vector2i>()};
			
			constSlider = new ConstSlider{std::move(slider), std::move(background), value, division, sliderScale, key, wheelHorizontal};
		}
		return true;
	}
}
