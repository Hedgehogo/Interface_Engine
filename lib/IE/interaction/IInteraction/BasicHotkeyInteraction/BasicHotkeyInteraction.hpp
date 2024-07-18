#pragma once

#include "../IInteraction.hpp"
#include "../BasicKeysInteraction/BasicKeysInteraction.hpp"

namespace ie {
	namespace detail {
		template<typename A_>
		struct BasicHotkeyInteractionHotkey;
	
		namespace make_system {
			using namespace ie::make_system;
			
			template<typename A_ = std::monostate>
			struct BasicHotkeyInteractionHotkey {
				bp::BoxPtr<make_system::BasicKeysInteraction<A_> > interaction;
				size_t state{std::numeric_limits<size_t>::max()};
				
				BasicHotkeyInteractionHotkey(
					bp::BoxPtr<make_system::BasicKeysInteraction<A_> >&& interaction,
					size_t state = std::numeric_limits<size_t>::max()
				);
				
				auto make(BasicActionInitInfo<A_> init_info) -> detail::BasicHotkeyInteractionHotkey<A_>*;
			};
		}
	
		template<typename A_ = std::monostate>
		struct BasicHotkeyInteractionHotkey {
			using Make = make_system::BasicHotkeyInteractionHotkey<A_>;
			
			bp::BoxPtr<BasicKeysInteraction<A_> > interaction_;
			size_t state_{std::numeric_limits<size_t>::max()};
			
			BasicHotkeyInteractionHotkey(Make&& make, BasicActionInitInfo<A_> init_info);
			
			BasicHotkeyInteractionHotkey(bp::BoxPtr<BasicKeysInteraction<A_> >&& interaction, size_t state = std::numeric_limits<size_t>::max());
			
			BasicHotkeyInteractionHotkey(size_t state);
		};
	}
	
	template<typename A_>
	class BasicHotkeyInteraction;
	
	namespace make_system {
		template<typename A_ = std::monostate>
		struct BasicHotkeyInteraction : public virtual IBasicInteraction<A_> {
			using Hotkey = detail::make_system::BasicHotkeyInteractionHotkey<A_>;
			
			std::vector<std::vector<Hotkey > > hotkeys;
			size_t state = 0;
			
			explicit BasicHotkeyInteraction(std::vector<std::vector<Hotkey > > hotkeys, size_t state = 0);
			
			auto make(BasicActionInitInfo<A_> init_info) -> ie::BasicHotkeyInteraction<A_>* override;
		};
	}
	
	template<typename A_ = std::monostate>
	class BasicHotkeyInteraction : public virtual IBasicInteraction<A_> {
	public:
		using Hotkey = detail::BasicHotkeyInteractionHotkey<A_>;
		using Make = make_system::BasicHotkeyInteraction<A_>;
		
		BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<A_> init_info);
		
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
	
	using HotkeyInteraction = BasicHotkeyInteraction<>;
}

template<typename A_>
struct ieml::Decode<char, ie::detail::make_system::BasicHotkeyInteractionHotkey<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::detail::make_system::BasicHotkeyInteractionHotkey<A_> >;
};

template<typename A_>
struct ieml::Decode<char, ie::make_system::BasicHotkeyInteraction<A_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicHotkeyInteraction<A_> >;
};

#include "BasicHotkeyInteraction.inl"