#include "textKeysInteraction.hpp"
#include "ui/iObject/iUnscalable/interactive/text/text.hpp"
#include "ui/interaction/event/key/openUrl/openUrlEvent.hpp"

namespace ui {
	TextKeysInteraction::TextKeysInteraction(KeyEvent* event, std::vector<Key> keys, std::vector<Key> blackListKeys) :
		KeysInteraction(event, keys, blackListKeys) {
	}
	
	void TextKeysInteraction::init(TextInteractionInitInfo textInteractionInitInfo) {
		TextInteraction::init(textInteractionInitInfo);
		dynamic_cast<TextEvent*>(event)->init(textInteractionInitInfo);
	}
	
	TextKeysInteraction* TextKeysInteraction::copy() {
		return new TextKeysInteraction{event, keys, blackListKeys};
	}
	
	
	bool DecodePointer<TextKeysInteraction>::decodePointer(const YAML::Node& node, TextKeysInteraction*& textKeysInteraction) {
		if(node.IsScalar()) {
			textKeysInteraction = new TextKeysInteraction{new OpenUrlEvent{node.as<std::string>()}, {Key::mouseLeft}};
			return true;
		}
		
		KeyEvent* event;
		std::vector<Key> keys;
		std::vector<Key> blackListKeys{};
		
		node["event"] >> event;
		
		keys.resize(node["keys"].size());
		uint i{0};
		for(auto& key: node["keys"]) {
			key >> keys[i];
			++i;
		}
		
		if(node["black-listKeys"]) {
			i = 0;
			for(auto& key: node["black-listKeys"]) {
				key >> blackListKeys[i];
				++i;
			}
		}
		
		{
			textKeysInteraction = new TextKeysInteraction{event, keys, blackListKeys};
			return true;
		}
	}
}