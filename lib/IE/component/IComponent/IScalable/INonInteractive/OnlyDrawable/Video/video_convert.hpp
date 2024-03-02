#pragma once

#include <IEML/node.hpp>
#include "../OnlyDrawable.hpp"

namespace ie {
	auto video_convert(ieml::Node const& node) -> orl::Option<OnlyDrawable::Make*>;
}