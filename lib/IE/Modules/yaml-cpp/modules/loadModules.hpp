#pragma once

#include <filesystem>

namespace ie {
	void loadModules(int argc = 0, char *argv[] = {}, std::filesystem::path modulesList = {});
}