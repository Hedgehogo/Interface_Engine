#include "HotkeyInteraction.hpp"

namespace ui {
	HotkeyInteraction::Hotkey::Hotkey(BoxPtr<KeysInteraction> && interaction, uint state) : interaction(std::move(interaction)), state(state) {
	}
	
	HotkeyInteraction::Hotkey::Hotkey(uint state) : interaction(nullptr), state(state) {
	}
	
	HotkeyInteraction::HotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey>>> && hotkeys, uint state) : hotkeyStates(std::move(hotkeys)), nowHotkeys(nullptr) {
		if(this->hotkeyStates.size() <= state) {
			this->hotkeyStates.resize(state, {});
		}
		nowHotkeys = &this->hotkeyStates[state];
	}
	
	void HotkeyInteraction::init(InteractionInitInfo interactionInitInfo) {
		for(const auto& hotkeyState: hotkeyStates) {
			for(auto& hotkey: hotkeyState) {
				hotkey->interaction->init(interactionInitInfo);
			}
		}
	}
	
	HotkeyInteraction::HotkeyInteraction(std::string) {
	}
	
	void HotkeyInteraction::setHotkeyEvent(uint state, HotkeyInteraction::Hotkey* hotkeyEvent) {
		if(hotkeyStates.size() <= state) {
			hotkeyStates.resize(state, {});
		}
		hotkeyStates[state].emplace_back(hotkeyEvent);
	}
	
	std::vector<BoxPtr<HotkeyInteraction::Hotkey>> HotkeyInteraction::getHotkeys(int state) {
		return hotkeyStates[state];
	}
	
	BoxPtr<HotkeyInteraction::Hotkey> HotkeyInteraction::getHotkey(int state, int i) {
		return hotkeyStates[state][i];
	}
	
	void HotkeyInteraction::start(sf::Vector2i mousePosition) {
		for(auto& hotkey: *nowHotkeys) {
			hotkey->interaction->start(mousePosition);
		}
	}
	
	void HotkeyInteraction::update(sf::Vector2i mousePosition) {
		for(auto& hotkey: *nowHotkeys) {
			hotkey->interaction->update(mousePosition);
			if(hotkey->interaction->isPress() && hotkey->state != UINT32_MAX) {
				finish(mousePosition);
				nowHotkeys = &hotkeyStates[hotkey->state];
				start(mousePosition);
			}
		}
	}
	
	void HotkeyInteraction::finish(sf::Vector2i mousePosition) {
		for(auto& hotkey: *nowHotkeys) {
			hotkey->interaction->finish(mousePosition);
		}
	}
	
	HotkeyInteraction* HotkeyInteraction::copy() {
		return new HotkeyInteraction{*this};
	}
	
	bool DecodePointer<HotkeyInteraction>::decodePointer(const YAML::Node& node, HotkeyInteraction*& hotkeyInteraction) {
		hotkeyInteraction = new HotkeyInteraction{
			convDef<std::vector<std::vector<BoxPtr<HotkeyInteraction::Hotkey>>>>(node["hotkeys"], {}),
			convDef(node["start-state"], 0u)
		};
		return true;
	}
	
	bool Decode<HotkeyInteraction::Hotkey*>::decode(const YAML::Node& node, HotkeyInteraction::Hotkey*& hotkey) {
		hotkey = new HotkeyInteraction::Hotkey{
			convDef(node["interaction"], BoxPtr<KeysInteraction>{}),
			convDef(node["state"], std::numeric_limits<uint32_t>::max())
		};
		return true;
	}
}