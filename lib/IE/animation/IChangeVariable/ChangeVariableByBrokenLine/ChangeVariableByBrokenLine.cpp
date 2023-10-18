#include "ChangeVariableByBrokenLine.hpp"

namespace ie {
	ChangeVariableByBrokenLine::ChangeVariableByBrokenLine(std::vector<Value> values) : values(values) {
		for(const auto& item: values) {
			size += item.size;
		}
	}
	
	float ChangeVariableByBrokenLine::get_size() {
		return size;
	}
	
	float ChangeVariableByBrokenLine::operator()(float frame) {
		float sum_size{0};
		std::size_t i{0};
		for(; sum_size + values[i].size < frame && i < values.size(); ++i) {
			sum_size += values[i].size;
		}
		
		float ratio = (frame - sum_size) / values[i].size;
		return (ratio * (values[((i == values.size() - 1) ? (0) : (i + 1))].value - values[i].value)) + values[i].value;
	}
	
	IChangeVariable* ChangeVariableByBrokenLine::copy() {
		return new ChangeVariableByBrokenLine{values};
	}
	
	bool Decode<ChangeVariableByBrokenLine::Value>::decode(const YAML::Node& node, ChangeVariableByBrokenLine::Value& value) {
		value = ChangeVariableByBrokenLine::Value{
			node["value"].as<float>(),
			conv_def(node["size"], 0.f),
		};
		
		return true;
	}
	
	bool DecodePointer<ChangeVariableByBrokenLine>::decode_pointer(const YAML::Node& node, ChangeVariableByBrokenLine*& broken_line) {
		broken_line = new ChangeVariableByBrokenLine{
			node["values"].as<std::vector<ChangeVariableByBrokenLine::Value>>()
		};
		
		return true;
	}
}