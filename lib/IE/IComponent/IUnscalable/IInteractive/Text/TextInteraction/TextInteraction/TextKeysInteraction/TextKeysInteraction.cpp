#include "TextKeysInteraction.hpp"

#include <utility>
#include "IE/IComponent/IUnscalable/IInteractive/Text/Text.hpp"
#include "IE/Interaction/IEvent/BasicKeyEvent/BasicOpenUrlEvent/BasicOpenUrlEvent.hpp"

namespace ui {
	TextKeysInteraction::TextKeysInteraction(BoxPtr<KeyEvent> event, std::vector<Key> keys, std::vector<Key> blackListKeys) :
		KeysInteraction(std::move(event), std::move(keys), std::move(blackListKeys)) {
	}
	
	void TextKeysInteraction::init(TextInteractionInitInfo textInteractionInitInfo) {
		TextInteraction::init(textInteractionInitInfo);
		dynamic_cast<TextEvent*>(event.get())->init(textInteractionInitInfo);
	}
	
	TextKeysInteraction* TextKeysInteraction::copy() {
		return new TextKeysInteraction{event, keys, blackListKeys};
	}
	
	bool DecodePointer<TextKeysInteraction>::decodePointer(const YAML::Node& node, TextKeysInteraction*& textKeysInteraction) {
		if(node.IsScalar()) {
			textKeysInteraction = new TextKeysInteraction{makeBoxPtr<KeyEvent, OpenUrlEvent>(node.as<std::string>()), {Key::mouseLeft}};
			return true;
		}
		textKeysInteraction = new TextKeysInteraction{
			node["event"].as<BoxPtr<KeyEvent>>(),
			node["keys"].as<std::vector<Key>>(),
			convDef<std::vector<Key>>(node["black-listKeys"], {})
		};
		return true;
	}
}