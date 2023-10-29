#pragma once

#include "../ISizing.hpp"

namespace ie {
	class ParentCoefficientSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float coefficient = 1;
			float addition = 0;
			
			Make(float coefficient = 1, float addition = 0);
			
			ParentCoefficientSizing* make(float normal_size) override;
		};
		
		ParentCoefficientSizing(Make&& make, float normal_size);
		
		explicit ParentCoefficientSizing(float coefficient = 1, float addition = 0);
		
		void init(float) override;
		
		float find_size(float parent_size, float) override;
		
		float get_parent_size(float object_size) override;
		
		ParentCoefficientSizing* copy() override;
	
	protected:
		float coefficient_;
		float addition_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<ParentCoefficientSizing> {
		static bool decode_pointer(const YAML::Node& node, ParentCoefficientSizing*& parent_coefficient_sizing);
	};
	*/
}
