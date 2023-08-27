#include "ConsoleCommandAction.hpp"
#include <IE/Modules/yaml-cpp/yamlBuilder/shortcut/shortcut.hpp>

namespace ie {
	ConsoleCommandAction::ConsoleCommandAction(const std::string& command) : command(command) {}
	
	void ConsoleCommandAction::startPressed() {}
	
	void ConsoleCommandAction::stopPressed() {
		system(command.c_str());
	}
	
	void ConsoleCommandAction::whilePressed() {}
	
	void ConsoleCommandAction::whileNotPressed() {}
	
	ConsoleCommandAction* ConsoleCommandAction::copy() {
		return new ConsoleCommandAction{*this};
	}
	
	bool DecodePointer<ConsoleCommandAction>::decodePointer(const YAML::Node& node, ConsoleCommandAction*& consoleCommandAction) {
		consoleCommandAction = new ConsoleCommandAction{
			node["command"].as<std::string>()
		};
		return true;
	}
	
	void init(int argc, char *argv[]) {
		inherit<ie::ConsoleCommandAction>("KeyAction", {"ConsoleCommandAction"});
	}
}