#pragma once

#include "../../../../../../../Interaction/IEvent/KeyEvent/BaseKeyEvent/BaseKeyEvent.hpp"
#include "modules/appendix/yaml-cpp/shared/value/general/sValue.hpp"

namespace ui {
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