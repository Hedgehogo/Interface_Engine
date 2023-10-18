#pragma once

#include "../IChangeVariable.hpp"

namespace ie {
	class ChangeVariableByCurve : public virtual IChangeVariable {
	public:
		ChangeVariableByCurve(float k1, float k2, float size = 1, sf::Vector2f start = {0, 0}, sf::Vector2f end = {1, 1});
	
		float get_size() override;
		
		float operator()(float frame) override;
		
		ChangeVariableByCurve* copy() override;
	
	protected:
		sf::Vector2f start, end;
		float k1, k2;
		float size;
	};
	
	template<>
	struct DecodePointer<ChangeVariableByCurve> {
		static bool decode_pointer(const YAML::Node& node, ChangeVariableByCurve*& change_variable_by_curve);
	};
}
