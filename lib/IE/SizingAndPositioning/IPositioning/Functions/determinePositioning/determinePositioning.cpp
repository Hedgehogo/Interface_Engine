#include "determinePositioning.hpp"
#include "../../../../Modules/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ie {
	bool determinePositioning(const YAML::Node& node, std::string& type) {
		if(node.IsScalar()) {
			type = "InternalPositioning";
			return true;
		} else {
			if(determine(node, {{"coefficient"}}, {{"offset"}})) {
				type = "InternalPositioning";
				return true;
			}
			if(determine(node, {{"parent-coefficient"},
								{"object-coefficient"}}, {{"offset"}})) {
				type = "MatchPositioning";
				return true;
			}
			if(determine(node, {{"target-coefficient"},
								{"object-coefficient"}}, {{"offset"}})) {
				type = "MatchTargetPositioning";
				return true;
			}
			if(determine(node, {{"parent-side"},
								{"object-side"}}, {{"offset"}})) {
				type = "MatchSidesPositioning";
				return true;
			}
		}
		return false;
	}
}
