#include "determine_positioning.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/determine/Determine.hpp"

namespace ie {
	bool determine_positioning(const YAML::Node& node, std::string& type) {
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