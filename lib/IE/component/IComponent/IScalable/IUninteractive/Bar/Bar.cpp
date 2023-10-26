#include <cmath>
#include "Bar.hpp"

namespace ie {
	Bar::Make::Make(BoxPtr<IUninteractive::Make>&& background, BoxPtr<IUninteractive::Make>&& strip, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), offset(offset), horizontal(horizontal), division(1) {
	}
	
	Bar::Make::Make(BoxPtr<IUninteractive::Make>&& background, BoxPtr<IUninteractive::Make>&& strip, int division, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), offset(offset), horizontal(horizontal), division(division) {
	}
	
	Bar* Bar::Make::make(InitInfo init_info) {
		return new Bar{std::move(*this), init_info};
	}
	
	Bar::Bar(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		background(make.background->make(init_info)),
		strip(make.strip->make(init_info)),
		horizontal(make.horizontal),
		offset(make.offset),
		division(make.division),
		value(0) {
	}
	
	Bar::Bar(BoxPtr<IUninteractive>&& background, BoxPtr<IUninteractive>&& strip, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), horizontal(horizontal), offset(offset), division(1), value(0) {
	}
	
	Bar::Bar(BoxPtr<IUninteractive>&& background, BoxPtr<IUninteractive>&& strip, int division, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), horizontal(horizontal), offset(offset), division(division), value(0) {
	}
	
	void Bar::init(InitInfo init_info) {
		background->init(init_info);
		strip->init(init_info);
	}
	
	float Bar::get_value() {
		return value;
	}
	
	void Bar::set_value(float value) {
		this->value = value;
		if(this->division > 1) {
			this->value = std::round(this->value);
		}
		sf::Vector2f strip_size{layout.size};
		if(horizontal) {
			strip_size.x = offset * layout.size.y;
			strip_size.x += (layout.size.x - strip_size.x) * this->value / static_cast<float>(division);
		} else {
			strip_size.y = offset * layout.size.x;
			strip_size.y += (layout.size.y - strip_size.y) * this->value / static_cast<float>(division);
		}
		strip->resize(strip_size, layout.position);
	}
	
	void Bar::draw() {
	}
	
	void Bar::resize(sf::Vector2f size, sf::Vector2f position) {
		IComponentBackground::resize(size, position);
		set_value(value);
	}
	
	sf::Vector2f Bar::get_min_size() const {
		sf::Vector2f strip_min_size{strip->get_min_size()};
		(horizontal ? strip_min_size.x : strip_min_size.y) *= value;
		return max(strip_min_size, background->get_min_size());
	}
	
	sf::Vector2f Bar::get_normal_size() const {
		sf::Vector2f strip_normal_size{strip->get_normal_size()};
		(horizontal ? strip_normal_size.x : strip_normal_size.y) *= value;
		return max(strip_normal_size, background->get_normal_size());
	}
	
	IUninteractive& Bar::get_background() {
		return *background;
	}
	
	const IUninteractive& Bar::get_background() const {
		return *background;
	}
	
	Bar* Bar::copy() {
		return new Bar{*this};
	}
	
	void Bar::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		strip->draw_debug(render_target, indent + indent_addition, indent_addition, hue, hue_offset);
	}
	
	LayoutData& Bar::layout_get_data() {
		return layout;
	}
	
	const LayoutData& Bar::layout_get_data() const {
		return layout;
	}
	
	bool DecodePointer<Bar>::decode_pointer(const YAML::Node& node, Bar*& bar) {
		bar = new Bar{
			node["background"].as<BoxPtr<IUninteractive> >(),
			node["strip"].as<BoxPtr<IUninteractive> >(),
			conv_def(node["division"], 1),
			conv_def(node["offset"], 0.0f),
			conv_def(node["offset"], true)
		};
		return true;
	}
}
