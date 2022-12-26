#pragma once

#include "../baseChangeVariable.hpp"

namespace ui {
	class ChangeVariableByStraightLine : public BaseChangeVariable{
		float length;

		float k, b;

	public:
		
		ChangeVariableByStraightLine(float k, float length, float b = 0);

		float getSize() override;

		float operator()(float x) override;
	};

	ChangeVariableByStraightLine* makeChangeVariableByStraightLine(float start, float end, float length);


	bool convertPointer(const YAML::Node &node, ChangeVariableByStraightLine*& changeVariableByStraightLine);
}