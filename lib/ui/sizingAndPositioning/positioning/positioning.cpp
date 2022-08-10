#include "positioning.hpp"

float ui::Positioning::operator()(float parentPosition, float objectSize, float parentSize, float targetSize) {
	return this->findPosition(parentPosition, objectSize, parentSize, targetSize);
}

ui::Positioning *ui::Positioning::createFromYaml(const YAML::Node &node) {
	return nullptr;
}
