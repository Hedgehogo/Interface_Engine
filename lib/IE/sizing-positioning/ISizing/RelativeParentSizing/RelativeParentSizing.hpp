#pragma once

#include "../ISizing.hpp"

namespace ie {
	class RelativeParentSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float addition = 0;
			
			Make(float addition = 0);
			
			RelativeParentSizing* make(float normal_size) override;
		};
		
		RelativeParentSizing(Make&& make, float normal_size);
		
		explicit RelativeParentSizing(float addition = 0);
		
		void init(float) override;
		
		float find_size(float parent_size, float) override;
		
		float get_parent_size(float object_size) override;
		
		RelativeParentSizing* copy() override;
	
	protected:
		float addition_;
	};
	
	template<>
	struct DecodePointer<RelativeParentSizing> {
		static bool decode_pointer(const YAML::Node& node, RelativeParentSizing*& relative_parent_sizing);
	};
}
