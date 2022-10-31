#pragma once

#include "../simple/keyEventSimple.hpp"
#include <string>
#include "../../../../../modules/appendix/yaml-cpp/yaml.hpp"

namespace ui {

	class OpenUrlEvent : public KeyEvent_Simple{
	protected:
		std::string url;

		void startPressed() override;

		void stopPressed() override;

		void whilePressed() override;

		void whileNotPressed() override;

	public:
		explicit OpenUrlEvent(const std::string &url);

		OpenUrlEvent *copy() override;
	};

	bool convertPointer(const YAML::Node &node, OpenUrlEvent *&openUrlInteraction);
} // ui