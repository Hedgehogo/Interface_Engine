#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "IE/Modules/yaml-cpp/shared/value/general/sValue.hpp"

namespace ie {
	class Switcher;
	
	class SwitcherEvent : public BaseKeyEvent {
	public:
		SwitcherEvent(PSbool value);
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		SwitcherEvent* copy() override;
		
	protected:
		PSbool value;
	};
	
	template<>
	struct DecodePointer<SwitcherEvent> {
		static bool decodePointer(const YAML::Node& node, SwitcherEvent*& switcherEvent);
	};
	
}