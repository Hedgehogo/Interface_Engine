#include "ChangeVariableByStraightLine.hpp"

namespace ie {
	ChangeVariableByStraightLine::ChangeVariableByStraightLine(float k, float length, float b) : length_(length), k_(k), b_(b) {
	}
	
	float ChangeVariableByStraightLine::get_size() {
		return length_;
	}
	
	float ChangeVariableByStraightLine::operator()(float x) {
		return (k_ * x) + b_;
	}
	
	IChangeVariable* ChangeVariableByStraightLine::copy() {
		return new ChangeVariableByStraightLine{k_, length_, b_};
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
