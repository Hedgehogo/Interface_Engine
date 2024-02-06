#include "StrikeThrough.hpp"

namespace ie {
	StrikeThrough::Make::Make(const orl::Option<sf::Color>& color, float strike_through_offset) : color(color), strike_through_offset(strike_through_offset) {
	}
	
	BaseLine* StrikeThrough::Make::make(LineInitInfo init_info) {
		return new StrikeThrough{std::move(*this), init_info};
	}
	
	StrikeThrough::StrikeThrough(Make&& make, LineInitInfo init_info) : BaseLine(sf::TriangleStrip, 4, make.color, init_info), strike_through_offset(make.strike_through_offset) {
		strike_through_offset *= init_info.size;
		underline_thickness = init_info.font.getUnderlineThickness(init_info.size);
	}
	
	void StrikeThrough::resize(float start, float end, float height) {
		vertex_array[0].position = {start, height - strike_through_offset - (underline_thickness / 2)};
		vertex_array[1].position = {start, height - strike_through_offset + (underline_thickness / 2)};
		vertex_array[2].position = {end, height - strike_through_offset - (underline_thickness / 2)};
		vertex_array[3].position = {end, height - strike_through_offset + (underline_thickness / 2)};
	}
	
	StrikeThrough* StrikeThrough::copy() const{
		return new StrikeThrough{*this};
	}
}

orl::Option<ie::StrikeThrough::Make> ieml::Decode<char, ie::StrikeThrough::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::StrikeThrough::Make{
		map.get_as<orl::Option<sf::Color>>("color").ok_or({}),
		map.get_as<float>("strike-through-offset").ok_or(0.3f),
	};
}
