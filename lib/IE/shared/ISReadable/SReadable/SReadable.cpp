#include "SReadable.hpp"

namespace ie {
	auto Determine<SMBool::Make>::determine(ieml::Node const& node) -> bool {
		return node.is_raw();
	}
}
