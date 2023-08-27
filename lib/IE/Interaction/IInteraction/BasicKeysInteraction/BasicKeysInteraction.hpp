#pragma once

#include "../IInteraction.hpp"
#include "../../../Enums/KeyHandler/KeyHandler.hpp"
#include "../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../../IEvent/BasicKeyEvent/BasicOpenUrlEvent/BasicOpenUrlEvent.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicKeysInteraction : public virtual IBasicInteraction<T> {
	public:
		BasicKeysInteraction(BoxPtr<BasicKeyEvent<T> >&& event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
		
		bool isPress() const;
		
		std::vector<Key> getKeys();
		
		BasicKeyEvent<T>* getEvent();
		
		void setEvent(BasicKeyEvent<T>* event);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i) override;
		
		BasicKeysInteraction<T>* copy() override;
		
	protected:
		BoxPtr<BasicKeyEvent<T> > event;
		std::vector<Key> keys;
		std::vector<Key> blackListKeys;
		bool press;
	};
	
	using KeysInteraction = BasicKeysInteraction<>;
	
	template<typename T>
	struct DecodePointer<BasicKeysInteraction<T> > {
		static bool decodePointer(const YAML::Node& node, BasicKeysInteraction<T>*& keysInteraction);
	};
}

#include "BasicKeysInteraction.inl"
