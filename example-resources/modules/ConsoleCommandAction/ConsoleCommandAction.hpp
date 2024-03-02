#pragma once

#include <string>
#include <IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp>
#include <IE/modules/yaml-cpp/yaml.hpp>

namespace ie {
	class ConsoleCommandAction : public BaseKeyAction {
	public:
		explicit ConsoleCommandAction(std::string const& command);
		
		auto copy() -> ConsoleCommandAction* override;
	
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		std::string command;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<ConsoleCommandAction> {
		static bool decode_pointer(const YAML::Node& node, ConsoleCommandAction*& console_command_action);
	};
	*/
	
	extern "C" {
		auto init(int argc, char *argv[]) -> void;
	}
}
