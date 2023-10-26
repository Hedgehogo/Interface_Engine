#pragma once

#include "../IInteraction.hpp"
#include "../BasicKeysInteraction/BasicKeysInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	namespace detail {
		template<typename T>
		struct BasicHotkeyInteractionHotkey;
	
		namespace make_system {
			using namespace ie::make_system;
			
			template<typename T = std::monostate>
			struct BasicHotkeyInteractionHotkey {
				BoxPtr<make_system::BasicKeysInteraction<T> > interaction;
				size_t state{std::numeric_limits<size_t>::max()};
				
				BasicHotkeyInteractionHotkey(
					BoxPtr<make_system::BasicKeysInteraction<T> >&& interaction,
					size_t state = std::numeric_limits<size_t>::max()
				);
				
				detail::BasicHotkeyInteractionHotkey<T>* make(BasicActionInitInfo<T> init_info);
			};
		}
	
		template<typename T = std::monostate>
		struct BasicHotkeyInteractionHotkey {
			using Make = make_system::BasicHotkeyInteractionHotkey<T>;
			
			BoxPtr<BasicKeysInteraction<T> > interaction_;
			size_t state_{std::numeric_limits<size_t>::max()};
			
			BasicHotkeyInteractionHotkey(Make&& make, BasicActionInitInfo<T> init_info);
			
			BasicHotkeyInteractionHotkey(BoxPtr<BasicKeysInteraction<T> >&& interaction, size_t state = std::numeric_limits<size_t>::max());
			
			BasicHotkeyInteractionHotkey(size_t state);
		};
	}
	
	template<typename T>
	class BasicHotkeyInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicHotkeyInteraction : public virtual IBasicInteraction<T> {
			using Hotkey = detail::make_system::BasicHotkeyInteractionHotkey<T>;
			
			std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys;
			size_t state = 0;
			
			BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, size_t state = 0);
			
			ie::BasicHotkeyInteraction<T>* make(BasicActionInitInfo<T> init_info) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicHotkeyInteraction : public virtual IBasicInteraction<T> {
	public:
		using Hotkey = detail::BasicHotkeyInteractionHotkey<T>;
		using Make = make_system::BasicHotkeyInteraction<T>;
		
		BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<T> init_info);
		
		BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, size_t state = 0);
		
		BasicHotkeyInteraction(std::string);
		
		void init(BasicActionInitInfo<T> init_info) override;
		
		void set_hotkey_action(size_t state, Hotkey* hotkey_action);
		
		std::vector<BoxPtr<Hotkey> > get_hotkeys(int state);
		
		BoxPtr<Hotkey> get_hotkey(int state, int i);
		
		void start(sf::Vector2i mouse_position) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i mouse_position) override;
		
		BasicHotkeyInteraction<T>* copy() override;
	
	protected:
		std::vector<std::vector<BoxPtr<Hotkey> > > hotkey_states_;
		std::vector<BoxPtr<Hotkey> >* now_hotkeys_;
	};
	
	using HotkeyInteraction = BasicHotkeyInteraction<>;
	
	template<typename T>
	struct Decode<detail::BasicHotkeyInteractionHotkey<T>*> {
		static bool decode(const YAML::Node& node, detail::BasicHotkeyInteractionHotkey<T>*& hotkey);
	};
}

#include "BasicHotkeyInteraction.inl"