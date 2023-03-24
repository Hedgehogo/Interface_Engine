#include "determine.hpp"

namespace ui {
	namespace detail {
		bool YamlArg::present(const YAML::Node& node) const {
			return node[name].IsDefined() && (type == YAML::NodeType::Undefined || type == node[name].Type());
		}
	}
	
	bool determine(const YAML::Node& node, std::initializer_list<detail::YamlArg> args, size_t sizeAddition) {
		return node.size() == args.size() + sizeAddition &&
			   std::all_of(args.begin(), args.end(), [&node](const detail::YamlArg& arg) { return arg.present(node); });
	}
	
	bool determine(const YAML::Node& node, std::initializer_list<detail::YamlArg> args, std::initializer_list<detail::YamlArg> optArgs, size_t sizeAddition) {
		return (node.size() >= args.size() + sizeAddition && node.size() <= args.size() + optArgs.size() + sizeAddition) &&
			   std::all_of(args.begin(), args.end(), [&node](const detail::YamlArg& arg) { return arg.present(node); }) &&
			   std::count_if(optArgs.begin(), optArgs.end(), [&node](const detail::YamlArg &optArg) { return optArg.present(node); }) == node.size() - args.size() + sizeAddition;
	}
}
