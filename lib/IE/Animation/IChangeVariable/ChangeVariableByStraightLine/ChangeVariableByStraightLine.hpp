#pragma once

#include "../IChangeVariable.hpp"

namespace ie {
	class ChangeVariableByStraightLine : public IChangeVariable {
	public:
		ChangeVariableByStraightLine(float k, float length, float b = 0);
		
		float getSize() override;
		
		float operator()(float x) override;
		
		IChangeVariable* copy() override;
	
	protected:
		float length;
		float k, b;
	};
	
	ChangeVariableByStraightLine* makeChangeVariableByStraightLine(float start, float end, float length);
	
	template<>
	struct DecodePointer<ChangeVariableByStraightLine> {
		static bool decodePointer(const YAML::Node& node, ChangeVariableByStraightLine*& changeVariableByStraightLine);
	};
}