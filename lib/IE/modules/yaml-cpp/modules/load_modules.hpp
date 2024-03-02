#pragma once

#include <filesystem>

namespace ie {
	auto load_modules(int argc = 0, char* argv[0] = {}, std::filesystem::path modules_list = {}) -> void;
}