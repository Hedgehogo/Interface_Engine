#pragma once

#include "../iInteraction.hpp"
#include "../../../enums/keyHandler/keyHandler.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class KeysInteraction : public virtual IInteraction {
	public:
		KeysInteraction(BoxPtr<KeyEvent>&& event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
		
		bool isPress() const;
		
		std::vector<Key> getKeys();
		
		KeyEvent* getEvent();
		
		void setEvent(KeyEvent* event);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i) override;
		
		KeysInteraction* copy() override;
		
	protected:
		BoxPtr<KeyEvent> event;
		std::vector<Key> keys;
		std::vector<Key> blackListKeys;
		bool press;
	};
	
	template<>
	struct DecodePointer<KeysInteraction> {
		static bool decodePointer(const YAML::Node& node, KeysInteraction*& keysInteraction);
	};
	
}