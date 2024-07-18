#pragma once

#include "../IInteraction.hpp"

namespace ie {
	template<typename A_>
	class BasicEmptyInteraction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicEmptyInteraction : public virtual IBasicInteraction<A_> {
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicEmptyInteraction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicEmptyInteraction : public virtual IBasicInteraction<A_> {
	public:
		using Make = make_system::BasicEmptyInteraction<A_>;
		
		BasicEmptyInteraction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		BasicEmptyInteraction();
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
	};
	
	using EmptyInteraction = BasicEmptyInteraction<>;
}

template<typename A_>
struct ieml::Decode<char, ie::BasicEmptyInteraction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BasicEmptyInteraction<A_> >;
};

#include "BasicEmptyInteraction.inl"