#include "BasicConsoleCommandAction.hpp"

namespace ie{
	extern "C" {
		auto init() -> void {
			add_type_with_make<IActivityAction, ConsoleCommandAction>("ConsoleCommandAction", "ConsoleCommandA");
		}
	}
}