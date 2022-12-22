#include "changeVariableByStraightLine.hpp"

namespace ui {
	ChangeVariableByStraightLine::ChangeVariableByStraightLine(float k, float length, float b) : length(length), k(k), b(b) {}


	float ChangeVariableByStraightLine::getSize() {
		return length;
	}

	float ChangeVariableByStraightLine::operator()(float x) {
		return (k * x) + b;
	}

	ChangeVariableByStraightLine makeChangeVariableByStraightLine(float start, float end, float length) {
		return ChangeVariableByStraightLine((end-start) / length, length, start);
	}
}
