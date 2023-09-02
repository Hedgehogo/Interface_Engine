#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include <string>
#include "IE/Modules/yaml-cpp/yaml.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicOpenUrlAction : public BasicBaseKeyAction<T> {
	public:
		struct Make : public BasicKeyAction<T>::Make {
			std::string url;
			
			Make(const std::string& url);
			
			BasicOpenUrlAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
		BasicOpenUrlAction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		explicit BasicOpenUrlAction(const std::string& url);
		
		BasicOpenUrlAction<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		std::string url;
	};
	
	using OpenUrlAction = BasicOpenUrlAction<>;
	
	template<typename T>
	struct DecodePointer<BasicOpenUrlAction<T> > {
		static bool decodePointer(const YAML::Node& node, BasicOpenUrlAction<T>*& openUrlInteraction);
	};
	
	bool determineUrl(const YAML::Node& node);
}

#include "BasicOpenUrlAction.inl"
