#pragma once

#include "../OnlyDrawable.hpp"

namespace ui {
	bool videoConvert(const YAML::Node& node, OnlyDrawable*& video);
}