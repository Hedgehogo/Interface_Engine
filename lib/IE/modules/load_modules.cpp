#include <IEML/parser.hpp>
#include "load_modules.hpp"
#include "load_c_modules/load_c_modules.hpp"

auto ie::load_modules(int argc, char* argv[0], std::filesystem::path modules_list) -> void {
	if(!modules_list.empty()) {
		auto libs{ieml::from_file(modules_list.string())};
		load_c_modules(libs, argc, argv);
	}
}
