#include "TextHotkeyInteraction.hpp"

namespace ui {
	bool DecodePointer<TextHotkeyInteraction>::decodePointer(const YAML::Node& node, TextHotkeyInteraction*& textHotkeyInteraction) {
		textHotkeyInteraction = new TextHotkeyInteraction{
			convDef<std::vector<std::vector<BoxPtr<TextHotkeyInteraction::Hotkey> > > >(node["hotkeys"], {}),
			convDef(node["start-state"], 0u)
		};
		return true;
	}
}