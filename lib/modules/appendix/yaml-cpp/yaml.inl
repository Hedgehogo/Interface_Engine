//included into yaml.hpp

template <typename T>
sf::Vector2<T> operator*(const sf::Vector2<T> &first, const sf::Vector2<T> &second) {
	return {first.x * second.x, first.y * second.y};
}

template <typename T>
sf::Vector2<T> operator/(const sf::Vector2<T> &first, const sf::Vector2<T> &second) {
	return {first.x / second.x, first.y / second.y};
}

namespace ui {
	template <class T>
	std::string type_name(const T& type) {
		return demangle(typeid(type).name());
	}
	
	template <class T>
	std::string type_name() {
		return demangle(typeid(T).name());
	}
	
	template <typename T>
	T* createPointer(const YAML::Node& node, bool &correctly) {
		T* object{nullptr};
		correctly = convertPointer(node, object);
		return object;
	}
	
	
	
	template <typename T>
	T convertDefault(const YAML::Node &node, const T &defaultValue) {
		return (node.IsDefined() ? node.as<T>() : defaultValue);
	}
	
	template<typename T>
	T convDef(const YAML::Node &node, const T &defaultValue) {
		return convertDefault<T>(node, defaultValue);
	}
	
	template<typename T>
	bool convert(const YAML::Node &node, std::vector<T> &vector) {
		for(const auto &item : node) {
			vector.resize(vector.size() + 1);
			item >> vector[vector.size() - 1];
		}
		return true;
	}
	
	template<typename T>
	bool convert(const YAML::Node& node, sf::Vector2<T>& vector) {
		vector.x = node[0].as<T>();
		vector.y = node[1].as<T>();
		return true;
	}
	
	template <typename T>
	bool convert(const YAML::Node &node, sf::Rect<T>  &rect) {
		sf::Vector2<T> position;
		sf::Vector2<T> size;
		node["position"] >> position;
		node["size"] >> size;
		rect = sf::Rect<T>{position, size};
		return true;
	}
}

namespace YAML {
	template <typename T>
	Node convert<T>::encode(const T& rhs) {
		return ui::convert(rhs);
	}
	
	template <typename T>
	bool convert<T>::decode(const Node& node, T& rhs) {
		return ui::convert(node, rhs);
	}
}

template <typename T>
std::enable_if_t<std::is_copy_constructible_v<T>, void>
operator>>(const YAML::Node &node, T &value) {
	value = node.as<T>();
}

template <typename T>
std::enable_if_t<!std::is_copy_constructible_v<T>, void>
operator>>(const YAML::Node &node, T &value) {
	YAML::convert<T>::decode(node, value);
}
