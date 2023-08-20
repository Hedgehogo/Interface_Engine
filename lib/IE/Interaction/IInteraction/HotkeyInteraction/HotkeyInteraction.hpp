#pragma once

#include "../IInteraction.hpp"
#include "../KeysInteraction/KeysInteraction.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class HotkeyInteraction : public virtual IInteraction {
	public:
		struct Hotkey {
			BoxPtr<KeysInteraction> interaction{nullptr};
			uint state{std::numeric_limits<uint32_t>::max()};
			
			Hotkey(BoxPtr<KeysInteraction> && interaction, uint state = std::numeric_limits<uint32_t>::max());
			
			Hotkey(uint state);
		};
	
		HotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey>>> && hotkeys, uint state = 0);
		
		HotkeyInteraction(std::string);
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		void setHotkeyEvent(uint state, Hotkey* hotkeyEvent);
		
		std::vector<BoxPtr<HotkeyInteraction::Hotkey>> getHotkeys(int state);
		
		BoxPtr<HotkeyInteraction::Hotkey> getHotkey(int state, int i);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		HotkeyInteraction* copy() override;
	
	protected:
		std::vector<std::vector<BoxPtr<Hotkey>>> hotkeyStates;
		std::vector<BoxPtr<Hotkey>>* nowHotkeys;
	};
	
	template<>
	struct DecodePointer<HotkeyInteraction> {
		static bool decodePointer(const YAML::Node& node, HotkeyInteraction*& hotkeyInteraction);
	};
	
	template<>
	struct Decode<HotkeyInteraction::Hotkey*> {
		static bool decode(const YAML::Node& node, HotkeyInteraction::Hotkey*& hotkey);
	};
}