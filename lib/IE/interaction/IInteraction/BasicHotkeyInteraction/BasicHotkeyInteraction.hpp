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
				uint state{std::numeric_limits<uint>::max()};
				
				BasicHotkeyInteractionHotkey(
					BoxPtr<make_system::BasicKeysInteraction<T> >&& interaction,
					uint state = std::numeric_limits<uint>::max()
				);
				
				detail::BasicHotkeyInteractionHotkey<T>* make(BasicActionInitInfo<T> initInfo);
			};
		}
	
		template<typename T = std::monostate>
		struct BasicHotkeyInteractionHotkey {
			using Make = make_system::BasicHotkeyInteractionHotkey<T>;
			
			BoxPtr<BasicKeysInteraction<T> > interaction;
			uint state{std::numeric_limits<uint>::max()};
			
			BasicHotkeyInteractionHotkey(Make&& make, BasicActionInitInfo<T> initInfo);
			
			BasicHotkeyInteractionHotkey(BoxPtr<BasicKeysInteraction<T> >&& interaction, uint state = std::numeric_limits<uint>::max());
			
			BasicHotkeyInteractionHotkey(uint state);
		};
	}
	
	template<typename T>
	class BasicHotkeyInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicHotkeyInteraction : public virtual IBasicInteraction<T> {
			using Hotkey = detail::make_system::BasicHotkeyInteractionHotkey<T>;
			
			std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys;
			uint state = 0;
			
			BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, uint state = 0);
			
			ie::BasicHotkeyInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicHotkeyInteraction : public virtual IBasicInteraction<T> {
	public:
		using Hotkey = detail::BasicHotkeyInteractionHotkey<T>;
		using Make = make_system::BasicHotkeyInteraction<T>;
		
		BasicHotkeyInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >&& hotkeys, uint state = 0);
		
		BasicHotkeyInteraction(std::string);
		
		void init(BasicActionInitInfo<T> initInfo) override;
		
		void setHotkeyAction(uint state, Hotkey* hotkeyAction);
		
		std::vector<BoxPtr<Hotkey> > getHotkeys(int state);
		
		BoxPtr<Hotkey> getHotkey(int state, int i);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		BasicHotkeyInteraction<T>* copy() override;
	
	protected:
		bool a{false};
		std::vector<std::vector<BoxPtr<Hotkey> > > hotkeyStates;
		std::vector<BoxPtr<Hotkey> >* nowHotkeys;
	};
	
	using HotkeyInteraction = BasicHotkeyInteraction<>;
	
	template<typename T>
	struct Decode<detail::BasicHotkeyInteractionHotkey<T>*> {
		static bool decode(const YAML::Node& node, detail::BasicHotkeyInteractionHotkey<T>*& hotkey);
	};
}

#include "BasicHotkeyInteraction.inl"