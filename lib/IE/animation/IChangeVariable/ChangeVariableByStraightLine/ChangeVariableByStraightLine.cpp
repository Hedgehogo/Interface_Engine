#include "ChangeVariableByStraightLine.hpp"

namespace ie {
	ChangeVariableByStraightLine::ChangeVariableByStraightLine(float k, float length, float b) : length(length), k(k), b(b) {
	}
	
	float ChangeVariableByStraightLine::get_size() {
		return length;
	}
	
	float ChangeVariableByStraightLine::operator()(float x) {
		return (k * x) + b;
	}
	
	IChangeVariable* ChangeVariableByStraightLine::copy() {
		return new ChangeVariableByStraightLine{k, length, b};
	}
	
	ChangeVariableByStraightLine* make_change_variable_by_straight_line(float start, float end, float length) {
		return new ChangeVariableByStraightLine((end - start) / length, length, start);
	}
	
	bool DecodePointer<ChangeVariableByStraightLine>::decode_pointer(const YAML::Node& node, ChangeVariableByStraightLine*& change_variable_by_straight_line) {
		if(node["k"]) {
			change_variable_by_straight_line = new ChangeVariableByStraightLine{
				node["k"].as<float>(),
				node["length"].as<float>(),
				conv_def(node["b"], 0.f)
			};
		} else {
			change_variable_by_straight_line = make_change_variable_by_straight_line(
				node["start"].as<float>(),
				node["end"].as<float>(),
				node["length"].as<float>()
			);
		}
		return true;
	}
}
