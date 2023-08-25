#pragma once

#include "../IInteraction.hpp"
#include "../../../Enums/KeyHandler/KeyHandler.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicOneKeyInteraction : public virtual IBasicInteraction<T> {
	public:
		BasicOneKeyInteraction(BoxPtr<BasicKeyEvent<T> >&& event, Key key);
		
		void init(BasicInteractionInitInfo<T> initInfo) override;
		
		Key getKey();
		
		BasicKeyEvent<T>& getEvent();
		
		const BasicKeyEvent<T>& getEvent() const;
		
		void setEvent(BoxPtr<BasicKeyEvent<T> >&& event);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i) override;
		
		BasicOneKeyInteraction<T>* copy() override;
	
	protected:
		BoxPtr<BasicKeyEvent<T> > event;
		Key key;
	};
	
	using OneKeyInteraction = BasicOneKeyInteraction<>;
	
	template<typename T>
	struct DecodePointer<BasicOneKeyInteraction<T> > {
		static bool decodePointer(const YAML::Node& node, BasicOneKeyInteraction<T>*& oneKeyInteraction);
	};
}

#include "BasicOneKeyInteraction.inl"
