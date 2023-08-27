#pragma once

#include "../IInteraction.hpp"
#include "../../../Enums/KeyHandler/KeyHandler.hpp"
#include "../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicKeysInteraction : public virtual IBasicInteraction<T> {
	public:
		BasicKeysInteraction(BoxPtr<BasicKeyAction<T> >&& action, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
		
		bool isPress() const;
		
		std::vector<Key> getKeys();
		
		BasicKeyAction<T>* getAction();
		
		void setAction(BasicKeyAction<T>* action);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i) override;
		
		BasicKeysInteraction<T>* copy() override;
		
	protected:
		BoxPtr<BasicKeyAction<T> > action;
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
