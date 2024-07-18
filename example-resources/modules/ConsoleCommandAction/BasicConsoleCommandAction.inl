#include <utility>

namespace ie {
	namespace make_system {
		template<typename A_>
		BasicConsoleCommandAction<A_>::BasicConsoleCommandAction(std::string command) : command(std::move(command)) {
		}
		
		template<typename A_>
		auto BasicConsoleCommandAction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicConsoleCommandAction<A_>* {
			return new ie::BasicConsoleCommandAction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicConsoleCommandAction<A_>::BasicConsoleCommandAction(Make&& make, BasicActionInitInfo<A_>) : command_(std::move(make.command)) {
	}
	
	template<typename A_>
	BasicConsoleCommandAction<A_>::BasicConsoleCommandAction(std::string command) : command_(std::move(command)) {
	}
	
	template<typename A_>
	auto BasicConsoleCommandAction<A_>::update(bool active) -> void {
		if(active) {
			system(command_.c_str());
		}
	}
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicConsoleCommandAction<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicConsoleCommandAction<A_> > {
	auto& clear_node{node.get_clear()};
	for(auto map: clear_node.get_map_view().ok_or_none()) {
		return {{map.at("command").except().get_string().except()}};
	}
	return {{clear_node.get_string().except()}};
}