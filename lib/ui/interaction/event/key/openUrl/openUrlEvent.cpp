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
			node["url"].as<std::string>()
		};
		return true;
	}
} // ui