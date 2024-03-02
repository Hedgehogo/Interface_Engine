#include "ConsoleCommandAction.hpp"

namespace ie {
	ConsoleCommandAction::ConsoleCommandAction(const std::string& command) : command(command) {}
	
	auto ConsoleCommandAction::copy() -> ConsoleCommandAction* {
		return new ConsoleCommandAction{*this};
	}
	
	auto ConsoleCommandAction::start_pressed() -> void {}
	
	auto ConsoleCommandAction::stop_pressed() -> void {
		system(command.c_str());
	}
	
	auto ConsoleCommandAction::while_pressed() -> void {}
	
	auto ConsoleCommandAction::while_not_pressed() -> void {}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<ConsoleCommandAction>::decode_pointer(const YAML::Node& node, ConsoleCommandAction*& console_command_action) {
		console_command_action = new ConsoleCommandAction{
			node["command"].as<std::string>()
		};
		return true;

	}
	*/
	
	auto init(int argc, char *argv[]) -> void {
		//inherit<ie::KeyAction, ie::ConsoleCommandAction>({"ConsoleCommandAction"});
	}
}