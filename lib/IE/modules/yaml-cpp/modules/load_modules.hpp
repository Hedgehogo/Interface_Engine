#pragma once

#include <filesystem>

namespace ie {
	void load_modules(int argc = 0, char* argv[0] = {}, std::filesystem::path modulesList = {});
}