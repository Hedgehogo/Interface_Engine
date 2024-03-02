#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/ISReadable/ISReadable.hpp"
#include "../BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	template<typename T_, typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
	class BasicSetSValueAction;
	
	namespace make_system {
		template<typename T_, typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
		struct BasicSetSValueAction : public BasicKeyAction<T_> {
			MakeDyn<Value_> value;
			typename Value_::T constant;
			
			BasicSetSValueAction(MakeDyn<Value_>&& value, typename Value_::T constant);
			
			auto make(BasicActionInitInfo<T_> init_info) -> ie::BasicSetSValueAction<T_, Value_>*;
		};
	}
}

template<typename T_, typename Value_>
struct ieml::Decode<char, ie::make_system::BasicSetSValueAction<T_, Value_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicSetSValueAction<T_, Value_> >;
};

namespace ie {
	template<typename T_, typename Value_, typename>
	class BasicSetSValueAction : public BasicBaseKeyAction<T_> {
	public:
		using Make = make_system::BasicSetSValueAction<T_, Value_>;
		
		BasicSetSValueAction(Make&& make, BasicActionInitInfo<T_> init_info);
	
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		Value_& value;
		typename Value_::T constant;
	};
	
	template<typename T_>
	using SetSValueAction = BasicSetSValueAction<std::monostate, ISMutable<T_> >;
	
	using SetSBoolAction = SetSValueAction<bool>;
	using SetSFloatAction = SetSValueAction<float>;
	using SetSIntAction = SetSValueAction<int>;
	using SetSSizeAction = SetSValueAction<size_t>;
}

#include "BasicSetSValueAction.inl"
