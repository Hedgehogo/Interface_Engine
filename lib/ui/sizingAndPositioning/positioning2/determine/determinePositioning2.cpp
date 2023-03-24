#include "determinePositioning2.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
	bool determinePositioning2(const YAML::Node &node, std::string &type) {
		if(node.IsScalar() ||
		   determine(node, {{"horizontal"}, {"vertical"}}) ||
		   determine(node, {{"coefficient"}}, {{"relative"}, {"offset"}}) ||
		   determine(node, {{"parent-coefficient"}, {"object-coefficient"}}, {{"offset"}}) ||
		   determine(node, {{"target-coefficient"}, {"object-coefficient"}}, {{"offset"}}) ||
		   determine(node, {{"parent-location"}, {"object-location"}}, {{"offset"}})) {
			type = "Positioning2";
			return true;
		}
		return false;
	}
}
