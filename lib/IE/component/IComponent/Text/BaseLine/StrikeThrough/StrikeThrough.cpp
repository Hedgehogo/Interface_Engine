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
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<StrikeThrough>::decode_pointer(const YAML::Node& node, StrikeThrough*& strike_through) {
		strike_through = new StrikeThrough{
			conv_def<orl::Option<sf::Color>>(node["color"], {}),
			conv_def(node["strike-through-offset"], 0.3f)
		};
		return true;

	}
	*/
}