#pragma once

#include "../BaseLine.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class Underline : public BaseLine {
	public:
		struct Make : public BaseLine::Make {
			orl::Option<sf::Color> color;
			
			explicit Make(const orl::Option<sf::Color>& color = {});
			
			Underline* make(LineInitInfo init_info) override;
		};
		
		Underline(Make&& make, LineInitInfo init_info);
		
		void resize(float start, float end, float height) override;
		
		Underline* copy() const override;
	
	protected:
		float underline_offset;
		float underline_thickness;
	};
}

template<>
struct ieml::Decode<char, ie::Underline::Make> {
	static orl::Option<ie::Underline::Make> decode(ieml::Node const& node);
};