//included into withVector2.inl

namespace ui {
	template <typename V>
	WithVector2<V>::WithVector2(const sf::Vector2<typename WithVector2<V>::T> &vector) : x(vector.x), y(vector.y) {}
	
	template <typename V>
	WithVector2<V>::WithVector2(const YAML::Node &node) : x(typename WithVector2<V>::T{}), y(typename WithVector2<V>::T{}) {
		sf::Vector2<typename WithVector2<V>::T> vector{};
		
		if(node["vector"])
			node["vector"] >> vector;
		
		setValue(vector);
	}
	
	template <typename V>
	const typename WithVector2<V>::T &WithVector2<V>::getX() const {
		return x.getValue();
	}
	
	template <typename V>
	void WithVector2<V>::setX(const typename WithVector2<V>::T &value) {
		x.setValue(value);
	}
	
	template <typename V>
	const typename WithVector2<V>::T &WithVector2<V>::getY() const {
		return y.getValue();
	}
	
	template <typename V>
	void WithVector2<V>::setY(const typename WithVector2<V>::T &value) {
		y.setValue(value);
	}
	
	template <typename V>
	sf::Vector2<typename WithVector2<V>::T> WithVector2<V>::getValue() const {
		return sf::Vector2<typename WithVector2<V>::T>{x.getValue(), y.getValue()};
	}
	
	template <typename V>
	void WithVector2<V>::setValue(const sf::Vector2<typename WithVector2<V>::T> &vector) {
		x.setValue(vector.x);
		y.setValue(vector.y);
	}
	
	template <typename V>
	WithVector2<V> *WithVector2<V>::createFromYaml(const YAML::Node &node) {
		sf::Vector2<typename WithVector2<V>::T> vector{};
		
		if(node["vector"])
			node["vector"] >> vector;
		
		return new WithVector2<V>(vector);
	}
	
	template <typename V>
	V &WithVector2<V>::getXReference() {
		return x;
	}
	
	template <typename V>
	V &WithVector2<V>::getYReference() {
		return y;
	}
}