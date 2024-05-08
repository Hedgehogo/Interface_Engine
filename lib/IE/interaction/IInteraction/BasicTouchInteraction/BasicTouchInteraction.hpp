#pragma once

#include "../IInteraction.hpp"
#include "IE/event/EventHandler/EventHandler.hpp"

namespace ie {
	template<typename A_>
	class BasicTouchInteraction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicTouchInteraction : public virtual IBasicInteraction<A_> {
			BoxPtr<BasicTouchAction<A_> > action;
			Key key;
			
			BasicTouchInteraction(BoxPtr<BasicTouchAction<A_> >&& action, Key key);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicTouchInteraction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicTouchInteraction : public virtual IBasicInteraction<A_> {
	public:
		using Make = make_system::BasicTouchInteraction<A_>;
		
		BasicTouchInteraction(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto get_key() -> Key;
		
		auto get_action() -> BasicTouchAction<A_>&;
		
		auto get_action() const -> BasicTouchAction<A_> const&;
		
		auto set_action(BoxPtr<BasicTouchAction<A_> >&& action) -> void;
		
		auto start(sf::Vector2i mouse_position) -> void override;
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
		
	protected:
		EventHandler* event_handler_;
		BoxPtr<BasicTouchAction<A_> > action_;
		Key key_;
	};
	
	using TouchInteraction = BasicTouchInteraction<>;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicTouchInteraction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicTouchInteraction<A_> >;
};

#include "BasicTouchInteraction.inl"