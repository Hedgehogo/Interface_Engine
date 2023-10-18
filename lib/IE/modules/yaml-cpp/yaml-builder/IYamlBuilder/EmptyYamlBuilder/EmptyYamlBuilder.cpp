#include "EmptyYamlBuilder.hpp"

namespace ie::detail {
	EmptyYamlBuilder EmptyYamlBuilder::builder = {};
	
	bool EmptyYamlBuilder::build(const YAML::Node&, void*&) const {
		return false;
	}
	
	IYamlBuilder* EmptyYamlBuilder::get_builder(const std::string&) {
		return this;
	}
	
	bool EmptyYamlBuilder::is_exists() {
		return false;
	}
	
	bool EmptyYamlBuilder::determine(const YAML::Node&, std::string&) {
		return false;
	}
}