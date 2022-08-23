#pragma once
#include <SFML/Graphics.hpp>
#include "../value/iWithValue.hpp"
#include "../value/general/withValue.hpp"
#include "../value/reference//withReferenceValue.hpp"
#include "../value/coefficient/general/withCoefficientValue.hpp"
#include "../value/coefficient/reference/withReferenceCoefficientValue.hpp"

namespace ui {
	template<typename T>
class IWithVector2 {
	public:
		virtual const T& getX() const = 0;
		
		virtual void setX(const T& value) {
			setValue(sf::Vector2<T>{value, getY()});
		}
		
		virtual const T& getY() const = 0;
		
		virtual void setY(const T& value) {
			setValue(sf::Vector2<T>{getX(), value});
		}
		
		virtual sf::Vector2<T> getValue() const {
			return sf::Vector2<T>{getX(), getY()};
		}
		
		virtual void setValue(const sf::Vector2<T>& vector) {
			setX(vector.x);
			setY(vector.y);
		}
	};
	
	typedef IWithVector2<float> IWithVec2f;
	typedef IWithVector2<int> IWithVec2i;
	typedef IWithVector2<unsigned> IWithVec2u;
}
