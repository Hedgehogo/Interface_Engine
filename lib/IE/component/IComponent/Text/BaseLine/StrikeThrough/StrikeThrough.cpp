#include "StrikeThrough.hpp"

namespace ie {
	StrikeThrough::MainLine::Make::Make(
		orl::Option<sf::Color> color,
		float strike_through_coefficient
	) :
		BaseLine::MainLine::Make(sf::TriangleStrip, 4, color),
		color(color),
		strike_through_coefficient(strike_through_coefficient) {
	}
	
	auto StrikeThrough::MainLine::Make::copy() -> Make* {
		return new Make{*this};
	}
	
	auto StrikeThrough::MainLine::Make::make(LineInitInfo init_info) -> MainLine* {
		return new MainLine{std::move(*this), init_info};
	}
	
	StrikeThrough::MainLine::MainLine(
		Make&& make,
		LineInitInfo init_info
	) :
		BaseLine::MainLine(make, init_info),
		strike_through_coefficient(make.strike_through_coefficient),
		strike_through_offset(make.strike_through_coefficient * init_info.size),
		underline_thickness(init_info.font.getUnderlineThickness(init_info.size)) {
	}
	
	auto StrikeThrough::MainLine::reinit(LineInitInfo init_info) -> void {
		BaseLine::MainLine::reinit(init_info);
		strike_through_offset = strike_through_coefficient * init_info.size;
		underline_thickness = init_info.font.getUnderlineThickness(init_info.size);
	}
	
	auto StrikeThrough::MainLine::copy() -> MainLine* {
		return new MainLine{*this};
	}
	
	auto StrikeThrough::MainLine::make() -> StrikeThrough* {
		return new StrikeThrough{std::move(*this)};
	}
	
	StrikeThrough::StrikeThrough(MainLine&& main_line) :
		BaseLine(main_line),
		strike_through_offset_(main_line.strike_through_offset),
		underline_thickness_(main_line.underline_thickness) {
	}
	
	auto StrikeThrough::resize(float start, float end, float height) -> void {
		vertex_array_[0].position = {start, height - strike_through_offset_ - (underline_thickness_ / 2)};
		vertex_array_[1].position = {start, height - strike_through_offset_ + (underline_thickness_ / 2)};
		vertex_array_[2].position = {end, height - strike_through_offset_ - (underline_thickness_ / 2)};
		vertex_array_[3].position = {end, height - strike_through_offset_ + (underline_thickness_ / 2)};
	}
	
	auto StrikeThrough::copy() const -> StrikeThrough* {
		return new StrikeThrough{*this};
	}
}

auto ieml::Decode<char, ie::StrikeThrough::MainLine::Make>::decode(ieml::Node const& node) -> orl::Option<ie::StrikeThrough::MainLine::Make> {
	if(node.is_map()) {
		auto map{node.get_map_view().except()};
		return ie::StrikeThrough::MainLine::Make{
			map.get_as<orl::Option<sf::Color> >("color").except().ok_or({}),
			map.get_as<float>("strike-through-coefficient").except().ok_or(0.3f),
		};
	} else if(node.is_null()) {
		return ie::StrikeThrough::MainLine::Make{};
	}
	return {};
}
