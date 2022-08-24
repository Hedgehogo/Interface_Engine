#pragma once
#include <SFML/Graphics.hpp>
#include "../value/iWithValue.hpp"
#include "../value/general/withValue.hpp"
#include "../value/general/sf_Vector2/withValue_sf_Vector2.hpp"
#include "../value/reference//withReferenceValue.hpp"
#include "../value/coefficient/general/withCoefficientValue.hpp"
#include "../value/coefficient/reference/withReferenceCoefficientValue.hpp"

namespace ui {
	template<typename T>
	class IWithVector2 : public IWith {
	public:
		virtual const T& getX() const = 0;
		
		virtual void setX(const T& value);
		
		virtual const T& getY() const = 0;
		
		virtual void setY(const T& value);
		
		virtual sf::Vector2<T> getValue() const;
		
		virtual void setValue(const sf::Vector2<T>& vector);
		
		static IWithVector2<T> *createFromYaml(const YAML::Node &node);
	};
	
	typedef IWithVector2<float> IWithVec2f;
	typedef IWithVector2<int> IWithVec2i;
	typedef IWithVector2<unsigned> IWithVec2u;
}

#include "iWithVector2.inl"
