#pragma once
#include "../withValue.hpp"

namespace ui {
	template<typename T>
	class WithValue<sf::Vector2<T>> : public virtual IWithValue<sf::Vector2<T>> {
	protected:
		sf::Vector2<T> value;
	
	public:
		WithValue(const sf::Vector2<T>& value = {});
		
		const T& getX() const override;
		
		void setX(const T& value) override;
		
		const T& getY() const override;
		
		void setY(const T& value) override;
		
		const sf::Vector2<T> &getValue() const override;
		
		void setValue(const sf::Vector2<T>& vector) override;
	};
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, WithValue<sf::Vector2<T>> *&withValueVector2);
	
	typedef WithValue<sf::Vector2f> WithSfVec2f;
	typedef WithValue<sf::Vector2i> WithSfVec2i;
	typedef WithValue<sf::Vector2u> WithSfVec2u;
}

#include "withValue_sf_Vector2.inl"
