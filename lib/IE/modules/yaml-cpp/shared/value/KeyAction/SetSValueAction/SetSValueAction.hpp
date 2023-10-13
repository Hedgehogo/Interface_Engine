#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../iSValue.hpp"

namespace ie {
	template<typename T>
	class SetSValueAction : public BaseKeyAction {
	public:
		struct Make : public BaseKeyAction::Make {
			PISValue<T> value;
			T constant;
			
			Make(PISValue<T> value, T constant);
			
			SetSValueAction* make(ActionInitInfo initInfo) override;
		};
		
		SetSValueAction(Make&& make, ActionInitInfo initInfo);
		
		SetSValueAction(PISValue<T> value, T constant);
		
		SetSValueAction<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		PISValue<T> value;
		T constant;
	};
	
	template<typename T>
	struct DecodePointer<SetSValueAction<T> > {
		static bool decodePointer(const YAML::Node& node, SetSValueAction<T>*& setSValueAction);
	};
	
	using SetSIntAction = SetSValueAction<int>;
	using SetSFloatAction = SetSValueAction<float>;
}

#include "SetSValueAction.inl"