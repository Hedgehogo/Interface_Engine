#pragma once

#include <IEML/node.hpp>
#include "../OnlyDrawable.hpp"

namespace ie {
	orl::Option<OnlyDrawable*> video_convert(ieml::Node const& node);
}