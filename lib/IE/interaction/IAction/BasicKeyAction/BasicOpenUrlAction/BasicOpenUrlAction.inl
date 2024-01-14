#include "IE/utils/network/open_url/open_url.hpp"

namespace ie {
	namespace make_system {
		template<typename T>
		BasicOpenUrlAction<T>::BasicOpenUrlAction(std::string url) : url(std::move(url)) {
		}
		
		template<typename T>
		ie::BasicOpenUrlAction<T>* BasicOpenUrlAction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicOpenUrlAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicOpenUrlAction<T>::BasicOpenUrlAction(Make&& make, BasicActionInitInfo<T>) :
		url_(std::move(make.url)) {
	}
	
	template<typename T>
	BasicOpenUrlAction<T>::BasicOpenUrlAction(const std::string& url) : url_(url) {
	}
	
	template<typename T>
	void BasicOpenUrlAction<T>::start_pressed() {
	}
	
	template<typename T>
	void BasicOpenUrlAction<T>::stop_pressed() {
		open_url(url_);
	}
	
	template<typename T>
	void BasicOpenUrlAction<T>::while_pressed() {
	}
	
	template<typename T>
	void BasicOpenUrlAction<T>::while_not_pressed() {
	}
	
	template<typename T>
	BasicOpenUrlAction<T>* BasicOpenUrlAction<T>::copy() {
		return new BasicOpenUrlAction<T>{*this};
	}
}

template<typename T>
orl::Option<ie::make_system::BasicOpenUrlAction<T> > ieml::Decode<char, ie::make_system::BasicOpenUrlAction<T> >::decode(ieml::Node const& node) {
	auto& clear_node{node.get_clear()};
	if(auto map_view{clear_node.get_map_view()}) {
		return {{map_view.ok().at("url").except().get_string().except()}};
	}
	return {{clear_node.get_string().except()}};
}