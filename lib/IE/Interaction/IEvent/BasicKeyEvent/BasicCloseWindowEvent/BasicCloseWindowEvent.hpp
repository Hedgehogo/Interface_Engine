#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "modules/appendix/yaml-cpp/yaml.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicCloseWindowEvent : public BasicBaseKeyEvent<T> {
	public:
		BasicCloseWindowEvent();
		
		void init(BasicInteractionInitInfo<T> initInfo) override;
		
		BasicCloseWindowEvent<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		sf::RenderWindow* window;
	};
	
	using CloseWindowEvent = BasicCloseWindowEvent<std::monostate>;
	
	template<typename T>
	struct DecodePointer<BasicCloseWindowEvent<T> > {
		static bool decodePointer(const YAML::Node&, BasicCloseWindowEvent<T>*& closeWindowEvent);
	};
}

#include "BasicCloseWindowEvent.inl"
