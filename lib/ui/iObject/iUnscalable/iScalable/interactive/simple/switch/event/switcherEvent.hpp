#pragma once

#include "../../../../../../../interaction/event/key/simple/keyEventSimple.hpp"
#include "modules/appendix/yaml-cpp/shared/value/general/sValue.hpp"

namespace ui {
	class Switcher;
	
	class SwitcherEvent : public KeyEvent_Simple {
	protected:
		PSbool value;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		SwitcherEvent(PSbool value);
		
		SwitcherEvent* copy() override;
	};
	
	template<>
	struct DecodePointer<SwitcherEvent> {
		static bool decodePointer(const YAML::Node& node, SwitcherEvent*& switcherEvent);
	};
	
}