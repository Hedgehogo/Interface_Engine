#include "ChangeVariableBySinusoid.hpp"

namespace ie {
	ChangeVariableBySinusoid::ChangeVariableBySinusoid(float size, float a, float b, float c, float d) : a_(a), b_(b), c_(c), d_(d), size_(size) {
	}
	
	float ChangeVariableBySinusoid::get_size() {
		return size_;
	}
	
	float ChangeVariableBySinusoid::operator()(float frame) {
		return a_ + (b_ * std::sin((c_ * frame) + d_));
	}
	
	IChangeVariable* ChangeVariableBySinusoid::copy() {
		return new ChangeVariableBySinusoid{size_, a_, b_, c_, d_};
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