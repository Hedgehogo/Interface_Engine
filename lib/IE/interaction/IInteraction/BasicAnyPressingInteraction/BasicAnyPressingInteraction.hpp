#pragma once

#include "../IInteraction.hpp"
#include "IE/event/EventHandler/EventHandler.hpp"

namespace ie {
	template<typename A_>
	class BasicAnyPressingInteraction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicAnyPressingInteraction : public virtual IBasicInteraction<A_> {
			BoxPtr<IBasicActivityAction<A_> > action;
			Key key;
			
			BasicAnyPressingInteraction(BoxPtr<IBasicActivityAction<A_> >&& action, Key key);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicAnyPressingInteraction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicAnyPressingInteraction : public virtual IBasicInteraction<A_> {
	public:
		using Make = make_system::BasicAnyPressingInteraction<A_>;
		
		BasicAnyPressingInteraction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
	
	protected:
		EventHandler* event_handler_;
		BoxPtr<IBasicActivityAction<A_> > action_;
		Key key_;
	};
	
	using AnyPressingInteraction = BasicAnyPressingInteraction<>;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicAnyPressingInteraction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicAnyPressingInteraction<A_> >;
};

#include "BasicAnyPressingInteraction.inl"
