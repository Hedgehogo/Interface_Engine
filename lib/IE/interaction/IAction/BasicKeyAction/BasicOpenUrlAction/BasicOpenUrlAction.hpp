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
			
			ie::BasicOpenUrlAction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicOpenUrlAction : public BasicBaseKeyAction<T> {
	public:
		using Make = make_system::BasicOpenUrlAction<T>;
		
		BasicOpenUrlAction(Make&& make, BasicActionInitInfo<T> init_info);
		
		explicit BasicOpenUrlAction(const std::string& url);
		
		BasicOpenUrlAction<T>* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		std::string url;
	};
	
	using OpenUrlAction = BasicOpenUrlAction<>;
	
	template<typename T>
	struct DecodePointer<BasicOpenUrlAction<T> > {
		static bool decode_pointer(const YAML::Node& node, BasicOpenUrlAction<T>*& open_url_interaction);
	};
	
	bool determine_url(const YAML::Node& node);
}

#include "BasicOpenUrlAction.inl"