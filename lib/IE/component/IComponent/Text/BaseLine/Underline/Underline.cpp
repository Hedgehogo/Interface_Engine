#include "Underline.hpp"

namespace ie {
	Underline::Make::Make(orl::Option<sf::Color> color) : color(std::move(color)) {
	}
	
	auto Underline::Make::make(LineInitInfo init_info) -> Underline* {
		return new Underline{std::move(*this), init_info};
	}
	
	Underline::Underline(Make&& make, LineInitInfo init_info) :
		BaseLine(sf::TriangleStrip, 4, std::move(make.color), init_info),
		underline_offset_(init_info.font.getUnderlinePosition(init_info.size)),
		underline_thickness_(init_info.font.getUnderlineThickness(init_info.size)) {
	}

	auto Underline::resize(float start, float end, float height) -> void {
		vertex_array_[0].position = {start, height + underline_offset_ - (underline_thickness_ / 2)};
		vertex_array_[1].position = {start, height + underline_offset_ + (underline_thickness_ / 2)};
		vertex_array_[2].position = {end, height + underline_offset_ - (underline_thickness_ / 2)};
		vertex_array_[3].position = {end, height + underline_offset_ + (underline_thickness_ / 2)};
	}
	
	auto Underline::copy() const -> Underline* {
		return new Underline{*this};
	}
}

auto ieml::Decode<char, ie::Underline::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Underline::Make> {
	auto map{node.get_map_view().except()};
	return {{map.get_as<orl::Option<sf::Color> >("color").except().ok_or({})}};
}