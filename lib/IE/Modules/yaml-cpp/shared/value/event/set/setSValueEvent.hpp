#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "../../iSValue.hpp"

namespace ie {
	template<typename T>
	class SetSValueEvent : public BaseKeyEvent {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		SetSValueEvent(const PISValue<T>& value, T variable);
		
		SetSValueEvent<T>* copy() override;
	
	protected:
		PISValue<T> value;
		T variable;
	};
	
	template<typename T>
	struct DecodePointer<SetSValueEvent<T> > {
		static bool decodePointer(const YAML::Node& node, SetSValueEvent<T>*& setSValueEvent);
	};
	
	using SetSintEvent = SetSValueEvent<int>;
	using SetSfloatEvent = SetSValueEvent<float>;
}

#include "setSValueEvent.inl"
