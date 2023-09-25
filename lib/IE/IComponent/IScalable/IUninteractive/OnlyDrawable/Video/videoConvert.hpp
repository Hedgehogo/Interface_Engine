#pragma once

#include "../OnlyDrawable.hpp"

namespace ie {
	bool videoConvert(const YAML::Node& node, OnlyDrawable*& video);
}