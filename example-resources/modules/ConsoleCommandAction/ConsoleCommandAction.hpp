#pragma once

#include <string>
#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include <IE/Modules/yaml-cpp/yaml.hpp>
#include <IE/Modules/yaml-cpp/yaml-builder/base/BaseYamlBuilder.hpp>

namespace ie {
	class ConsoleCommandAction : public BaseKeyAction {
	protected:
		std::string command;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
	public:
		explicit ConsoleCommandAction(const std::string& command);
		
		ConsoleCommandAction* copy() override;
	};
	
	template<>
	struct DecodePointer<ConsoleCommandAction> {
		static bool decodePointer(const YAML::Node& node, ConsoleCommandAction*& consoleCommandAction);
	};
	
	extern "C" {
		void init(int argc, char *argv[]);
	}
}
