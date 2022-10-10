#pragma once
#include "../iSVector2.hpp"

namespace ui {
	template<typename T>
	class SVector2 : public ISVector2 {
	public:
		typedef to_auto<decltype(std::declval<T>().getValue())> V;
	
	protected:
		std::shared_ptr<T> x, y;
	
	public:
		SVector2(const sf::Vector2<V> &vector = {});
		
		SVector2(std::shared_ptr<T> x, std::shared_ptr<T> y);
		
		PIShared getXPtr() const override;
		
		void setXPtr(PIShared value) override;
		
		PIShared getYPtr() const override;
		
		void setYPtr(PIShared value) override;
		
		V getX() const;
		
		void setX(const V &value);
		
		V getY() const;
		
		void setY(const V &value);
		
		sf::Vector2<V> getValue() const;
		
		void setValue(const sf::Vector2<V> &vector);
	};
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, SVector2<T> *&withVector2);
	
	template <typename T>
	using SVec2 = SVector2<T>;
	
	template <typename T>
	using PSVec2 = std::shared_ptr<SVec2<T>>;
	
	typedef SVec2<Sfloat> SVec2f;
	typedef SVec2<Sint> SVec2i;
	typedef SVec2<Suint> SVec2u;
	typedef SVec2<SCoefficientValue> SCoefficientVec2;
	
	typedef std::shared_ptr<SVec2f> PSVec2f;
	typedef std::shared_ptr<SVec2i> PSVec2i;
	typedef std::shared_ptr<SVec2u> PSVec2u;
	typedef std::shared_ptr<SCoefficientVec2> PSCoefficientVec2;
}

#include "sVector2.inl"
