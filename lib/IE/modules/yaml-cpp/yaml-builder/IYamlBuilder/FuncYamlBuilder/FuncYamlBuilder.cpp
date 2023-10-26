#include "FuncYamlBuilder.hpp"
#include <utility>

namespace ie::detail {
	std::vector<FuncYamlBuilder> FuncYamlBuilder::builders_ = {};
	
	FuncYamlBuilder::FuncYamlBuilder(FuncYamlBuilder::VoidBuildFunc function, std::vector<std::string> names) : names_(std::move(names)), function_(std::move(function)) {
	}
	
	bool FuncYamlBuilder::build(const YAML::Node& node, void*& object) const {
		return function_(node, object);
	}
	
	IYamlBuilder* FuncYamlBuilder::get_builder(const std::string& type) {
		if(std::find(names_.begin(), names_.end(), type) != names_.end()) {
			return this;
		} else {
			return &EmptyYamlBuilder::builder;
		}
	}
	
	bool FuncYamlBuilder::determine(const YAML::Node&, std::string&) {
		return false;
	}
}