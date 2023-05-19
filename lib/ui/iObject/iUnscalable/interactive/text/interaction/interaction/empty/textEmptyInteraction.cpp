#include "textEmptyInteraction.hpp"

namespace ui {
	TextEmptyInteraction* TextEmptyInteraction::copy() {
		return new TextEmptyInteraction{};
	}
	
	
	bool DecodePointer<TextEmptyInteraction>::decodePointer(const YAML::Node& node, TextEmptyInteraction*& textEmptyInteraction) {
		{
			textEmptyInteraction = new TextEmptyInteraction{};
			return true;
		}
	}
}