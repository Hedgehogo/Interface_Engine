#pragma once

#include <filesystem>

namespace ui{
	void loadModules(int argc = 0, char *argv[] = {}, std::filesystem::path modulesList = {});
}