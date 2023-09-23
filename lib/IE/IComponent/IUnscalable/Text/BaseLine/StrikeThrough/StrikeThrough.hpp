#pragma once

#include "../BaseLine.hpp"

namespace ie {
	class StrikeThrough : public BaseLine {
	public:
		struct Make : public BaseLine::Make {
			sf::Color color = sf::Color{255, 255, 255, 0};
			float strikeThroughOffset;
			
			Make(const sf::Color& color = sf::Color{255, 255, 255, 0}, float strikeThroughOffset = 0.3);
			
			BaseLine* make(LineInitInfo initInfo) override;
		};
		
		StrikeThrough(Make&& make, LineInitInfo initInfo);
		
		StrikeThrough(sf::Color color = sf::Color{255, 255, 255, 0}, float strikeThroughOffset = 0.3);
		
		void init(LineInitInfo initInfo);
		
		void resize(float start, float end, float height);
		
		StrikeThrough* copy() const override;
	
	protected:
		float strikeThroughOffset;
		float underlineThickness;
	};
	
	template<>
	struct DecodePointer<StrikeThrough> {
		static bool decodePointer(const YAML::Node& node, StrikeThrough*& strikeThrough);
	};
}