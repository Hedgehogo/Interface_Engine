#include "../../../../../modules/appendix/openUrl/openUrl.hpp"

namespace ui {
	template<typename T>
	BasicOpenUrlEvent<T>::BasicOpenUrlEvent(const std::string& url) : url(url) {
	}
	
	template<typename T>
	void BasicOpenUrlEvent<T>::startPressed() {
	}
	
	template<typename T>
	void BasicOpenUrlEvent<T>::stopPressed() {
		openUrl(url);
	}
	
	template<typename T>
	void BasicOpenUrlEvent<T>::whilePressed() {
	}
	
	template<typename T>
	void BasicOpenUrlEvent<T>::whileNotPressed() {
	}
	
	template<typename T>
	BasicOpenUrlEvent<T>* BasicOpenUrlEvent<T>::copy() {
		return new BasicOpenUrlEvent<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<BasicOpenUrlEvent<T> >::decodePointer(const YAML::Node& node, BasicOpenUrlEvent<T>*& openUrlInteraction) {
		openUrlInteraction = new OpenUrlEvent {
			(node.IsScalar() ? node : node["url"]).as<std::string>()
		};
		return true;
	}
}