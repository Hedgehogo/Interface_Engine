#include "changeVariableBySteppedLine.hpp"

namespace ui {
	ChangeVariableBySteppedLine::ChangeVariableBySteppedLine(std::vector<Value> values) : values(values) {
		for(const auto& item: values) {
			size += item.size;
		}
	}
	
	float ChangeVariableBySteppedLine::getSize() {
		return size;
	}
	
	float ChangeVariableBySteppedLine::operator()(float frame) {
		float sumSize{0};
		std::size_t i{0};
		for(; sumSize + values[i].size < frame && i < values.size(); ++i) {
			sumSize += values[i].size;
		}
		
		return values[i].value;
	}
	
	IChangeVariable* ChangeVariableBySteppedLine::copy() {
		return new ChangeVariableBySteppedLine{values};
	}
	
	bool Decode<ChangeVariableBySteppedLine::Value>::decode(const YAML::Node& node, ChangeVariableBySteppedLine::Value& value) {
		value = ChangeVariableBySteppedLine::Value{
			node["value"].as<float>(),
			convDef(node["size"], 0.f),
		};
		
		return true;
	}
	
	bool DecodePointer<ChangeVariableBySteppedLine>::decodePointer(const YAML::Node& node, ChangeVariableBySteppedLine*& brokenLine) {
		brokenLine = new ChangeVariableBySteppedLine{
			node["values"].as<std::vector<ChangeVariableBySteppedLine::Value>>()
		};
		
		return true;
	}
}