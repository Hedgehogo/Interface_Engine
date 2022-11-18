#include "openUrlEvent.hpp"
#include "../../../../../modules/appendix/openUrl/openUrl.hpp"

namespace ui {
	OpenUrlEvent::OpenUrlEvent(const std::string &url) : url(url) {}

	void OpenUrlEvent::startPressed() {}

	void OpenUrlEvent::stopPressed() {
		openUrl(url);
	}

	void OpenUrlEvent::whilePressed() {}

	void OpenUrlEvent::whileNotPressed() {}

	OpenUrlEvent *OpenUrlEvent::copy() {
		return new OpenUrlEvent{url};
	}

	bool convertPointer(const YAML::Node &node, OpenUrlEvent *&openUrlInteraction) {
		openUrlInteraction = new OpenUrlEvent{
			(node.IsScalar() ? node : node["url"]).as<std::string>()
		};
		return true;
	}

	bool determineUrl(const YAML::Node &node){
		if (node.IsScalar()){
			std::string url{node.as<std::string>()};
			return url.substr(0, 7) == "file://" || url.substr(0, 7) == "http://" || url.substr(0, 8) == "https://";
		}
		return false;
	}
} // ui