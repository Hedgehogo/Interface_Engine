#pragma once

#include "../iChangeVariable.hpp"

namespace ui {
	class ChangeVariableByCurve : public IChangeVariable {
	protected:
		sf::Vector2f start, end;
		float k1, k2;
		float size;
		
	public:
		ChangeVariableByCurve(float k1, float k2, float size = 1, sf::Vector2f start = {0, 0}, sf::Vector2f end = {1, 1});
	
		float getSize() override;
		
		float operator()(float frame) override;
		
		ChangeVariableByCurve* copy() override;
	};
	
	template<>
	struct DecodePointer<ChangeVariableByCurve> {
		static bool decodePointer(const YAML::Node& node, ChangeVariableByCurve*& changeVariableByCurve);
	};
}
