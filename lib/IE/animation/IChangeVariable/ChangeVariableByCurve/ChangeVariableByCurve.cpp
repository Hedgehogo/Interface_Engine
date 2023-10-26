#include "ChangeVariableByCurve.hpp"

namespace ie {
	ChangeVariableByCurve::ChangeVariableByCurve(float k1, float k2, float size, sf::Vector2f start, sf::Vector2f end) : start_(start), end_(end), k1_(k1), k2_(k2), size_(size) {
	}
	
	float ChangeVariableByCurve::get_size() {
		return size_;
	}
	
	float s(float x) {
		return 3 * std::pow(x, 2) - 2 * std::pow(x, 3);
	}
	
	float d(float x, sf::Vector2f A, float a) {
		return (x - A.x) * a + A.y;
	}
	
	float ChangeVariableByCurve::operator()(float frame) {
		frame /= size_;
		return s((end_.x - frame) / (end_.x - start_.x)) * d(frame, start_, k1_) + s((frame - start_.x) / (end_.x - start_.x)) * d(frame, end_, k2_);
	}
	
	ChangeVariableByCurve* ChangeVariableByCurve::copy() {
		return new ChangeVariableByCurve{k1_, k2_, size_, start_, end_};
	}
	
	bool DecodePointer<ChangeVariableByCurve>::decode_pointer(const YAML::Node& node, ChangeVariableByCurve*& change_variable_by_curve) {
		change_variable_by_curve = new ChangeVariableByCurve{
			node["k1"].as<float>(),
			node["k2"].as<float>(),
			conv_def(node["size"], 1.f),
			conv_def(node["start"], sf::Vector2f{0, 0}),
			conv_def(node["end"], sf::Vector2f{1, 1})
		};
		
		return true;
	}
}