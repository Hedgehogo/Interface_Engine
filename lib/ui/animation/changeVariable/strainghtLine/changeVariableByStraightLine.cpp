#include "changeVariableByStraightLine.hpp"

namespace ui {
	ChangeVariableByStraightLine::ChangeVariableByStraightLine(float k, float length, float b) : length(length), k(k), b(b) {}


	float ChangeVariableByStraightLine::getSize() {
		return length;
	}

	float ChangeVariableByStraightLine::operator()(float x) {
		return (k * x) + b;
	}

	ChangeVariableByStraightLine* makeChangeVariableByStraightLine(float start, float end, float length) {
		return new ChangeVariableByStraightLine((end-start) / length, length, start);
	}

	bool convertPointer(const YAML::Node &node, ChangeVariableByStraightLine*& changeVariableByStraightLine){
		if (node["k"]){
			changeVariableByStraightLine = new ChangeVariableByStraightLine{
				node["k"].as<float>(),
				node["length"].as<float>(),
				convDef(node["b"], 0.f)
			};
		}else{
			changeVariableByStraightLine = makeChangeVariableByStraightLine(
				node["start"].as<float>(),
				node["end"].as<float>(),
				node["length"].as<float>()
			);
		}
		return true;
	}
}
