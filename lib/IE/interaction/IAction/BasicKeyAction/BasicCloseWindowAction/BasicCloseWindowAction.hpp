#pragma once

#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	template<typename T>
	class BasicCloseWindowAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicCloseWindowAction : public BasicKeyAction<T> {
			ie::BasicCloseWindowAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicCloseWindowAction : public BasicBaseKeyAction<T> {
	public:
		using Make = make_system::BasicCloseWindowAction<T>;
		
		BasicCloseWindowAction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicCloseWindowAction();
		
		void init(BasicActionInitInfo<T> initInfo) override;
		
		BasicCloseWindowAction<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		sf::RenderWindow* window;
	};
	
	using CloseWindowAction = BasicCloseWindowAction<std::monostate>;
	
	template<typename T>
	struct DecodePointer<BasicCloseWindowAction<T> > {
		static bool decodePointer(const YAML::Node&, BasicCloseWindowAction<T>*& closeWindowAction);
	};
}

#include "BasicCloseWindowAction.inl"