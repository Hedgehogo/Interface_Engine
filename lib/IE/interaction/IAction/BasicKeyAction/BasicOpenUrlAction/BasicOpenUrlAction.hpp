#pragma once

#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include <string>
#include "IE/modules/yaml-cpp/yaml.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/determine/determine.hpp"

namespace ie {
	template<typename T>
	class BasicOpenUrlAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicOpenUrlAction : public BasicKeyAction<T> {
			std::string url;
			
			BasicOpenUrlAction(const std::string& url);
			
			ie::BasicOpenUrlAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicOpenUrlAction : public BasicBaseKeyAction<T> {
	public:
		using Make = make_system::BasicOpenUrlAction<T>;
		
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