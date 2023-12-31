#include "determine.hpp"

namespace ie {
	namespace detail {
		bool IemlArg::present(ieml::MapData const& map) const {
			if(auto item{map.find(name)}; item != map.end()) {
				return !type.is_some() || item->second.get_type() == type.some();
			}
			return true;
		}
	}
	
	bool determine(ieml::Node const& node, std::initializer_list<detail::IemlArg> args, size_t size_addition) {
		if(auto map_result{node.get_map()}) {
			auto& map{map_result.ok()};
			return map.size() == args.size() + size_addition && std::all_of(
				args.begin(),
				args.end(),
				[&map](const detail::IemlArg& arg) {
					return arg.present(map);
				}
			);
		}
		return false;
	}
	
	namespace detail {
		template<class InputIt, class UnaryPredicate>
		size_t count_if(InputIt first, InputIt last, UnaryPredicate pred) {
			size_t count = 0;
			for(; first != last; ++first) {
				if(pred(*first)) {
					++count;
				}
			}
			return count;
		}
	}
	
	bool determine(
		ieml::Node const& node,
		std::initializer_list<detail::IemlArg> args,
		std::initializer_list<detail::IemlArg> opt_args,
		size_t size_addition
	) {
		if(auto map_result{node.get_map()}) {
			auto& map{map_result.ok()};
			return (map.size() >= args.size() + size_addition && map.size() <= args.size() + opt_args.size() + size_addition) && std::all_of(
				args.begin(),
				args.end(),
				[&map](const detail::IemlArg& arg) {
					return arg.present(map);
				}
			) && detail::count_if(
				opt_args.begin(),
				opt_args.end(),
				[&map](const detail::IemlArg& opt_arg) {
					return opt_arg.present(map);
				}
			) == map.size() - args.size() + size_addition;
		}
		return false;
	}
}
