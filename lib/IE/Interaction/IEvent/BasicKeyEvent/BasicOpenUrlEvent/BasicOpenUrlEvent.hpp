#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include <string>
#include "IE/Modules/yaml-cpp/yaml.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicOpenUrlEvent : public BasicBaseKeyEvent<T> {
	public:
		explicit BasicOpenUrlEvent(const std::string& url);
		
		BasicOpenUrlEvent<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		std::string url;
	};
	
	using OpenUrlEvent = BasicOpenUrlEvent<>;
	
	template<typename T>
	struct DecodePointer<BasicOpenUrlEvent<T> > {
		static bool decodePointer(const YAML::Node& node, BasicOpenUrlEvent<T>*& openUrlInteraction);
	};
	
	bool determineUrl(const YAML::Node& node);
}

#include "BasicOpenUrlEvent.inl"
