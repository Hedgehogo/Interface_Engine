#pragma once

#include <vector>
#include "../IChangeVariable.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class ChangeVariableBySteppedLine : public virtual IChangeVariable {
	public:
		struct Value {
			float value;
			float size = 0;
		};
	
		ChangeVariableBySteppedLine(std::vector<Value> values);
		
		float get_size() override;
		
		float operator()(float frame) override;
		
		IChangeVariable* copy() override;
	
	protected:
		std::vector<Value> values_;
		float size_;
	};
	
	/*old_yaml_decode
	template<>
	struct Decode<ChangeVariableBySteppedLine::Value> {
		static bool decode(const YAML::Node& node, ChangeVariableBySteppedLine::Value& value);
	};
	*/
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<ChangeVariableBySteppedLine> {
		static bool decode_pointer(const YAML::Node& node, ChangeVariableBySteppedLine*& broken_line);
	};
	*/
}
