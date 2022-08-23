#pragma once
#include "../iWithVector2.hpp"

namespace ui {
	template<typename T>
	using remove_all_extents = typename std::remove_all_extents<T>::type;
	
	template<typename T>
	using to_auto = std::remove_const_t<std::remove_reference_t<T>>;
	
	template<typename V>
	class WithVector2 : public IWithVector2<to_auto<decltype(std::declval<V>().getValue())>> {
	private:
		typedef to_auto<decltype(std::declval<V>().getValue())> T;
		
	protected:
		V x, y;
		
	public:
		WithVector2(const sf::Vector2<T>& vector = {}) : x(vector.x), y(vector.y) {}
		
		WithVector2(const YAML::Node& node) : x(T{}), y(T{}) {
			sf::Vector2<T> vector{};
			if(node["vector"])
				node["vector"] >> vector;
			setValue(vector);
		}
		
		const T& getX() const override { return x.getValue(); }
		
		void setX(const T& value) override { x.setValue(value); }
		
		const T& getY() const override { return y.getValue(); }
		
		void setY(const T& value) override { y.setValue(value); }
		
		sf::Vector2<T> getValue() const override {
			return sf::Vector2<T>{x.getValue(), y.getValue()};
		}
		
		void setValue(const sf::Vector2<T>& vector) override {
			x.setValue(vector.x);
			y.setValue(vector.y);
		}
		
		V& getXReference() { return x; }
		
		V& getYReference() { return y; }
	};
	
	template<typename T>
	class WithVector2<sf::Vector2<T>> : public IWithVector2<T> {
	protected:
		sf::Vector2<T> vector;
	
	public:
		WithVector2(const sf::Vector2<T>& vector = {}) : vector(vector) {}
		
		const T& getX() const override { return vector.x; }
		
		void setX(const T& value) override { vector.x = value; }
		
		const T& getY() const override { return vector.y; }
		
		void setY(const T& value) override { vector.y = value; }
		
		sf::Vector2<T> getValue() const override { return vector; }
		
		void setValue(const sf::Vector2<T>& vector) override { this->vector = vector;}
	};
	
	template<typename T>
	using WithVec2 = WithVector2<T>;
	
	typedef WithVec2<WithValue<float>> WithVec2f;
	typedef WithVec2<WithValue<int>> WithVec2i;
	typedef WithVec2<WithValue<unsigned>> WithVec2u;
	typedef WithVec2<WithCoefficientValue> WithCoefficientVec2;
}
