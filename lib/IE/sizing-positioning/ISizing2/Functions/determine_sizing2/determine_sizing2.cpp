#include "determine_sizing2.hpp"
#include "IE/ieml/determine/determine.hpp"

namespace ie {
	auto determine_sizing2(ieml::Node const& node) -> orl::Option<std::string> {
		auto& clear_node{node.get_clear()};
		if(clear_node.is_raw()) {
			return {"Sizing2"};
		} else {
			if(clear_node.at("ratio").is_ok() || clear_node.at("horizontal").is_ok()) {
				if(
					determine(clear_node, {}, {
						{"relative"},
						{"ratio"},
						{"horizontal"}
					}) ||
					determine(clear_node, {{"const-size"}}, {
						{"ratio"},
						{"horizontal"}
					}) ||
					determine(clear_node, {{"coefficient"}}, {
						{"addition"},
						{"relative"},
						{"ratio"},
						{"horizontal"}
					}) ||
					determine(
						clear_node, {
							{"target-coefficient"},
							{"parent-coefficient"}
						}, {
							{"addition"},
							{"ratio"},
							{"horizontal"}
						}
					)
					) {
					return {"ConstRatioSizing2"};
				}
			} else {
				if(
					determine(clear_node, {
						{"horizontal"},
						{"vertical"}
					}) ||
					determine(clear_node, {{"relative"}}) ||
					determine(clear_node, {{"const-size"}}) ||
					determine(clear_node, {{"coefficient"}}, {
						{"addition"},
						{"relative"}
					}) ||
					determine(clear_node, {
						{"target-coefficient"},
						{"parent-coefficient"}
					}, {{"addition"}})
					) {
					return {"Sizing2"};
				}
			}
			if(determine(clear_node, {{"sizing"}}, {
				{"ratio"},
				{"horizontal"}
			})) {
				return {"ConstRatioSizing2"};
			}
		}
		return {};
	}
}