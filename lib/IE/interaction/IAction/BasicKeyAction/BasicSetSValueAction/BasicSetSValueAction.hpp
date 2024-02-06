#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/ISValue/ISValue.hpp"
#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	template<typename T_, typename Value_, typename = std::enable_if_t<is_shared<Value_> > >
	class BasicSetSValueAction;
	
	namespace make_system {
		template<typename T_, typename Value_, typename = std::enable_if_t<is_shared<Value_> > >
		struct BasicSetSValueAction : public BasicKeyAction<T_> {
			MakeDyn<Value_> value;
			typename Value_::T constant;
			
			BasicSetSValueAction(MakeDyn<Value_>&& value, typename Value_::T constant);
			
			ie::BasicSetSValueAction<T_, Value_>* make(BasicActionInitInfo<T_> init_info);
		};
	}
}

template<typename T_, typename Value_>
struct ieml::Decode<char, ie::make_system::BasicSetSValueAction<T_, Value_> > {
	static orl::Option<ie::make_system::BasicSetSValueAction<T_, Value_> > decode(ieml::Node const& node);
};

namespace ie {
	template<typename T_, typename Value_, typename>
	class BasicSetSValueAction : public BasicBaseKeyAction<T_> {
	public:
		using Make = make_system::BasicSetSValueAction<T_, Value_>;
		
		BasicSetSValueAction(Make&& make, BasicActionInitInfo<T_> init_info);
	
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		Value_& value;
		typename Value_::T constant;
	};
	
	template<typename T_>
	using SetSValueAction = BasicSetSValueAction<std::monostate, ISValue<T_> >;
	
	using SetSBoolAction = SetSValueAction<bool>;
	using SetSFloatAction = SetSValueAction<float>;
	using SetSIntAction = SetSValueAction<int>;
	using SetSUSizeAction = SetSValueAction<size_t>;
}

#include "BasicSetSValueAction.inl"
