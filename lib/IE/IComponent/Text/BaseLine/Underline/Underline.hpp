#pragma once

#include "../BaseLine.hpp"

namespace ie {
	class Underline : public BaseLine {
	public:
		struct Make : public BaseLine::Make {
			orl::Option<sf::Color> color;
			
			explicit Make(const orl::Option<sf::Color>& color = {});
			
			Underline* make(LineInitInfo initInfo) override;
		};
		
		Underline(Make&& make, LineInitInfo initInfo);
		
		Underline(orl::Option<sf::Color> color = {});
		
		void init(LineInitInfo initInfo) override;
		
		void resize(float start, float end, float height) override;
		
		Underline* copy() const override;
	
	protected:
		float underlineOffset;
		float underlineThickness;
	};
	
	template<>
	struct DecodePointer<Underline> {
		static bool decodePointer(const YAML::Node& node, Underline*& underline);
	};
}