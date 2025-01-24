#pragma once

#include "../ITrigger.hpp"
#include "IE/event/EventHandler/EventHandler.hpp"
#include "IE/event/PointerTracker/PointerTracker.hpp"

namespace ie {
	template<typename A_>
	class BasicTouchTrigger;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicTouchTrigger : public virtual IBasicTrigger<A_> {
			BoxPtr<IBasicTouchAction<A_> > action;
			Key key;
			
			BasicTouchTrigger(BoxPtr<IBasicTouchAction<A_> >&& action, Key key);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicTouchTrigger<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicTouchTrigger : public virtual IBasicTrigger<A_> {
	public:
		using Make = make_system::BasicTouchTrigger<A_>;
		
		BasicTouchTrigger(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto get_key() -> Key;
		
		auto get_action() -> IBasicTouchAction<A_>&;
		
		auto get_action() const -> IBasicTouchAction<A_> const&;
		
		auto set_action(BoxPtr<IBasicTouchAction<A_> >&& action) -> void;
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
		
	protected:
		PointerTracker tracker_;
		EventHandler* event_handler_;
		BoxPtr<IBasicTouchAction<A_> > action_;
		Key key_;
	};
	
	using TouchTrigger = BasicTouchTrigger<>;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicTouchTrigger<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicTouchTrigger<A_> >;
};

#include "BasicTouchTrigger.inl"