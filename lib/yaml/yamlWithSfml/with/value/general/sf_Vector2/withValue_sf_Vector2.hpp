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
		
		static WithValue<sf::Vector2<T>> *createFromYaml(const YAML::Node &node);
	};
	
	typedef WithValue<sf::Vector2f> WithSfVec2f;
	typedef WithValue<sf::Vector2i> WithSfVec2i;
	typedef WithValue<sf::Vector2u> WithSfVec2u;
}

#include "withValue_sf_Vector2.inl"
