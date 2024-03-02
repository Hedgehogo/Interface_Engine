#include <cmath>
#include "Bar.hpp"

namespace ie {
	Bar::Make::Make(BoxPtr<INonInteractive::Make>&& background, BoxPtr<INonInteractive::Make>&& strip, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), offset(offset), horizontal(horizontal), division(1) {
	}
	
	Bar::Make::Make(BoxPtr<INonInteractive::Make>&& background, BoxPtr<INonInteractive::Make>&& strip, int division, float offset, bool horizontal) :
		background(std::move(background)), strip(std::move(strip)), offset(offset), horizontal(horizontal), division(division) {
	}
	
	auto Bar::Make::make(InitInfo init_info) -> Bar* {
		return new Bar{std::move(*this), init_info};
	}
	
	Bar::Bar(Make&& make, InitInfo init_info) :
		background_(make.background->make(init_info)),
		strip_(make.strip->make(init_info)),
		horizontal_(make.horizontal),
		offset_(make.offset),
		division_(make.division),
		value_(0) {
	}
	
	auto Bar::get_value() -> float {
		return value_;
	}
	
	auto Bar::set_value(float value) -> void {
		this->value_ = value;
		if(this->division_ > 1) {
			this->value_ = std::round(this->value_);
		}
		auto strip_size{sf::Vector2f{layout_.size}};
		if(horizontal_) {
			strip_size.x = offset_ * layout_.size.y;
			strip_size.x += (layout_.size.x - strip_size.x) * this->value_ / static_cast<float>(division_);
		} else {
			strip_size.y = offset_ * layout_.size.x;
			strip_size.y += (layout_.size.y - strip_size.y) * this->value_ / static_cast<float>(division_);
		}
		strip_->resize(strip_size, layout_.position);
	}
	
	auto Bar::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		IComponentBackground::resize(size, position);
		set_value(value_);
	}
	
	auto Bar::get_min_size() const -> sf::Vector2f {
		sf::Vector2f strip_min_size{strip_->get_min_size()};
		(horizontal_ ? strip_min_size.x : strip_min_size.y) *= value_;
		return max(strip_min_size, background_->get_min_size());
	}
	
	auto Bar::get_normal_size() const -> sf::Vector2f {
		sf::Vector2f strip_normal_size{strip_->get_normal_size()};
		(horizontal_ ? strip_normal_size.x : strip_normal_size.y) *= value_;
		return max(strip_normal_size, background_->get_normal_size());
	}
	
	auto Bar::get_background() -> INonInteractive& {
		return *background_;
	}
	
	auto Bar::get_background() const -> INonInteractive const& {
		return *background_;
	}
	
	auto Bar::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		strip_->draw_debug(render_target, indent + indent_addition, indent_addition, hue, hue_offset);
	}
	
	auto Bar::layout_get_data() -> LayoutData& {
		return layout_;
	}
	
	auto Bar::layout_get_data() const -> LayoutData const& {
		return layout_;
	}
}

auto ieml::Decode<char, ie::Bar::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Bar::Make> {
	auto map{node.get_map_view().except()};
	return ie::Bar::Make{
		map.at("background").except().as<ie::BoxPtr<ie::INonInteractive::Make> >().except(),
		map.at("strip").except().as<ie::BoxPtr<ie::INonInteractive::Make> >().except(),
		map.get_as<int>("division").except().ok_or(1),
		map.get_as<float>("offset").except().ok_or(0.0),
		map.get_as<bool>("offset").except().ok_or(true),
	};
}
