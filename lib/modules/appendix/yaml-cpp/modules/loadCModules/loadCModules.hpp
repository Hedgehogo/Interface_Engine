#pragma once

#include <filesystem>

namespace ui {
	
	void loadCModules(std::filesystem::path modulesList = {}, int argc = 0, char* argv[] = {});
	
}
