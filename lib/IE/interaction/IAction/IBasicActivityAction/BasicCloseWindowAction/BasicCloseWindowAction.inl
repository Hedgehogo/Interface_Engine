#include "IE/window/Window/Window.hpp"

namespace ie {
	namespace make_system {
		template<typename A_>
		auto BasicCloseWindowAction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicCloseWindowAction<A_>* {
			return new ie::BasicCloseWindowAction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicCloseWindowAction<A_>::BasicCloseWindowAction(Make&&, BasicActionInitInfo<A_> init_info) :
		window_(&init_info.window) {
	}
	
	template<typename A_>
	auto BasicCloseWindowAction<A_>::update(bool active) -> void {
		if(active && window_->isOpen()) {
			window_->close();
		}
	}
}

template<typename A_>
auto ieml::Decode<char, ie::BasicCloseWindowAction<A_> >::decode(ieml::Node const&) -> orl::Option<ie::BasicCloseWindowAction<A_> > {
	return ie::BasicCloseWindowAction<A_>{};
}
