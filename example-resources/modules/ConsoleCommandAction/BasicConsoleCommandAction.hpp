#pragma once

#include <string>
#include <IE/interaction/IAction/IBasicActivityAction/IBasicActivityAction.hpp>
#include <IE/ieml/shortcuts/shortcuts.hpp>

namespace ie {
	template<typename A_>
	class BasicConsoleCommandAction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicConsoleCommandAction : public virtual IBasicActivityAction<A_> {
			std::string command;
			
			BasicConsoleCommandAction(std::string command);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicConsoleCommandAction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicConsoleCommandAction : public virtual IBasicActivityAction<A_> {
	public:
		using Make = make_system::BasicConsoleCommandAction<A_>;
		
		BasicConsoleCommandAction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		BasicConsoleCommandAction(std::string command);
		
		auto update(bool active) -> void override;
	
	protected:
		std::string command_;
	};
	
	using ConsoleCommandAction = BasicConsoleCommandAction<>;
	
	extern "C" {
		auto init() -> void;
	}
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicConsoleCommandAction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicConsoleCommandAction<A_> >;
};

#include "BasicConsoleCommandAction.inl"