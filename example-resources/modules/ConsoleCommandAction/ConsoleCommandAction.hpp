#pragma once

#include <string>
#include <IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp>
#include <IE/modules/yaml-cpp/yaml.hpp>
#include <IE/modules/yaml-cpp/yaml-builder/IYamlBuilder/BaseYamlBuilder/BaseYamlBuilder.hpp>

namespace ie {
	class ConsoleCommandAction : public BaseKeyAction {
	public:
		explicit ConsoleCommandAction(const std::string& command);
		
		ConsoleCommandAction* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		std::string command;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<ConsoleCommandAction> {
		static bool decode_pointer(const YAML::Node& node, ConsoleCommandAction*& console_command_action);
	};
	*/
	
	extern "C" {
		void init(int argc, char *argv[]);
	}
}
