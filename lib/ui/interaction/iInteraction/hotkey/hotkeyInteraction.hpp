#pragma once

#include "../iInteraction.hpp"
#include "../keys/keysInteraction.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class HotkeyInteraction : public virtual IInteraction {
	public:
		struct Hotkey {
			uint state{std::numeric_limits<uint32_t>::max()};
			KeysInteraction* interaction{nullptr};
			
			Hotkey(KeysInteraction* interaction, uint state = std::numeric_limits<uint32_t>::max());
			
			Hotkey(uint state);
			
			~Hotkey();
		};
	
		HotkeyInteraction(std::vector<std::vector<Hotkey*>> hotkeys, uint state = 0);
		
		HotkeyInteraction(std::string str);
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		void setHotkeyEvent(uint state, Hotkey* hotkeyEvent);
		
		std::vector<Hotkey*> getHotkeys(int state);
		
		Hotkey* getHotkey(int state, int i);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		HotkeyInteraction* copy() override;
		
		~HotkeyInteraction() override;
	
	protected:
		std::vector<std::vector<Hotkey*>> hotkeyStates;
		std::vector<Hotkey*>* nowHotkeys;
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