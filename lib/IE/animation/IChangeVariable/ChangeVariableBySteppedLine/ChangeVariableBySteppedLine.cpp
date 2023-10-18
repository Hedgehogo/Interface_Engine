#include "ChangeVariableBySteppedLine.hpp"

namespace ie {
	ChangeVariableBySteppedLine::ChangeVariableBySteppedLine(std::vector<Value> values) : values(values) {
		for(const auto& item: values) {
			size += item.size;
		}
	}
	
	float ChangeVariableBySteppedLine::get_size() {
		return size;
	}
	
	float ChangeVariableBySteppedLine::operator()(float frame) {
		float sum_size{0};
		std::size_t i{0};
		for(; sum_size + values[i].size < frame && i < values.size(); ++i) {
			sum_size += values[i].size;
		}
		
		return values[i].value;
	}
	
	IChangeVariable* ChangeVariableBySteppedLine::copy() {
		return new ChangeVariableBySteppedLine{values};
	}
	
	bool Decode<ChangeVariableBySteppedLine::Value>::decode(const YAML::Node& node, ChangeVariableBySteppedLine::Value& value) {
		value = ChangeVariableBySteppedLine::Value{
			node["value"].as<float>(),
			conv_def(node["size"], 0.f),
		};
		
		return true;
	}
	
	bool DecodePointer<ChangeVariableBySteppedLine>::decode_pointer(const YAML::Node& node, ChangeVariableBySteppedLine*& broken_line) {
		broken_line = new ChangeVariableBySteppedLine{
			node["values"].as<std::vector<ChangeVariableBySteppedLine::Value>>()
		};
		
		return true;
	}
}