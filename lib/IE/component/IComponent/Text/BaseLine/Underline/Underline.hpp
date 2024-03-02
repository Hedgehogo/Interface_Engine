#pragma once

#include "../BaseLine.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class Underline : public BaseLine {
	public:
		struct Make : public BaseLine::Make {
			orl::Option<sf::Color> color;
			
			Make(orl::Option<sf::Color> color = {});
			
			auto make(LineInitInfo init_info) -> Underline* override;
		};
		
		Underline(Make&& make, LineInitInfo init_info);
		
		auto resize(float start, float end, float height) -> void override;
		
		auto copy() const -> Underline* override;
	
	protected:
		float underline_offset_;
		float underline_thickness_;
	};
}

template<>
struct ieml::Decode<char, ie::Underline::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Underline::Make>;
};