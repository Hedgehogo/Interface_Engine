#include "StrikeThrough.hpp"

namespace ie {
	StrikeThrough::Make::Make(orl::Option<sf::Color> color, float strike_through_offset) :
		color(std::move(color)), strike_through_offset(strike_through_offset) {
	}
	
	auto StrikeThrough::Make::copy() -> StrikeThrough::Make* {
		return new Make{*this};
	}
	
	auto StrikeThrough::Make::make(LineInitInfo init_info) -> BaseLine* {
		return new StrikeThrough{std::move(*this), init_info};
	}
	
	StrikeThrough::StrikeThrough(Make&& make, LineInitInfo init_info) :
		BaseLine(sf::TriangleStrip, 4, std::move(make.color), init_info),
		strike_through_offset_(make.strike_through_offset * init_info.size),
		underline_thickness_(init_info.font.getUnderlineThickness(init_info.size)) {
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

auto ieml::Decode<char, ie::StrikeThrough::Make>::decode(ieml::Node const& node) -> orl::Option<ie::StrikeThrough::Make> {
	auto map{node.get_map_view().except()};
	return ie::StrikeThrough::Make{
		map.get_as<orl::Option<sf::Color> >("color").except().ok_or({}),
		map.get_as<float>("strike-through-offset").except().ok_or(0.3f),
	};
}
