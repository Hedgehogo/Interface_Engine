#pragma once

#include "../BaseLine.hpp"

namespace ie {
	class StrikeThrough : public BaseLine {
	public:
		struct Make : public BaseLine::Make {
			orl::Option<sf::Color> color = sf::Color{255, 255, 255, 0};
			float strike_through_offset;
			
			Make(const orl::Option<sf::Color>& color = {}, float strike_through_offset = 0.3);
			
			BaseLine* make(LineInitInfo init_info) override;
		};
		
		StrikeThrough(Make&& make, LineInitInfo init_info);
		
		StrikeThrough(orl::Option<sf::Color> color = {}, float strike_through_offset = 0.3);
		
		void init(LineInitInfo init_info);
		
		void resize(float start, float end, float height);
		
		StrikeThrough* copy() const override;
	
	protected:
		float strike_through_offset;
		float underline_thickness;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<StrikeThrough> {
		static bool decode_pointer(const YAML::Node& node, StrikeThrough*& strike_through);
	};
	*/
}