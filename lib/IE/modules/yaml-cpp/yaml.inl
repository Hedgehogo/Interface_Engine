//included into yaml.hpp

template<typename T>
sf::Vector2<T> operator*(const sf::Vector2<T>& first, const sf::Vector2<T>& second) {
	return {first.x * second.x, first.y * second.y};
}

template<typename T>
sf::Vector2<T> operator/(const sf::Vector2<T>& first, const sf::Vector2<T>& second) {
	return {first.x / second.x, first.y / second.y};
}

namespace ie {
	template<class T>
	std::string type_name(const T& type) {
		return demangle(typeid(type).name());
	}
	
	template<class T>
	std::string type_name() {
		return demangle(typeid(T).name());
	}
	
	template<typename T>
	bool create_pointer(const YAML::Node& node, T*& object) {
		return DecodePointer<T>::decode_pointer(node, object);
	}
	
	
	template<typename T>
	T convert_default(const YAML::Node& node, const T& default_value) {
		return (node.IsDefined() ? node.as<T>() : default_value);
	}
	
	template<typename T>
	T conv_def(const YAML::Node& node, const T& default_value) {
		return convert_default<T>(node, default_value);
	}
	
	template<typename B, typename T, typename ...Arg>
	B* convert_default_ptr(const YAML::Node& node, Arg&&... arg) {
		return node.IsDefined() ? node.as<B*>() : new T{arg...};
	}
	
	template<typename B, typename T, typename ...Arg>
	B* conv_def_ptr(const YAML::Node& node, Arg&&... arg) {
		return convert_default_ptr<B, T>(node, arg...);
	}
	
	template<typename B, typename T, typename ...Arg>
	BoxPtr<B> convert_default_box_ptr(const YAML::Node& node, Arg&&... arg) {
		return node.IsDefined() ? node.as<BoxPtr<B> >() : make_box_ptr<T>(arg...);
	}
	
	template<typename B, typename T, typename ...Arg>
	BoxPtr<B> conv_def_box_ptr(const YAML::Node& node, Arg&&... arg) {
		return convert_default_box_ptr<B, T>(node, arg...);
	}
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T>, bool>
	Decode<BoxPtr<T>>::decode(const YAML::Node& node, BoxPtr<T>& object) {
		object = BoxPtr{node.as<T*>()};
		return true;
	}
	
	/*old_yaml_decode_impl
	template<typename T>
	bool Decode<orl::Option<T> >::decode(const YAML::Node& node, orl::Option<T>& object) {
		if(node.IsNull()) {
			object = orl::Option<T>{};
		} else {
			object = orl::Option<T>{node.as<T>()};
		}
		return true;

	}
	*/
	
	/*old_yaml_decode_impl
	template<typename T>
	bool Decode<std::vector<T> >::decode(const YAML::Node& node, std::vector<T>& vector) {
		for(const auto& item: node) {
			vector.resize(vector.size() + 1);
			item >> vector[vector.size() - 1];
		}
		return true;

	}
	*/
	
	
	/*old_yaml_decode_impl
	template<typename T>
	bool Decode<sf::Vector2<T>>::decode(const YAML::Node& node, sf::Vector2<T>& vector) {
		vector.x = node[0].as<T>();
		vector.y = node[1].as<T>();
		return true;

	}
	*/
	
	
	/*old_yaml_decode_impl
	template<typename T>
	bool Decode<sf::Rect<T>>::decode(const YAML::Node& node, sf::Rect<T>& rect) {
		sf::Vector2<T> position;
		sf::Vector2<T> size;
		node["position"] >> position;
		node["size"] >> size;
		rect = sf::Rect<T>{position, size};
		return true;

	}
	*/
}
