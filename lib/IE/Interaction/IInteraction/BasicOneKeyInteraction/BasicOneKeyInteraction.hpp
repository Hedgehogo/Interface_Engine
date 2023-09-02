#pragma once

#include "../IInteraction.hpp"
#include "../../../Enums/KeyHandler/KeyHandler.hpp"
#include "../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicOneKeyInteraction : public virtual IBasicInteraction<T> {
	public:
		struct Make : public IBasicInteraction<T>::Make {
			BoxPtr<typename BasicKeyAction<T>::Make> action;
			Key key;
			
			Make(BoxPtr<typename BasicKeyAction<T>::Make>&& action, Key key);
			
			BasicOneKeyInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
		BasicOneKeyInteraction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		BasicOneKeyInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key);
		
		void init(BasicActionInitInfo<T> initInfo) override;
		
		Key getKey();
		
		BasicKeyAction<T>& getAction();
		
		const BasicKeyAction<T>& getAction() const;
		
		void setAction(BoxPtr<BasicKeyAction<T> >&& action);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i) override;
		
		BasicOneKeyInteraction<T>* copy() override;
	
	protected:
		BoxPtr<BasicKeyAction<T> > action;
		Key key;
	};
	
	using OneKeyInteraction = BasicOneKeyInteraction<>;
	
	template<typename T>
	struct DecodePointer<BasicOneKeyInteraction<T> > {
		static bool decodePointer(const YAML::Node& node, BasicOneKeyInteraction<T>*& oneKeyInteraction);
	};
}

#include "BasicOneKeyInteraction.inl"
