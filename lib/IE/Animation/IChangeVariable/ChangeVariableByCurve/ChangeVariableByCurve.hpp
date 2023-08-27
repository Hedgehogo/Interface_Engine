#pragma once

#include "../IChangeVariable.hpp"

namespace ie {
	class ChangeVariableByCurve : public IChangeVariable {
	public:
		ChangeVariableByCurve(float k1, float k2, float size = 1, sf::Vector2f start = {0, 0}, sf::Vector2f end = {1, 1});
	
		float getSize() override;
		
		float operator()(float frame) override;
		
		ChangeVariableByCurve* copy() override;
	
	protected:
		sf::Vector2f start, end;
		float k1, k2;
		float size;
	};
	
	template<>
	struct DecodePointer<ChangeVariableByCurve> {
		static bool decodePointer(const YAML::Node& node, ChangeVariableByCurve*& changeVariableByCurve);
	};
}
