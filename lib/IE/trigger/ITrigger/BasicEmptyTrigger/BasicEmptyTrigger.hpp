#pragma once

#include "../ITrigger.hpp"

namespace ie {
	template<typename A_>
	class BasicEmptyTrigger;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicEmptyTrigger : public virtual IBasicTrigger<A_> {
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicEmptyTrigger<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicEmptyTrigger : public virtual IBasicTrigger<A_> {
	public:
		using Make = make_system::BasicEmptyTrigger<A_>;
		
		BasicEmptyTrigger(Make&& make, BasicActionInitInfo<A_> init_info);
		
		BasicEmptyTrigger();
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
	};
	
	using EmptyTrigger = BasicEmptyTrigger<>;
}

template<typename A_>
struct ieml::Decode<char, ie::BasicEmptyTrigger<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BasicEmptyTrigger<A_> >;
};

#include "BasicEmptyTrigger.inl"