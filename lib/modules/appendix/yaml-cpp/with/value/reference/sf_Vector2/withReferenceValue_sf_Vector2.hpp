#pragma once
#include "../withReferenceValue.hpp"

namespace ui {
	template<typename T>
	class WithReferenceValue<sf::Vector2<T>> : public virtual IWithValue<sf::Vector2<T>> {
	protected:
		sf::Vector2<T>* valueReference;
	
	public:
		WithReferenceValue(sf::Vector2<T>& value);
		
		const T& getX() const override;
		
		void setX(const T& value) override;
		
		const T& getY() const override;
		
		void setY(const T& value) override;
		
		const sf::Vector2<T> &getValue() const override;
		
		void setValue(const sf::Vector2<T>& vector) override;
		
		void setReference(T& valueReference) override;
	};
	
	typedef WithReferenceValue<sf::Vector2f> WithRefSfVec2f;
	typedef WithReferenceValue<sf::Vector2i> WithRefSfVec2i;
	typedef WithReferenceValue<sf::Vector2u> WithRefSfVec2u;
}

#include "withReferenceValue_sf_Vector2.inl"
