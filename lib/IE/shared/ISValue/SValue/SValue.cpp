#include "SValue.hpp"

namespace ie {
	bool Determine<SBool::Make>::determine(ieml::Node const& node) {
		return node.is_raw();
	}
}
