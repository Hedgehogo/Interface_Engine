#include "funcYamlBuilder.hpp"
#include <utility>

namespace ie::detail {
	std::vector<FuncYamlBuilder> FuncYamlBuilder::builders = {};
	
	FuncYamlBuilder::FuncYamlBuilder(FuncYamlBuilder::VoidBuildFunc function, std::vector<std::string> names) : names(std::move(names)), function(std::move(function)) {
	}
	
	bool FuncYamlBuilder::build(const YAML::Node& node, void*& object) const {
		return function(node, object);
	}
	
	IYamlBuilder* FuncYamlBuilder::getBuilder(const std::string& type) {
		if(std::find(names.begin(), names.end(), type) != names.end()) {
			return this;
		} else {
			return &EmptyYamlBuilder::builder;
		}
	}
	
	bool FuncYamlBuilder::determine(const YAML::Node&, std::string&) {
		return false;
	}
}