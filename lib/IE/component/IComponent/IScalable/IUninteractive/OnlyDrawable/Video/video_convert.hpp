#pragma once

#include <IEML/node.hpp>
#include "../OnlyDrawable.hpp"

namespace ie {
	orl::Option<OnlyDrawable::Make*> video_convert(ieml::Node const& node);
}