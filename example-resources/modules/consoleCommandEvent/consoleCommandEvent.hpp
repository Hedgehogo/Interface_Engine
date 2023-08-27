#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include <IE/Modules/yaml-cpp/yaml.hpp>
#include <string>
#include <IE/Modules/yaml-cpp/yamlBuilder/base/baseYamlBuilder.hpp>

namespace ie {
	class ConsoleCommandEvent : public BaseKeyEvent{
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
