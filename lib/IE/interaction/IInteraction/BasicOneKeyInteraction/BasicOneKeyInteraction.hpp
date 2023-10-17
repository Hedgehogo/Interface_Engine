#pragma once

#include "../IInteraction.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	template<typename T>
	class BasicOneKeyInteraction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicOneKeyInteraction : public virtual IBasicInteraction<T> {
			BoxPtr<BasicKeyAction<T> > action;
			Key key;
			
			BasicOneKeyInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key);
			
			ie::BasicOneKeyInteraction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicOneKeyInteraction : public virtual IBasicInteraction<T> {
	public:
		using Make = make_system::BasicOneKeyInteraction<T>;
		
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