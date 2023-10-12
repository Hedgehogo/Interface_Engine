#pragma once

#include "../BasicKeyAction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicBaseKeyAction : public virtual BasicKeyAction<T> {
	public:
		BasicBaseKeyAction() = default;
		
		void init(BasicActionInitInfo<T> initInfo) override;
		
		void setPressed(bool pressed) override;
		
		void update(sf::Vector2i mousePosition, bool press) override;
	
	protected:
		virtual void startPressed() = 0;
		
		virtual void stopPressed() = 0;
		
		virtual void whilePressed() = 0;
		
		virtual void whileNotPressed() = 0;
		
		sf::Vector2i mousePosition;
	};
	
	using BaseKeyAction = BasicBaseKeyAction<>;
}

#include "BasicBaseKeyAction.inl"
