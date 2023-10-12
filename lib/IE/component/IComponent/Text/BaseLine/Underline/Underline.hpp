#pragma once

#include "../BaseLine.hpp"

namespace ie {
	class Underline : public BaseLine {
	public:
		struct Make : public BaseLine::Make {
			sf::Color color;
			
			explicit Make(const sf::Color& color = nullColor);
			
			Underline* make(LineInitInfo initInfo) override;
		};
		
		Underline(Make&& make, LineInitInfo initInfo);
		
		Underline(sf::Color color = nullColor);
		
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