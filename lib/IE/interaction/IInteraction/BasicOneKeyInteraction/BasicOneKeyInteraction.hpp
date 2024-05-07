#pragma once

#include "../IInteraction.hpp"
#include "IE/event/EventHandler/EventHandler.hpp"

namespace ie {
	template<typename T>
	class BasicOneKeyInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicOneKeyInteraction : public virtual IBasicInteraction<T> {
			BoxPtr<BasicTouchAction<T> > action;
			Key key;
			
			BasicOneKeyInteraction(BoxPtr<BasicTouchAction<T> >&& action, Key key);
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicOneKeyInteraction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicOneKeyInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicOneKeyInteraction<T>;
		
		BasicOneKeyInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		auto get_key() -> Key;
		
		auto get_action() -> BasicTouchAction<T>&;
		
		auto get_action() const -> BasicTouchAction<T> const&;
		
		auto set_action(BoxPtr<BasicTouchAction<T> >&& action) -> void;
		
		auto start(sf::Vector2i mouse_position) -> void override;
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
		
	protected:
		EventHandler* event_handler_;
		BoxPtr<BasicTouchAction<T> > action_;
		Key key_;
	};
	
	using OneKeyInteraction = BasicOneKeyInteraction<>;
}

template<typename T>
struct ieml::Decode<char, ie::make_system::BasicOneKeyInteraction<T> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicOneKeyInteraction<T>>;
};

#include "BasicOneKeyInteraction.inl"