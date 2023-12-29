#include "ChangeVariableBySteppedLine.hpp"

namespace ie {
	ChangeVariableBySteppedLine::ChangeVariableBySteppedLine(std::vector<Value> values) : values_(values) {
		for(const auto& item: values) {
			size_ += item.size;
		}
	}
	
	float ChangeVariableBySteppedLine::get_size() {
		return size_;
	}
	
	float ChangeVariableBySteppedLine::operator()(float frame) {
		float sum_size{0};
		size_t i{0};
		for(; sum_size + values_[i].size < frame && i < values_.size(); ++i) {
			sum_size += values_[i].size;
		}
		
		return values_[i].value;
	}
	
	IChangeVariable* ChangeVariableBySteppedLine::copy() {
		return new ChangeVariableBySteppedLine{values_};
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