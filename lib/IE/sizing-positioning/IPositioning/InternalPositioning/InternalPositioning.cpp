#include "InternalPositioning.hpp"

namespace ie {
	InternalPositioning::InternalPositioning(float coefficient, float offset) : coefficient_(coefficient), offset_(offset) {
	}
	
	float InternalPositioning::find_position(float parent_position, float object_size, float parent_size, float) {
		return parent_position + (parent_size - object_size) * coefficient_ + offset_;
	}
	
	InternalPositioning* InternalPositioning::copy() {
		return new InternalPositioning{*this};
	}
	
	float InternalPositioning::get_coefficient() const {
		return coefficient_;
	}
	
	float InternalPositioning::get_offset() const {
		return offset_;
	}
	
	bool DecodePointer<InternalPositioning>::decode_pointer(const YAML::Node& node, InternalPositioning*& internal_positioning) {
		if(node.IsScalar()) {
			internal_positioning = new InternalPositioning{
				node.as<float>()
			};
		} else {
			internal_positioning = new InternalPositioning{
				node["coefficient"].as<float>(),
				conv_def(node["offset"], 0.f)
			};
		}
		return true;
	}
}