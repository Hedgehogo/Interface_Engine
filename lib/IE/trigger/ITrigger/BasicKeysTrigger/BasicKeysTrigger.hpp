#pragma once

#include "../ITrigger.hpp"
#include "IE/event/EventHandler/KeyHandler/KeyHandler.hpp"

namespace ie {
	template<typename A_>
	class BasicKeysTrigger;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicKeysTrigger : public virtual IBasicTrigger<A_> {
			BoxPtr<IBasicActivityAction<A_> > action;
			std::vector<Key> keys;
			std::vector<Key> black_list_keys = {};
			
			BasicKeysTrigger(BoxPtr<IBasicActivityAction<A_> >&& action, std::vector<Key> keys, std::vector<Key> black_list_keys = {});
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicKeysTrigger<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicKeysTrigger : public virtual IBasicTrigger<A_> {
	public:
		using Make = make_system::BasicKeysTrigger<A_>;
		
		BasicKeysTrigger(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto is_press() const -> bool;
		
		auto get_keys() -> std::vector<Key>;
		
		auto get_action() -> IBasicActivityAction<A_>*;
		
		auto set_action(IBasicActivityAction<A_>* action) -> void;
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
		
	protected:
		EventHandler* event_handler_;
		BoxPtr<IBasicActivityAction<A_> > action_;
		std::vector<Key> keys_;
		std::vector<Key> black_list_keys_;
		bool press_;
	};
	
	using KeysTrigger = BasicKeysTrigger<>;
}

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicKeysTrigger<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicKeysTrigger<A_> >;
};

#include "BasicKeysTrigger.inl"
