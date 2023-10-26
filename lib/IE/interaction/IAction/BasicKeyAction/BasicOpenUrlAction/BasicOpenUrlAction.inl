#include "IE/utils/network/open_url/open_url.hpp"

namespace ie {
	namespace make_system {
		template<typename T>
		BasicOpenUrlAction<T>::BasicOpenUrlAction(const std::string& url) : url(url) {
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
	
	template<typename T>
	bool DecodePointer<BasicOpenUrlAction<T> >::decode_pointer(const YAML::Node& node, BasicOpenUrlAction<T>*& open_url_interaction) {
		open_url_interaction = new BasicOpenUrlAction<T>{
			(node.IsScalar() ? node : node["url"]).as<std::string>()
		};
		return true;
	}
}