#pragma once

#include "../onlyDrawable.hpp"

namespace ui{
	bool videoConvert(const YAML::Node &node, OnlyDrawable *&video);
}