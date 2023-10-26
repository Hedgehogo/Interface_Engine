#include "ChangeVariableByBrokenLine.hpp"

namespace ie {
	ChangeVariableByBrokenLine::ChangeVariableByBrokenLine(std::vector<Value> values) : values_(values) {
		for(const auto& item: values) {
			size_ += item.size;
		}
	}
	
	float ChangeVariableByBrokenLine::get_size() {
		return size_;
	}
	
	float ChangeVariableByBrokenLine::operator()(float frame) {
		float sum_size{0};
		size_t i{0};
		for(; sum_size + values_[i].size < frame && i < values_.size(); ++i) {
			sum_size += values_[i].size;
		}
		
		float ratio = (frame - sum_size) / values_[i].size;
		return (ratio * (values_[((i == values_.size() - 1) ? (0) : (i + 1))].value - values_[i].value)) + values_[i].value;
	}
	
	IChangeVariable* ChangeVariableByBrokenLine::copy() {
		return new ChangeVariableByBrokenLine{values_};
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