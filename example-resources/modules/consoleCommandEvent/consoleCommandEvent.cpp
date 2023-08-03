#include "consoleCommandEvent.hpp"
#include <modules/appendix/yaml-cpp/yamlBuilder/shortcut/shortcut.hpp>

namespace ui {
	ConsoleCommandEvent::ConsoleCommandEvent(const std::string& command) : command(command) {}
	
	void ConsoleCommandEvent::startPressed() {}
	
	void ConsoleCommandEvent::stopPressed() {
		system(command.c_str());
	}
	
	void ConsoleCommandEvent::whilePressed() {}
	
	void ConsoleCommandEvent::whileNotPressed() {}
	
	ConsoleCommandEvent* ConsoleCommandEvent::copy() {
		return new ConsoleCommandEvent{*this};
	}
	
	bool DecodePointer<ConsoleCommandEvent>::decodePointer(const YAML::Node& node, ConsoleCommandEvent*& consoleCommandEvent) {
		consoleCommandEvent = new ConsoleCommandEvent{
			node["command"].as<std::string>()
		};
		return true;
	}
	
	void init(int argc, char *argv[]){
		inherit<ui::ConsoleCommandEvent>("ui::KeyEvent", {"ConsoleCommandE"});
	}
}