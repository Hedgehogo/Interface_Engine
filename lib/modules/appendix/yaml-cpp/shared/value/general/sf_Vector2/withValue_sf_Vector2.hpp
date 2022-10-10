#pragma once
#include "../withValue.hpp"

namespace ui {
	template<typename T>
	class SValue<sf::Vector2<T>> : public virtual ISValue<sf::Vector2<T>> {
	protected:
		sf::Vector2<T> value;
	
	public:
		SValue(const sf::Vector2<T>& value = {});
		
		const T& getX() const override;
		
		void setX(const T& value) override;
		
		const T& getY() const override;
		
		void setY(const T& value) override;
		
		const sf::Vector2<T> &getValue() const override;
		
		void setValue(const sf::Vector2<T>& vector) override;
	};
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, SValue<sf::Vector2<T>> *&sValue);
	
	typedef SValue<sf::Vector2f> SSfVec2f;
	typedef SValue<sf::Vector2i> SSfVec2i;
	typedef SValue<sf::Vector2u> SSfVec2u;
}

#include "withValue_sf_Vector2.inl"
