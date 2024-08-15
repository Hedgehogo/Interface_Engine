#include "Underline.hpp"

namespace ie {
	Underline::MainLine::Make::Make(orl::Option<sf::Color> color) : BaseLine::MainLine::Make(sf::TriangleStrip, 4, color){
	}
	
	auto Underline::MainLine::Make::copy() -> Make* {
		return new Make{*this};
	}
	
	auto Underline::MainLine::Make::make(LineInitInfo init_info) -> MainLine* {
		return new MainLine{std::move(*this), init_info};
	}
	
	Underline::MainLine::MainLine(
		Make&& make,
		LineInitInfo init_info
	) :
		BaseLine::MainLine(make, init_info),
		underline_offset_(init_info.font.getUnderlinePosition(init_info.size)),
		underline_thickness_(init_info.font.getUnderlineThickness(init_info.size)) {
	}
	
	auto Underline::MainLine::reinit(LineInitInfo init_info) -> void {
		BaseLine::MainLine::reinit(init_info);
		underline_offset_ = init_info.font.getUnderlinePosition(init_info.size);
		underline_thickness_ = init_info.font.getUnderlineThickness(init_info.size);
	}
	
	auto Underline::MainLine::make() -> Underline* {
		return new Underline{std::move(*this)};
	}
	
	auto Underline::MainLine::copy() -> MainLine* {
		return new MainLine{*this};
	}
	
	Underline::Underline(MainLine&& main_line) :
		BaseLine(main_line),
		underline_offset_(main_line.underline_offset_),
		underline_thickness_(main_line.underline_thickness_) {
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

auto ieml::Decode<char, ie::Underline::MainLine::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Underline::MainLine::Make> {
	if(node.is_map()) {
		return ie::Underline::MainLine::Make{node.get_map_view().except().get_as<orl::Option<sf::Color> >("color").except().ok_or({})};
	} else if(node.is_null()) {
		return ie::Underline::MainLine::Make{};
	}
	return {};
}