#pragma once

#include "../IInteraction.hpp"
#include "../BasicKeysInteraction/BasicKeysInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	namespace detail {
		template<typename T>
		struct BasicHotkeyInteractionHotkey;
	
		namespace make_system {
			using namespace ie::make_system;
			
			template<typename T = std::monostate>
			struct BasicHotkeyInteractionHotkey {
				bp::BoxPtr<make_system::BasicKeysInteraction<T> > interaction;
				size_t state{std::numeric_limits<size_t>::max()};
				
				BasicHotkeyInteractionHotkey(
					bp::BoxPtr<make_system::BasicKeysInteraction<T> >&& interaction,
					size_t state = std::numeric_limits<size_t>::max()
				);
				
				auto make(BasicActionInitInfo<T> init_info) -> detail::BasicHotkeyInteractionHotkey<T>*;
			};
		}
	
		template<typename T = std::monostate>
		struct BasicHotkeyInteractionHotkey {
			using Make = make_system::BasicHotkeyInteractionHotkey<T>;
			
			bp::BoxPtr<BasicKeysInteraction<T> > interaction_;
			size_t state_{std::numeric_limits<size_t>::max()};
			
			BasicHotkeyInteractionHotkey(Make&& make, BasicActionInitInfo<T> init_info);
			
			BasicHotkeyInteractionHotkey(bp::BoxPtr<BasicKeysInteraction<T> >&& interaction, size_t state = std::numeric_limits<size_t>::max());
			
			BasicHotkeyInteractionHotkey(size_t state);
		};
	}
	
	template<typename T>
	class BasicHotkeyInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicHotkeyInteraction : public virtual IBasicInteraction<T> {
			using Hotkey = detail::make_system::BasicHotkeyInteractionHotkey<T>;
			
			std::vector<std::vector<Hotkey > > hotkeys;
			size_t state = 0;
			
			explicit BasicHotkeyInteraction(std::vector<std::vector<Hotkey > > hotkeys, size_t state = 0);
			
			auto make(BasicActionInitInfo<T> init_info) -> ie::BasicHotkeyInteraction<T>* override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicHotkeyInteraction : public virtual IBasicInteraction<T> {
	public:
		using Hotkey = detail::BasicHotkeyInteractionHotkey<T>;
		using Make = make_system::BasicHotkeyInteraction<T>;
		
		BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		auto set_hotkey_action(size_t state, Hotkey* hotkey_action) -> void;
		
		auto get_hotkeys(int state) -> std::vector<Hotkey>;
		
		auto get_hotkey(int state, int i) -> Hotkey;
		
		auto start(sf::Vector2i mouse_position) -> void override;
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
		auto finish(sf::Vector2i mouse_position) -> void override;
		
	protected:
		std::vector<std::vector<Hotkey > > hotkey_states_;
		std::vector<Hotkey >* now_hotkeys_;
	};
	
	using HotkeyInteraction = BasicHotkeyInteraction<>;
}

template<typename T>
struct ieml::Decode<char, ie::detail::make_system::BasicHotkeyInteractionHotkey<T> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::detail::make_system::BasicHotkeyInteractionHotkey<T> >;
};

template<typename T>
struct ieml::Decode<char, ie::make_system::BasicHotkeyInteraction<T> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicHotkeyInteraction<T> >;
};

#include "BasicHotkeyInteraction.inl"