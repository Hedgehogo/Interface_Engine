#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/ISReadable/ISReadable.hpp"
#include "IE/interaction/IAction/BasicTouchAction/BasicBaseTouchAction/BasicBaseTouchAction.hpp"

namespace ie {
	template<typename T_, typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
	class BasicAddSValueAction;
	
	namespace make_system {
		template<typename T_, typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
		struct BasicAddSValueAction : public BasicTouchAction<T_> {
			MakeDyn<Value_> value;
			typename Value_::T constant;
			
			BasicAddSValueAction(MakeDyn<Value_>&& value, typename Value_::T constant);
			
			auto make(BasicActionInitInfo<T_> init_info) -> ie::BasicAddSValueAction<T_, Value_>*;
		};
	}
}

template<typename T_, typename Value_>
struct ieml::Decode<char, ie::make_system::BasicAddSValueAction<T_, Value_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicAddSValueAction<T_, Value_> >;
};

namespace ie {
	template<typename T_, typename Value_, typename>
	class BasicAddSValueAction : public BasicBaseTouchAction<T_> {
	public:
		using Make = make_system::BasicAddSValueAction<T_, Value_>;
		
		BasicAddSValueAction(Make&& make, BasicActionInitInfo<T_> init_info);
	
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		Value_& value;
		typename Value_::T constant;
	};
	
	template<typename T_>
	using AddSValueAction = BasicAddSValueAction<std::monostate, ISMutable<T_> >;
	
	using AddSBoolAction = AddSValueAction<bool>;
	using AddSFloatAction = AddSValueAction<float>;
	using AddSIntAction = AddSValueAction<int>;
	using AddSSizeAction = AddSValueAction<size_t>;
}

#include "BasicAddSValueAction.inl"
