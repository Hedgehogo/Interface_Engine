#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/ISReadable/ISReadable.hpp"
#include "../IBasicActivityAction.hpp"

namespace ie {
	template<typename A_, typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
	class BasicSetSValueAction;
	
	namespace make_system {
		template<typename A_, typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
		struct BasicSetSValueAction : public virtual IBasicActivityAction<A_> {
			MakeDyn<Value_> value;
			typename Value_::T constant;
			
			BasicSetSValueAction(MakeDyn<Value_>&& value, typename Value_::T constant);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicSetSValueAction<A_, Value_>*;
		};
	}
	
	template<typename A_, typename Value_, typename>
	class BasicSetSValueAction : public virtual IBasicActivityAction<A_> {
	public:
		using Make = make_system::BasicSetSValueAction<A_, Value_>;
		
		BasicSetSValueAction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto update(bool active) -> void override;
	
	protected:
		Value_& value;
		typename Value_::T constant;
	};
	
	template<typename A_>
	using SetSValueAction = BasicSetSValueAction<std::monostate, ISMutable<A_> >;
	
	using SetSBoolAction = SetSValueAction<bool>;
	using SetSFloatAction = SetSValueAction<float>;
	using SetSIntAction = SetSValueAction<int>;
	using SetSSizeAction = SetSValueAction<size_t>;
}

template<typename A_, typename Value_>
struct ieml::Decode<char, ie::make_system::BasicSetSValueAction<A_, Value_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicSetSValueAction<A_, Value_> >;
};

#include "BasicSetSValueAction.inl"
