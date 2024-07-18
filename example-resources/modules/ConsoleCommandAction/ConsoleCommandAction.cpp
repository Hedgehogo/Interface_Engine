#include "ConsoleCommandAction.hpp"

#include <utility>

namespace ie {
	ConsoleCommandAction::Make::Make(std::string command) : command(std::move(command)) {
	}
	
	auto ConsoleCommandAction::Make::make(ActionInitInfo init_info) -> ConsoleCommandAction*{
		return new ConsoleCommandAction{std::move(*this), init_info};
	}
	
	ConsoleCommandAction::ConsoleCommandAction(Make&& make, ActionInitInfo init_info) : command(make.command) {}
	
	auto ConsoleCommandAction::start_pressed() -> void {}
	
	auto ConsoleCommandAction::stop_pressed() -> void {
		system(command.c_str());
	}
	
	auto ConsoleCommandAction::while_pressed() -> void {}
	
	auto ConsoleCommandAction::while_not_pressed() -> void {}

	extern "C" {
		auto init() -> void {
			add_type_with_make<BaseKeyAction, ConsoleCommandAction>("ConsoleCommandAction", "ConsoleCommandA");
		}
	}
}

auto ieml::Decode<char, ie::ConsoleCommandAction::Make>::decode(ieml::Node const& node) -> orl::Option<ie::ConsoleCommandAction::Make>{
	auto map{node.get_map_view().except()};
	return ie::ConsoleCommandAction::Make{
		map.at("command").except().as<std::string>().except()
	};
}
