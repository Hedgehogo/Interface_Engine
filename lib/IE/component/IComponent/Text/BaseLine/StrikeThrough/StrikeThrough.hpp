#pragma once

#include "../BaseLine.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class StrikeThrough : public BaseLine {
	public:
		struct Make : public BaseLine::Make {
			orl::Option<sf::Color> color = {};
			float strike_through_offset;
			
			Make(const orl::Option<sf::Color>& color = {}, float strike_through_offset = 0.3);
			
			BaseLine* make(LineInitInfo init_info) override;
		};
		
		StrikeThrough(Make&& make, LineInitInfo init_info);

		void resize(float start, float end, float height) override;
		
		StrikeThrough* copy() const override;
	
	protected:
		float strike_through_offset;
		float underline_thickness;
	};
}

template<>
struct ieml::Decode<char, ie::StrikeThrough::Make> {
	static orl::Option<ie::StrikeThrough::Make> decode(ieml::Node const& node);
};