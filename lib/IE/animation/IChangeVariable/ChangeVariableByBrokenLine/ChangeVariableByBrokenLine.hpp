#pragma once

#include "../IChangeVariable.hpp"

namespace ie {
	class ChangeVariableByBrokenLine : public virtual IChangeVariable {
	public:
		struct Value {
			float value;
			float size = 0;
		};
	
		ChangeVariableByBrokenLine(std::vector<Value> values);
		
		float get_size() override;
		
		float operator()(float frame) override;
		
		IChangeVariable* copy() override;
	
	protected:
		std::vector<Value> values;
		float size;
	};
	
	template<>
	struct Decode<ChangeVariableByBrokenLine::Value> {
		static bool decode(const YAML::Node& node, ChangeVariableByBrokenLine::Value& value);
	};
	
	template<>
	struct DecodePointer<ChangeVariableByBrokenLine> {
		static bool decode_pointer(const YAML::Node& node, ChangeVariableByBrokenLine*& broken_line);
	};
}
