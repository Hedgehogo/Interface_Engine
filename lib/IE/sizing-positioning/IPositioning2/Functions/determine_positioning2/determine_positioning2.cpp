#include "determine_positioning2.hpp"
#include "IE/ieml/determine/determine.hpp"

namespace ie {
	auto determine_positioning2(ieml::Node const& node) -> orl::Option<std::string> {
		auto& clear_node{node.get_clear()};
		if(clear_node.is_raw() ||
		   determine(clear_node, {
			   {"horizontal"},
			   {"vertical"}
		   }) ||
		   determine(clear_node, {{"coefficient"}}, {
			   {"relative"},
			   {"offset"}
		   }) ||
		   determine(clear_node, {
			   {"parent-coefficient"},
			   {"object-coefficient"}
		   }, {{"offset"}}) ||
		   determine(clear_node, {
			   {"target-coefficient"},
			   {"object-coefficient"}
		   }, {{"offset"}}) ||
		   determine(clear_node, {
			   {"parent-location"},
			   {"object-location"}
		   }, {{"offset"}})) {
			return {"Positioning2"};
		}
		return {};
	}
}