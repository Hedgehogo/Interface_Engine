#include "IE/utils/network/open_url/open_url.hpp"

namespace ie {
	namespace make_system {
		template<typename A_>
		BasicOpenUrlAction<A_>::BasicOpenUrlAction(std::string url) : url(std::move(url)) {
		}
		
		template<typename A_>
		auto BasicOpenUrlAction<A_>::make(BasicActionInitInfo<A_> init_info) -> ie::BasicOpenUrlAction<A_>* {
			return new ie::BasicOpenUrlAction<A_>{std::move(*this), init_info};
		}
	}
	
	template<typename A_>
	BasicOpenUrlAction<A_>::BasicOpenUrlAction(Make&& make, BasicActionInitInfo<A_>) : url_(std::move(make.url)) {
	}
	
	template<typename A_>
	BasicOpenUrlAction<A_>::BasicOpenUrlAction(std::string url) : url_(std::move(url)) {
	}
	
	template<typename A_>
	auto BasicOpenUrlAction<A_>::update(bool active) -> void {
		if(active) {
			open_url(url_);
		}
	}
}

template<typename A_>
auto ieml::Decode<char, ie::make_system::BasicOpenUrlAction<A_> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicOpenUrlAction<A_> > {
	auto& clear_node{node.get_clear()};
	for(auto map: clear_node.get_map_view().ok_or_none()) {
		return {{map.at("url").except().get_string().except()}};
	}
	return {{clear_node.get_string().except()}};
}