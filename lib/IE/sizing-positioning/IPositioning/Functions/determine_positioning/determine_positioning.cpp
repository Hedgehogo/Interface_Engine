#include "determine_positioning.hpp"
#include "IE/ieml/determine/determine.hpp"

namespace ie {
	orl::Option<std::string> determine_positioning(ieml::Node const& node) {
		auto& clear_node{node.get_clear()};
		if(clear_node.is_raw()) {
			return {"InternalPositioning"};
		} else {
			if(determine(clear_node, {{"coefficient"}}, {{"offset"}})) {
				return {"InternalPositioning"};
			}
			if(determine(clear_node, {
				{"parent-coefficient"},
				{"object-coefficient"}
			}, {{"offset"}})) {
				return {"MatchPositioning"};
			}
			if(determine(clear_node, {
				{"target-coefficient"},
				{"object-coefficient"}
			}, {{"offset"}})) {
				return {"MatchTargetPositioning"};
			}
			if(determine(clear_node, {
				{"parent-side"},
				{"object-side"}
			}, {{"offset"}})) {
				return {"MatchSidesPositioning"};
			}
		}
		return {};
	}
}