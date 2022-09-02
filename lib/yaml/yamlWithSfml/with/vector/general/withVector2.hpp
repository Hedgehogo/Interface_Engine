#pragma once
#include "../iWithVector2.hpp"

namespace ui {
	template<typename T>
	class WithVector2 : public IWithVector2 {
	private:
		typedef to_auto<decltype(std::declval<T>().getValue())> V;
	
	protected:
		std::shared_ptr<T> x, y;
	
	public:
		WithVector2(const sf::Vector2<V> &vector = {});
		
		WithVector2(std::shared_ptr<T> x, std::shared_ptr<T> y);
		
		std::shared_ptr<IWith> getXPtr() const override;
		
		void setXPtr(std::shared_ptr<IWith> value) override;
		
		std::shared_ptr<IWith> getYPtr() const override;
		
		void setYPtr(std::shared_ptr<IWith> value) override;
		
		V getX() const;
		
		void setX(const V &value);
		
		V getY() const;
		
		void setY(const V &value);
		
		sf::Vector2<V> getValue() const;
		
		void setValue(const sf::Vector2<V> &vector);
		
		static WithVector2 *createFromYaml(const YAML::Node &node);
	};
	
	template <typename T>
	using WithVec2 = WithVector2<T>;
	
	typedef WithVec2<WithValue<float>> WithVec2f;
	typedef WithVec2<WithValue<int>> WithVec2i;
	typedef WithVec2<WithValue<unsigned>> WithVec2u;
	typedef WithVec2<WithCoefficientValue> WithCoefficientVec2;
}

#include "withVector2.inl"
