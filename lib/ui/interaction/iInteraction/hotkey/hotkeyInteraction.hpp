#pragma once

#include "../iInteraction.hpp"
#include "../keys/keysInteraction.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
    class HotkeyInteraction : public virtual IInteraction{
    public:
        struct Hotkey {
            uint state{UINT32_MAX};
            KeysInteraction *interaction{nullptr};
			
            Hotkey(KeysInteraction *interaction, int state = UINT32_MAX);
			
            Hotkey(uint state);
			
            ~Hotkey();
        };
		
    protected:
        std::vector<std::vector<Hotkey*>> hotkeyStates;
        std::vector<Hotkey*> *nowHotkeys;
		
    public:
        HotkeyInteraction(std::vector<std::vector<Hotkey*>> hotkeys, uint state = 0);
		
        HotkeyInteraction(std::string str);

		void init(ui::InteractionManager &interactionManager) override;

        void setHotkeyEvent(uint state, Hotkey* hotkeyEvent);

        std::vector<Hotkey*> getHotkeys(int state);

        Hotkey* getHotkey(int state, int i);

        void start(sf::Vector2i mousePosition) override;

        void update(sf::Vector2i mousePosition) override;

        void finish(sf::Vector2i mousePosition) override;

        HotkeyInteraction* copy() override;

        ~HotkeyInteraction() override;
    };
	
	bool convertPointer(const YAML::Node &node, HotkeyInteraction *&hotkeyInteraction);
	
	template<>
	bool convert<HotkeyInteraction::Hotkey>(const YAML::Node& node, HotkeyInteraction::Hotkey *&hotkey);
}