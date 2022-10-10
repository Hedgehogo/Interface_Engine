#pragma once
#include "../sReferenceValue.hpp"

namespace ui {
	template<typename T>
	class SReferenceValue<sf::Vector2<T>> : public virtual ISValue<sf::Vector2<T>> {
	protected:
		sf::Vector2<T>* valueReference;
	
	public:
		SReferenceValue(sf::Vector2<T>& value);
		
		const T& getX() const override;
		
		void setX(const T& value) override;
		
		const T& getY() const override;
		
		void setY(const T& value) override;
		
		const sf::Vector2<T> &getValue() const override;
		
		void setValue(const sf::Vector2<T>& vector) override;
		
		void setReference(T& valueReference) override;
	};
	
	typedef SReferenceValue<sf::Vector2f> SRefSfVec2f;
	typedef SReferenceValue<sf::Vector2i> SRefSfVec2i;
	typedef SReferenceValue<sf::Vector2u> SRefSfVec2u;
}

#include "sReferenceValue_sf_Vector2.inl"
