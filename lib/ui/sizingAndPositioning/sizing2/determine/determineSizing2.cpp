#include "determineSizing2.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
	bool determineSizing2(const YAML::Node &node, std::string &type) {
		if(node.IsScalar()) {
			type = "Sizing2";
			return true;
		} else {
			if(node["ratio"].IsDefined() || node["horizontal"].IsDefined()) {
				if(determine(node, {}, {{"relative"}, {"ratio"}, {"horizontal"}}) ||
				   determine(node, {{"const-size"}}, {{"ratio"}, {"horizontal"}}) ||
				   determine(node, {{"coefficient"}}, {{"addition"}, {"relative"}, {"ratio"}, {"horizontal"}}) ||
				   determine(node, {{"target-coefficient"}, {"parent-coefficient"}}, {{"addition"}, {"ratio"}, {"horizontal"}})) {
					type = "ConstRatioSizing2";
					return true;
				}
			} else {
				if(determine(node, {{"horizontal"}, {"vertical"}}) ||
				   determine(node, {{"relative"}}) ||
				   determine(node, {{"const-size"}}) ||
				   determine(node, {{"coefficient"}}, {{"addition"}, {"relative"}}) ||
				   determine(node, {{"target-coefficient"}, {"parent-coefficient"}}, {{"addition"}})) {
					type = "Sizing2";
					return true;
				}
			}
			if(determine(node, {{"sizing"}}, {{"ratio"}, {"horizontal"}})) {
				type = "ConstRatioSizing2";
				return true;
			}
		}
		return false;
	}
}
