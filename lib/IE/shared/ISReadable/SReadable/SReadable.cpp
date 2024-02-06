#include "SReadable.hpp"

namespace ie {
	bool Determine<SMBool::Make>::determine(ieml::Node const& node) {
		return node.is_raw();
	}
}
