#include "determine.hpp"

namespace ie {
	namespace detail {
		auto IemlArg::present(ieml::MapData const& map) const -> bool {
			if(auto item{map.find(name)}; item != map.end()) {
				return !type.is_some() || item->second.get_type() == type.some();
			}
			return true;
		}
	}
	
	auto determine(ieml::Node const& node, std::initializer_list<detail::IemlArg> args, size_t size_addition) -> bool {
		for(auto& map: node.get_map().ok_or_none()) {
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
		auto count_if(InputIt first, InputIt last, UnaryPredicate pred) -> size_t {
			size_t count = 0;
			for(; first != last; ++first) {
				if(pred(*first)) {
					++count;
				}
			}
			return count;
		}
	}
	
	auto determine(
		ieml::Node const& node,
		std::initializer_list<detail::IemlArg> args,
		std::initializer_list<detail::IemlArg> opt_args,
		size_t size_addition
	) -> bool {
		for(auto& map: node.get_map().ok_or_none()) {
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
