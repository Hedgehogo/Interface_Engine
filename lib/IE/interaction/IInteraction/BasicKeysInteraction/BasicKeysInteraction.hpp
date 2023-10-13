#pragma once

#include "../IInteraction.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include "IE/modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	template<typename T>
	class BasicKeysInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicKeysInteraction : public virtual IBasicInteraction<T> {
			BoxPtr<typename ie::BasicKeyAction<T>::Make > action;
			std::vector<Key> keys;
			std::vector<Key> blackListKeys = {};
			
			BasicKeysInteraction(BoxPtr<typename ie::BasicKeyAction<T>::Make >&& action, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
			
			ie::BasicKeysInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicKeysInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicKeysInteraction<T>;
		
		BasicKeysInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicKeysInteraction(BoxPtr<BasicKeyAction<T> >&& action, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
		
		void init(BasicActionInitInfo<T> initInfo) override;
		
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