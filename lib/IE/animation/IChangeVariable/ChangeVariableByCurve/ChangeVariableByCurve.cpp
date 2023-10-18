#include "ChangeVariableByCurve.hpp"

namespace ie {
	ChangeVariableByCurve::ChangeVariableByCurve(float k1, float k2, float size, sf::Vector2f start, sf::Vector2f end) : start(start), end(end), k1(k1), k2(k2), size(size) {
	}
	
	float ChangeVariableByCurve::get_size() {
		return size;
	}
	
	float s(float x) {
		return 3 * std::pow(x, 2) - 2 * std::pow(x, 3);
	}
	
	float d(float x, sf::Vector2f A, float a) {
		return (x - A.x) * a + A.y;
	}
	
	float ChangeVariableByCurve::operator()(float frame) {
		frame /= size;
		return s((end.x - frame) / (end.x - start.x)) * d(frame, start, k1) + s((frame - start.x) / (end.x - start.x)) * d(frame, end, k2);
	}
	
	ChangeVariableByCurve* ChangeVariableByCurve::copy() {
		return new ChangeVariableByCurve{k1, k2, size, start, end};
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