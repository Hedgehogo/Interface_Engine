#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/ISReadable/ISReadable.hpp"
#include "IE/interaction/IAction/IBasicActivityAction/IBasicActivityAction.hpp"

namespace ie {
	template<typename A_, typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
	class BasicAddSValueAction;
	
	namespace make_system {
		template<typename A_, typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
		struct BasicAddSValueAction : public virtual IBasicActivityAction<A_> {
			MakeDyn<Value_> value;
			typename Value_::T constant;
			
			BasicAddSValueAction(MakeDyn<Value_>&& value, typename Value_::T constant);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicAddSValueAction<A_, Value_>*;
		};
	}
}

template<typename A_, typename Value_>
struct ieml::Decode<char, ie::make_system::BasicAddSValueAction<A_, Value_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicAddSValueAction<A_, Value_> >;
};

namespace ie {
	template<typename A_, typename Value_, typename>
	class BasicAddSValueAction : public virtual IBasicActivityAction<A_> {
	public:
		using Make = make_system::BasicAddSValueAction<A_, Value_>;
		
		BasicAddSValueAction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto update(bool active) -> void override;
	
	protected:
		Value_& value;
		typename Value_::T constant;
	};
	
	template<typename A_>
	using AddSValueAction = BasicAddSValueAction<std::monostate, ISMutable<A_> >;
	
	using AddSBoolAction = AddSValueAction<bool>;
	using AddSFloatAction = AddSValueAction<float>;
	using AddSIntAction = AddSValueAction<int>;
	using AddSSizeAction = AddSValueAction<size_t>;
}

#include "BasicAddSValueAction.inl"
