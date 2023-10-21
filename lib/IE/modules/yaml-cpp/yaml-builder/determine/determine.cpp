#include "determine.hpp"

namespace ie {
	namespace detail {
		bool YamlArg::present(const YAML::Node& node) const {
			return node[name].IsDefined() && (type == YAML::NodeType::Undefined || type == node[name].Type());
		}
	}
	
	bool determine(const YAML::Node& node, std::initializer_list<detail::YamlArg> args, size_t size_addition) {
		return node.size() == args.size() + size_addition &&
			   std::all_of(args.begin(), args.end(), [&node](const detail::YamlArg& arg) {
				   return arg.present(node);
			   });
	}

	namespace detail{
		template<class InputIt, class UnaryPredicate>
		size_t count_if(InputIt first, InputIt last, UnaryPredicate p) {
			size_t count = 0;
			for(; first != last; ++first) {
				if(p(*first)) {
					++count;
				}
			}
			return count;
		}
	}
	
	bool determine(const YAML::Node& node, std::initializer_list<detail::YamlArg> args, std::initializer_list<detail::YamlArg> opt_args, size_t size_addition) {
		return (node.size() >= args.size() + size_addition && node.size() <= args.size() + opt_args.size() + size_addition) &&
			   std::all_of(args.begin(), args.end(), [&node](const detail::YamlArg& arg) {
				   return arg.present(node);
			   }) &&
			   detail::count_if(opt_args.begin(), opt_args.end(), [&node](const detail::YamlArg& opt_arg) {
				   return opt_arg.present(node);
			   }) == node.size() - args.size() + size_addition;
	}
}
