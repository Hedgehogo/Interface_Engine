#include "ConsoleCommandAction.hpp"
#include <IE/Modules/yaml-cpp/yaml-builder/shortcut/shortcut.hpp>

namespace ie {
	ConsoleCommandAction::ConsoleCommandAction(const std::string& command) : command(command) {}
	
	ConsoleCommandAction* ConsoleCommandAction::copy() {
		return new ConsoleCommandAction{*this};
	}
	
	void ConsoleCommandAction::start_pressed() {}
	
	void ConsoleCommandAction::stop_pressed() {
		system(command.c_str());
	}
	
	void ConsoleCommandAction::while_pressed() {}
	
	void ConsoleCommandAction::while_not_pressed() {}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<ConsoleCommandAction>::decode_pointer(const YAML::Node& node, ConsoleCommandAction*& console_command_action) {
		console_command_action = new ConsoleCommandAction{
			node["command"].as<std::string>()
		};
		return true;

	}
	*/
	
	void init(int argc, char *argv[]) {
		inherit<ie::KeyAction, ie::ConsoleCommandAction>({"ConsoleCommandAction"});
	}
}