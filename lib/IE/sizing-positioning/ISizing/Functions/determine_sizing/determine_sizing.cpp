#include "determine_sizing.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/determine/determine.hpp"

namespace ie {
	bool determine_sizing(const YAML::Node& node, std::string& type) {
		if(node.IsScalar()) {
			type = "ConstSizing";
			return true;
		} else {
			if(determine(node, {})) {
				type = "RelativeNormalSizing";
				return true;
			}
			if(determine(node, {{"size"}})) {
				type = "ConstSizing";
				return true;
			}
			if(determine(node, {{"addition"}})) {
				type = "RelativeParentSizing";
				return true;
			}
			if(determine(node, {{"coefficient"}}, {{"addition"}})) {
				type = "ParentCoefficientSizing";
				return true;
			}
			if(determine(node, {
				{"target-coefficient"},
				{"parent-coefficient"}
			}, {{"addition"}})) {
				type = "SmartSizing";
				return true;
			}
		}
		return false;
	}
}