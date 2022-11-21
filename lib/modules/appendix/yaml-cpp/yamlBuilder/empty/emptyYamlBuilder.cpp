#include "emptyYamlBuilder.hpp"

namespace ui::detail {
	EmptyYamlBuilder EmptyYamlBuilder::builder = {};
	
	bool EmptyYamlBuilder::build(const YAML::Node &node, void *&object) const {
		return false;
	}
	
	IYamlBuilder *EmptyYamlBuilder::getBuilder(const std::string &type) {
		return this;
	}
	
	bool EmptyYamlBuilder::isExists() {
		return false;
	}
	
	bool EmptyYamlBuilder::determine(const YAML::Node &node, std::string &type) {
		return false;
	}
}