#pragma once

#include "ui/interaction/event/key/simple/keyEventSimple.hpp"
#include "../../iSValue.hpp"

namespace ui {
	template<typename T>
	class SetSValueEvent : public KeyEvent_Simple{
	protected:
		PISValue<T> value;
		T variable;
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		SetSValueEvent(const PISValue<T>& value, T variable);
		
		SetSValueEvent<T>* copy() override;
	};
	
	template<typename T>
	struct DecodePointer<SetSValueEvent<T>> {
		static bool decodePointer(const YAML::Node& node, SetSValueEvent<T>*& setSValueEvent);
	};
	
	using SetSintEvent = SetSValueEvent<int>;
	using SetSfloatEvent = SetSValueEvent<float>;
}

#include "setSValueEvent.inl"
