#pragma once

#include "../ISizing.hpp"

namespace ie {
	class SmartSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float target_coefficient = 1;
			float parent_coefficient = 0;
			float addition = 0;
			
			Make(float target_coefficient = 1, float parent_coefficient = 0, float addition = 0);
			
			SmartSizing* make(float normal_size) override;
		};
		
		SmartSizing(Make&& make, float normal_size);
		
		explicit SmartSizing(float target_coefficient = 1, float parent_coefficient = 0, float addition = 0);
		
		void init(float) override;
		
		float find_size(float parent_size, float target_size) override;
		
		float get_parent_size(float object_size) override;
		
		SmartSizing* copy() override;
	
	protected:
		float target_coefficient_;
		float parent_coefficient_;
		float addition_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<SmartSizing> {
		static bool decode_pointer(const YAML::Node& node, SmartSizing*& smart_sizing);
	};
	*/
}
