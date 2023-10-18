#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../ISValue.hpp"

namespace ie {
	template<typename T>
	class SetSValueAction : public BaseKeyAction {
	public:
		struct Make : public BaseKeyAction::Make {
			PISValue<T> value;
			T constant;
			
			Make(PISValue<T> value, T constant);
			
			SetSValueAction* make(ActionInitInfo init_info) override;
		};
		
		SetSValueAction(Make&& make, ActionInitInfo init_info);
		
		SetSValueAction(PISValue<T> value, T constant);
		
		SetSValueAction<T>* copy() override;
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		PISValue<T> value;
		T constant;
	};
	
	template<typename T>
	struct DecodePointer<SetSValueAction<T> > {
		static bool decode_pointer(const YAML::Node& node, SetSValueAction<T>*& set_s_value_action);
	};
	
	using SetSIntAction = SetSValueAction<int>;
	using SetSFloatAction = SetSValueAction<float>;
}

#include "SetSValueAction.inl"