#pragma once

#include <string>
#include <IE/interaction/IAction/IBasicTouchAction/IBasicTouchAction.hpp>
#include <IE/ieml/shortcuts/shortcuts.hpp>

namespace ie {
	class ConsoleCommandAction : public BaseTouchAction {
	public:
	struct Make : public BaseKeyAction::Make {
		std::string command;
		
		explicit Make(std::string command);
		
		auto make(ActionInitInfo init_info) -> ConsoleCommandAction* override;
	};
		
		explicit ConsoleCommandAction(Make&& make, ActionInitInfo init_info);
	
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		std::string command;
	};
	
	extern "C" {
		auto init() -> void;
	}
}

template<>
struct ieml::Decode<char, ie::ConsoleCommandAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ConsoleCommandAction::Make>;
};
