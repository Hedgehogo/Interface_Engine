#pragma once

#include "../BaseLine.hpp"

namespace ie {
	class Underline : public BaseLine {
	public:
		struct Make : public BaseLine::Make {
			orl::Option<sf::Color> color;
			
			explicit Make(const orl::Option<sf::Color>& color = {});
			
			Underline* make(LineInitInfo init_info) override;
		};
		
		Underline(Make&& make, LineInitInfo init_info);
		
		Underline(orl::Option<sf::Color> color = {});
		
		void init(LineInitInfo init_info) override;
		
		void resize(float start, float end, float height) override;
		
		Underline* copy() const override;
	
	protected:
		float underline_offset;
		float underline_thickness;
	};
	
	template<>
	struct DecodePointer<Underline> {
		static bool decode_pointer(const YAML::Node& node, Underline*& underline);
	};
}