#pragma once

#include "../simple/keyEventSimple.hpp"
#include <string>
#include "modules/appendix/yaml-cpp/yaml.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
	class OpenUrlEvent : public KeyEvent_Simple {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit OpenUrlEvent(const std::string& url);
		
		OpenUrlEvent* copy() override;
	
	protected:
		std::string url;
	};
	
	template<>
	struct DecodePointer<OpenUrlEvent> {
		static bool decodePointer(const YAML::Node& node, OpenUrlEvent*& openUrlInteraction);
	};
	
	bool determineUrl(const YAML::Node& node);
}