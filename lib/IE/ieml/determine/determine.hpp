#pragma once

#include <IEML/node.hpp>

namespace ie {
	namespace detail {
		struct IemlArg {
			std::string name;
			orl::Option<ieml::NodeType> type{};
			
			[[nodiscard]] auto present(ieml::MapData const& map) const -> bool;
		};
	}
	
	auto determine(ieml::Node const& node, std::initializer_list<detail::IemlArg> args, size_t size_addition = 0) -> bool;
	
	auto determine(
		ieml::Node const& node,
		std::initializer_list<detail::IemlArg> args,
		std::initializer_list<detail::IemlArg> opt_args,
		size_t size_addition = 0
	) -> bool;
}