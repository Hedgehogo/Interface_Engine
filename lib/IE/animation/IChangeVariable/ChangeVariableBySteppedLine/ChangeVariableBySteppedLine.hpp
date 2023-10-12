#pragma once

#include "../IChangeVariable.hpp"

namespace ie {
	class ChangeVariableBySteppedLine : public virtual IChangeVariable {
	public:
		struct Value {
			float value;
			float size = 0;
		};
	
		ChangeVariableBySteppedLine(std::vector<Value> values);
		
		float getSize() override;
		
		float operator()(float frame) override;
		
		IChangeVariable* copy() override;
	
	protected:
		std::vector<Value> values;
		float size;
	};
	
	template<>
	struct Decode<ChangeVariableBySteppedLine::Value> {
		static bool decode(const YAML::Node& node, ChangeVariableBySteppedLine::Value& value);
	};
	
	template<>
	struct DecodePointer<ChangeVariableBySteppedLine> {
		static bool decodePointer(const YAML::Node& node, ChangeVariableBySteppedLine*& brokenLine);
	};
}
