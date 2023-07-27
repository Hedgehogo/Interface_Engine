#include "textEmptyInteraction.hpp"

namespace ui {
	TextEmptyInteraction* TextEmptyInteraction::copy() {
		auto textEmptyInteraction = new TextEmptyInteraction{};
		TextInteraction::copy(textEmptyInteraction);
		return textEmptyInteraction;
	}
	
	bool DecodePointer<TextEmptyInteraction>::decodePointer(const YAML::Node& node, TextEmptyInteraction*& textEmptyInteraction) {
		{
			textEmptyInteraction = new TextEmptyInteraction{};
			return true;
		}
	}
}