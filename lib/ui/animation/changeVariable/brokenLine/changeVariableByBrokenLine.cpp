#include "changeVariableByBrokenLine.hpp"

namespace ui {
	ChangeVariableByBrokenLine::ChangeVariableByBrokenLine(std::vector<Value> values) : values(values) {
		for(const auto& item: values) {
			size += item.size;
		}
	}
	
	float ChangeVariableByBrokenLine::getSize() {
		return size;
	}
	
	float ChangeVariableByBrokenLine::operator()(float frame) {
		float sumSize{0};
		int i{0};
		for(; sumSize + values[i].size < frame && i < values.size(); ++i) {
			sumSize += values[i].size;
		}
		
		float ratio = (frame - sumSize) / values[i].size;
		return (ratio * (values[((i == values.size() - 1) ? (0) : (i + 1))].value - values[i].value)) + values[i].value;
	}
	
	IChangeVariable* ChangeVariableByBrokenLine::copy() {
		return new ChangeVariableByBrokenLine{values};
	}
	
	template<>
	bool convert(const YAML::Node &node, ChangeVariableByBrokenLine::Value &value) {
		value = ChangeVariableByBrokenLine::Value{
			node["value"].as<float>(),
			convDef(node["size"], 0.f),
		};
		
		return true;
	}
	
	bool Decode<ChangeVariableByBrokenLine::Value>::decode(const YAML::Node &node, ChangeVariableByBrokenLine::Value &value) {
		value = ChangeVariableByBrokenLine::Value{
			node["value"].as<float>(),
			convDef(node["size"], 0.f),
		};
		
		return true;
	}
	
	bool convertPointer(const YAML::Node& node, ChangeVariableByBrokenLine*& brokenLine) {
		brokenLine = new ChangeVariableByBrokenLine{
			node["values"].as<std::vector<ChangeVariableByBrokenLine::Value>>()
		};
		
		return true;
	}
	
	bool DecodePointer<ChangeVariableByBrokenLine>::decodePointer(const YAML::Node& node, ChangeVariableByBrokenLine*& brokenLine) {
		brokenLine = new ChangeVariableByBrokenLine{
			node["values"].as<std::vector<ChangeVariableByBrokenLine::Value>>()
		};
		
		return true;
	}
}