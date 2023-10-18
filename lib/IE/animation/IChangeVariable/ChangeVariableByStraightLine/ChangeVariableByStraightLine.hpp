#pragma once

#include "../IChangeVariable.hpp"

namespace ie {
	class ChangeVariableByStraightLine : public virtual IChangeVariable {
	public:
		ChangeVariableByStraightLine(float k, float length, float b = 0);
		
		float get_size() override;
		
		float operator()(float x) override;
		
		IChangeVariable* copy() override;
	
	protected:
		float length;
		float k, b;
	};
	
	ChangeVariableByStraightLine* make_change_variable_by_straight_line(float start, float end, float length);
	
	template<>
	struct DecodePointer<ChangeVariableByStraightLine> {
		static bool decode_pointer(const YAML::Node& node, ChangeVariableByStraightLine*& change_variable_by_straight_line);
	};
}