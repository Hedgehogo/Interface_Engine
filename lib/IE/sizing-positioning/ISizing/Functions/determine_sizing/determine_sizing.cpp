#include "determine_sizing.hpp"
#include "IE/ieml/determine/determine.hpp"

namespace ie {
	orl::Option<std::string> determine_sizing(ieml::Node const& node) {
		auto& clear_node{node.get_clear()};
		if(clear_node.is_raw()) {
			return {"ConstSizing"};
		} else {
			if(determine(clear_node, {})) {
				return {"RelativeNormalSizing"};
			}
			if(determine(clear_node, {{"size"}})) {
				return {"ConstSizing"};
			}
			if(determine(clear_node, {{"addition"}})) {
				return {"RelativeParentSizing"};
			}
			if(determine(clear_node, {{"coefficient"}}, {{"addition"}})) {
				return {"ParentCoefficientSizing"};
			}
			if(determine(clear_node, {
				{"target-coefficient"},
				{"parent-coefficient"}
			}, {{"addition"}})) {
				return {"SmartSizing"};
			}
		}
		return {};
	}
}