#include "textKeysInteraction.hpp"
#include "../../text.hpp"
namespace ui {
    TextKeysInteraction::TextKeysInteraction(KeyEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys) : KeysInteraction(event, keys, blackListKeys) {}

    void TextKeysInteraction::init(Text *text, InteractionManager &interactionManager) {
	    TextInteraction::init(text, interactionManager);
        dynamic_cast<TextEvent *>(event)->init(text);
    }

    TextKeysInteraction *TextKeysInteraction::copy() {
        return new TextKeysInteraction{event, keys, blackListKeys};
    }

	bool convertPointer(const YAML::Node &node, TextKeysInteraction *&textKeysInteraction){
		KeyEvent *event;
		std::vector<Key> keys;
		std::vector<Key> blackListKeys{};

		node["event"] >> event;

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

		{ textKeysInteraction = new TextKeysInteraction{event, keys, blackListKeys}; return true; }
	}
}