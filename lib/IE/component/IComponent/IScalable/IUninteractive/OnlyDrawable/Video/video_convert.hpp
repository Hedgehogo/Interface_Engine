#pragma once

#include "../OnlyDrawable.hpp"

namespace ie {
	bool video_convert(const YAML::Node& node, OnlyDrawable*& video);
}