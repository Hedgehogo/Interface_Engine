#include "ChangeVariableBySinusoid.hpp"

namespace ie {
	ChangeVariableBySinusoid::ChangeVariableBySinusoid(float size, float a, float b, float c, float d) : a(a), b(b), c(c), d(d), size(size) {
	}
	
	float ChangeVariableBySinusoid::get_size() {
		return size;
	}
	
	float ChangeVariableBySinusoid::operator()(float frame) {
		return a + (b * std::sin((c * frame) + d));
	}
	
	IChangeVariable* ChangeVariableBySinusoid::copy() {
		return new ChangeVariableBySinusoid{size, a, b, c, d};
	}
	
	
	bool DecodePointer<ChangeVariableBySinusoid>::decode_pointer(const YAML::Node& node, ChangeVariableBySinusoid*& change_variable_by_sinusoid) {
		change_variable_by_sinusoid = new ChangeVariableBySinusoid{
			node["size"].as<float>(),
			conv_def(node["a"], conv_def(node["offset-OY"], 0.f)),
			conv_def(node["b"], conv_def(node["amplitude"], 1.f)),
			conv_def(node["c"], conv_def(node["frequency"], 1.f)),
			conv_def(node["d"], conv_def(node["offset-OX"], 0.f)),
		};
		
		return true;
	}
}