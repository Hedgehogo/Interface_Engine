#pragma once

#include "../ITrigger.hpp"
#include "../BasicKeysTrigger/BasicKeysTrigger.hpp"

namespace ie {
	namespace detail {
		template<typename A_>
		struct BasicHotkeyTriggerHotkey;
	
		namespace make_system {
			using namespace ie::make_system;
			
			template<typename A_ = std::monostate>
			struct BasicHotkeyTriggerHotkey {
				bp::BoxPtr<make_system::BasicKeysTrigger<A_> > trigger;
				size_t state{std::numeric_limits<size_t>::max()};
				
				BasicHotkeyTriggerHotkey(
					bp::BoxPtr<make_system::BasicKeysTrigger<A_> >&& trigger,
					size_t state = std::numeric_limits<size_t>::max()
				);
				
				auto make(BasicActionInitInfo<A_> init_info) -> detail::BasicHotkeyTriggerHotkey<A_>*;
			};
		}
	
		template<typename A_ = std::monostate>
		struct BasicHotkeyTriggerHotkey {
			using Make = make_system::BasicHotkeyTriggerHotkey<A_>;
			
			bp::BoxPtr<BasicKeysTrigger<A_> > trigger_;
			size_t state_{std::numeric_limits<size_t>::max()};
			
			BasicHotkeyTriggerHotkey(Make&& make, BasicActionInitInfo<A_> init_info);
			
			BasicHotkeyTriggerHotkey(bp::BoxPtr<BasicKeysTrigger<A_> >&& trigger, size_t state = std::numeric_limits<size_t>::max());
			
			BasicHotkeyTriggerHotkey(size_t state);
		};
	}
	
	template<typename A_>
	class BasicHotkeyTrigger;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicHotkeyTrigger : public virtual IBasicTrigger<A_> {
			using Hotkey = detail::make_system::BasicHotkeyTriggerHotkey<A_>;
			
			std::vector<std::vector<Hotkey > > hotkeys;
			size_t state = 0;
			
			explicit BasicHotkeyTrigger(std::vector<std::vector<Hotkey > > hotkeys, size_t state = 0);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicHotkeyTrigger<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicHotkeyTrigger : public virtual IBasicTrigger<A_> {
	public:
		using Hotkey = detail::BasicHotkeyTriggerHotkey<A_>;
		using Make = make_system::BasicHotkeyTrigger<A_>;
		
		BasicHotkeyTrigger(Make&& make, BasicActionInitInfo<A_> init_info);
		
		auto set_hotkey_action(size_t state, Hotkey* hotkey_action) -> void;
		
		auto get_hotkeys(int state) -> std::vector<Hotkey>;
		
		auto get_hotkey(int state, int i) -> Hotkey;
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
		
	protected:
		std::vector<std::vector<Hotkey> > hotkey_states_;
		std::vector<Hotkey>* now_hotkeys_;
	};
	
	using HotkeyTrigger = BasicHotkeyTrigger<>;
}

template<typename A_>
struct ieml::Decode<char, ie::detail::make_system::BasicHotkeyTriggerHotkey<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::detail::make_system::BasicHotkeyTriggerHotkey<A_> >;
};

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicHotkeyTrigger<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicHotkeyTrigger<A_> >;
};

#include "BasicHotkeyTrigger.inl"