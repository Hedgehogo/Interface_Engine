#pragma once

#include "../ITrigger.hpp"
#include "IE/event/EventHandler/EventHandler.hpp"

namespace ie {
	template<typename A_>
	class BasicAnyPressingTrigger;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicAnyPressingTrigger : public virtual IBasicTrigger<A_> {
			BoxPtr<IBasicActivityAction<A_> > action;
			Key key;
			
			BasicAnyPressingTrigger(BoxPtr<IBasicActivityAction<A_> >&& action, Key key);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicAnyPressingTrigger<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicAnyPressingTrigger : public virtual IBasicTrigger<A_> {
	public:
		using Make = make_system::BasicAnyPressingTrigger<A_>;
		
		BasicAnyPressingTrigger(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
	
	protected:
		EventHandler* event_handler_;
		BoxPtr<IBasicActivityAction<A_> > action_;
		Key key_;
	};
	
	using AnyPressingTrigger = BasicAnyPressingTrigger<>;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicAnyPressingTrigger<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicAnyPressingTrigger<A_> >;
};

#include "BasicAnyPressingTrigger.inl"
