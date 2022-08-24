#pragma once
#include "../iWithVector2.hpp"

namespace ui {
	template <typename T>
	using to_auto = std::remove_const_t<std::remove_reference_t<T>>;
	
	template <typename V>
	class WithVector2 : public IWithVector2<to_auto<decltype(std::declval<V>().getValue())>> {
	private:
		typedef to_auto<decltype(std::declval<V>().getValue())> T;
	
	protected:
		V x, y;
	
	public:
		WithVector2(const sf::Vector2<T> &vector = {});
		
		WithVector2(const YAML::Node &node);
		
		const T &getX() const override;
		
		void setX(const T &value) override;
		
		const T &getY() const override;
		
		void setY(const T &value) override;
		
		sf::Vector2<T> getValue() const override;
		
		void setValue(const sf::Vector2<T> &vector) override;
		
		static WithVector2<V> *createFromYaml(const YAML::Node &node);
		
		V &getXReference();
		
		V &getYReference();
	};
	
	template <typename T>
	using WithVec2 = WithVector2<T>;
	
	typedef WithVec2<WithValue<float>> WithVec2f;
	typedef WithVec2<WithValue<int>> WithVec2i;
	typedef WithVec2<WithValue<unsigned>> WithVec2u;
	typedef WithVec2<WithCoefficientValue> WithCoefficientVec2;
}

#include "withVector2.inl"
