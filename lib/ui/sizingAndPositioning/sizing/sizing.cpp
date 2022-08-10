#include "sizing.hpp"

float ui::Sizing::getParentSize(float objectSize) {
	return 0;
}

float ui::Sizing::operator()(float parentSize, float targetSize) {
	return this->findSize(parentSize, targetSize);
}

ui::Sizing *ui::Sizing::createFromYaml(const YAML::Node &node) {
	return nullptr;
}
