#include "textButtonsInteraction.hpp"
#include "../../text.hpp"
namespace ui {
    TextButtonsInteraction::TextButtonsInteraction(ButtonEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys) : ButtonsInteraction(event, keys, blackListKeys) {}

    void TextButtonsInteraction::init(Text *text) {
        TextInteraction::init(text);
        dynamic_cast<TextEvent *>(event)->init(text);
    }

    TextButtonsInteraction *TextButtonsInteraction::copy() {
        return new TextButtonsInteraction{event, keys, blackListKeys};
    }

	bool convertPointer(const YAML::Node &node, TextButtonsInteraction *&textButtonsInteraction){
		ButtonEvent *event;
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

		{ textButtonsInteraction = new TextButtonsInteraction{event, keys, blackListKeys}; return true; }
	}
}