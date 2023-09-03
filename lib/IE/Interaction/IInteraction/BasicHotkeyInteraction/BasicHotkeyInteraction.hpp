#pragma once

#include "../IInteraction.hpp"
#include "../BasicKeysInteraction/BasicKeysInteraction.hpp"
#include "../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	namespace detail {
		template<typename T = std::monostate>
		struct BasicHotkeyInteractionHotkey {
			BoxPtr<BasicKeysInteraction<T> > interaction;
			uint state{std::numeric_limits<uint>::max()};
			
			struct Make {
				BoxPtr<typename BasicKeysInteraction<T>::Make> interaction;
				uint state{std::numeric_limits<uint>::max()};
				
				Make(
					BoxPtr<typename BasicKeysInteraction<T>::Make>&& interaction,
					uint state = std::numeric_limits<uint>::max()
				);
				
				BasicHotkeyInteractionHotkey<T>* make(BasicActionInitInfo<T> initInfo);
			};
			
			BasicHotkeyInteractionHotkey(Make&& make, BasicActionInitInfo<T> initInfo);
			
			BasicHotkeyInteractionHotkey(BoxPtr<BasicKeysInteraction<T> >&& interaction, uint state = std::numeric_limits<uint>::max());
			
			BasicHotkeyInteractionHotkey(uint state);
		};
	}
	
	template<typename T = std::monostate>
	class BasicHotkeyInteraction : public virtual IBasicInteraction<T> {
	public:
		using Hotkey = detail::BasicHotkeyInteractionHotkey<T>;
		
		struct Make : public virtual IBasicInteraction<T>::Make {
			std::vector<std::vector<BoxPtr<typename Hotkey::Make> > >&& hotkeys;
			uint state = 0;
			
			Make(std::vector<std::vector<BoxPtr<typename Hotkey::Make> > >&& hotkeys, uint state = 0);
			
			BasicHotkeyInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
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
