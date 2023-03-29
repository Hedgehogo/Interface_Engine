#include <iostream>
#include "changeVariableBySteppedLine.hpp"

namespace ui {
	ChangeVariableBySteppedLine::ChangeVariableBySteppedLine(std::vector<Value> values) : values(values) {
		for (const auto &item: values){
			size += item.size;
		}
	}

	float ChangeVariableBySteppedLine::getSize() {
		return size;
	}

	float ChangeVariableBySteppedLine::operator()(float frame) {
		float sumSize{0};
		int i{0};
		for (; sumSize + values[i].size < frame && i < values.size(); ++i) {
			sumSize += values[i].size;
		}

		return values[i].value;
	}

	IChangeVariable *ChangeVariableBySteppedLine::copy() {
		return new ChangeVariableBySteppedLine{values};
	}

	template<>
	bool convert(const YAML::Node &node, ChangeVariableBySteppedLine::Value &value) {
		value = ChangeVariableBySteppedLine::Value{
			node["value"].as<float>(),
			convDef(node["size"], 0.f),
		};

		return true;
	}

	bool convertPointer(const YAML::Node &node, ChangeVariableBySteppedLine *&brokenLine) {
		brokenLine = new ChangeVariableBySteppedLine{
			node["values"].as<std::vector<ChangeVariableBySteppedLine::Value>>()
		};

		return true;
	}
} // ui