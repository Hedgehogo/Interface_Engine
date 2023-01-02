#pragma once

#include "../iChangeVariable.hpp"

namespace ui {
	class ChangeVariableByStraightLine : public IChangeVariable{
		float length;

		float k, b;

	public:
		
		ChangeVariableByStraightLine(float k, float length, float b = 0);

		float getSize() override;

		float operator()(float x) override;

		IChangeVariable * copy() override;
	};

	ChangeVariableByStraightLine* makeChangeVariableByStraightLine(float start, float end, float length);


	bool convertPointer(const YAML::Node &node, ChangeVariableByStraightLine*& changeVariableByStraightLine);
}