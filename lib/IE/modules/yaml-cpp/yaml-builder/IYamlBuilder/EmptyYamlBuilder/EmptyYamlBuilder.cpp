#include "EmptyYamlBuilder.hpp"

namespace ie::detail {
	EmptyYamlBuilder EmptyYamlBuilder::builder = {};
	
	bool EmptyYamlBuilder::build(const YAML::Node&, void*&) const {
		return false;
	}
	
	IYamlBuilder* EmptyYamlBuilder::getBuilder(const std::string&) {
		return this;
	}
	
	bool EmptyYamlBuilder::isExists() {
		return false;
	}
	
	bool EmptyYamlBuilder::determine(const YAML::Node&, std::string&) {
		return false;
	}
}