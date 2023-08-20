#pragma once

#include <IE/interaction/event/key/simple/keyEventSimple.hpp>
#include <modules/appendix/yaml-cpp/yaml.hpp>
#include <string>
#include <modules/appendix/yaml-cpp/yamlBuilder/base/baseYamlBuilder.hpp>

namespace ui {
	class ConsoleCommandEvent : public KeyEvent_Simple{
	protected:
		std::string command;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
	public:
		explicit ConsoleCommandEvent(const std::string& command);
		
		ConsoleCommandEvent* copy() override;
	};
	
	template<>
	struct DecodePointer<ConsoleCommandEvent> {
		static bool decodePointer(const YAML::Node& node, ConsoleCommandEvent*& consoleCommandEvent);
	};
	
	extern "C" {
		void init(int argc, char *argv[]);
	}
}
