#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../iSValue.hpp"

namespace ie {
	template<typename T>
	class SetSValueAction : public BaseKeyAction {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		SetSValueAction(const PISValue<T>& value, T variable);
		
		SetSValueAction<T>* copy() override;
	
	protected:
		PISValue<T> value;
		T variable;
	};
	
	template<typename T>
	struct DecodePointer<SetSValueAction<T> > {
		static bool decodePointer(const YAML::Node& node, SetSValueAction<T>*& setSValueAction);
	};
	
	using SetSIntAction = SetSValueAction<int>;
	using SetSFloatAction = SetSValueAction<float>;
}

#include "SetSValueAction.inl"
