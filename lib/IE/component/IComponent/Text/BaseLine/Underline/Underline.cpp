#include "Underline.hpp"

namespace ie {
	Underline::Make::Make(const orl::Option<sf::Color>& color) : color(color) {
	}
	
	Underline* Underline::Make::make(LineInitInfo init_info) {
		return new Underline{std::move(*this), init_info};
	}
	
	Underline::Underline(Make&& make, LineInitInfo init_info) : BaseLine(sf::TriangleStrip, 4, make.color, init_info) {
		underline_offset = init_info.font.getUnderlinePosition(init_info.size);
		underline_thickness = init_info.font.getUnderlineThickness(init_info.size);
	}

	void Underline::resize(float start, float end, float height) {
		vertex_array[0].position = {start, height + underline_offset - (underline_thickness / 2)};
		vertex_array[1].position = {start, height + underline_offset + (underline_thickness / 2)};
		vertex_array[2].position = {end, height + underline_offset - (underline_thickness / 2)};
		vertex_array[3].position = {end, height + underline_offset + (underline_thickness / 2)};
	}
	
	Underline* Underline::copy() const{
		return new Underline{*this};
	}
}

orl::Option<ie::Underline::Make> ieml::Decode<char, ie::Underline::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::Underline::Make{
		map.get_as<orl::Option<sf::Color>>("color").ok_or({}),
	};
}