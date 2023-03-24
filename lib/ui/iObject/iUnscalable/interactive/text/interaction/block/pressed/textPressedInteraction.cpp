#include "textPressedInteraction.hpp"
#include "../../../../../../../interaction/interactionManager/interactionManager.hpp"
#include "../../../event/textEvent.hpp"
namespace ui {
	TextPressedInteraction::TextPressedInteraction(KeyEvent *event, const std::vector<Key> keys, const std::vector<Key> blackListKeys) : TextKeysInteraction(event, keys, blackListKeys) {}

	void TextPressedInteraction::init(Text* text, InteractionManager &interactionManager) {
		this->interactionManager = &interactionManager;
		this->text = text;
		dynamic_cast<TextEvent*>(event)->init(text);
	}

	bool TextPressedInteraction::isBlocked() const {
		return true;
	}

	void TextPressedInteraction::update(sf::Vector2i mousePosition) {
		KeysInteraction::update(mousePosition);
		if (!isPress()){
			interactionManager->deleteInteraction(*this);
		}
	}

	TextPressedInteraction *TextPressedInteraction::copy() {
		return new TextPressedInteraction{event->copy(), keys, blackListKeys};
	}

	bool convertPointer(const YAML::Node &node, TextPressedInteraction *&textPressedInteraction) {
		std::vector<Key> keys;
		std::vector<Key> blackListKeys{};

		keys.resize(node["keys"].size());
		uint i{0};
		for (auto &key: node["keys"]) {
			key >> keys[i];
			++i;
		}

		if (node["black-listKeys"]){
			i = 0;
			for (auto& key : node["black-listKeys"]) {
				key >> blackListKeys[i];
				++i;
			}
		}

		{ textPressedInteraction = new TextPressedInteraction{node["event"].as<KeyEvent*>(), keys, blackListKeys}; return true; }
	}
}