#pragma once

#include "../IInteraction.hpp"
#include "IE/event/KeyHandler/KeyHandler.hpp"

namespace ie {
	template<typename T>
	class BasicKeysInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicKeysInteraction : public virtual IBasicInteraction<T> {
			BoxPtr<BasicKeyAction<T> > action;
			std::vector<Key> keys;
			std::vector<Key> black_list_keys = {};
			
			BasicKeysInteraction(BoxPtr<BasicKeyAction<T> >&& action, std::vector<Key> keys, std::vector<Key> black_list_keys = {});
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicKeysInteraction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicKeysInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicKeysInteraction<T>;
		
		BasicKeysInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		auto is_press() const -> bool;
		
		auto get_keys() -> std::vector<Key>;
		
		auto get_action() -> BasicKeyAction<T>*;
		
		auto set_action(BasicKeyAction<T>* action) -> void;
		
		auto start(sf::Vector2i mouse_position) -> void override;
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
		
	protected:
		KeyHandler* key_handler_;
		BoxPtr<BasicKeyAction<T> > action_;
		std::vector<Key> keys_;
		std::vector<Key> black_list_keys_;
		bool press_;
	};
	
	using KeysInteraction = BasicKeysInteraction<>;
}

template<typename T>
struct ieml::Decode<char, ie::make_system::BasicKeysInteraction<T> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicKeysInteraction<T> >;
};

#include "BasicKeysInteraction.inl"
