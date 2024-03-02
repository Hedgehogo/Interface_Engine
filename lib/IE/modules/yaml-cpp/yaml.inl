//included into yaml.hpp

template<typename T>
auto operator*(const sf::Vector2<T>& first, const sf::Vector2<T>& second) -> sf::Vector2<T> {
	return {first.x * second.x, first.y * second.y};
}

template<typename T>
auto operator/(const sf::Vector2<T>& first, const sf::Vector2<T>& second) -> sf::Vector2<T> {
	return {first.x / second.x, first.y / second.y};
}

namespace ie {
	template<class T>
	auto type_name(const T& type) -> std::string {
		return demangle(typeid(type).name());
	}
	
	template<class T>
	auto type_name() -> std::string {
		return demangle(typeid(T).name());
	}
	
	template<typename T>
	auto create_pointer(const YAML::Node& node, T*& object) -> bool {
		return DecodePointer<T>::decode_pointer(node, object);
	}
	
	
	template<typename T>
	auto convert_default(const YAML::Node& node, const T& default_value) -> T {
		return (node.IsDefined() ? node.as<T>() : default_value);
	}
	
	template<typename T>
	auto conv_def(const YAML::Node& node, const T& default_value) -> T {
		return convert_default<T>(node, default_value);
	}
	
	template<typename B, typename T, typename ...Arg>
	auto convert_default_ptr(const YAML::Node& node, Arg&&... arg) -> B* {
		return node.IsDefined() ? node.as<B*>() : new T{arg...};
	}
	
	template<typename B, typename T, typename ...Arg>
	auto conv_def_ptr(const YAML::Node& node, Arg&&... arg) -> B* {
		return convert_default_ptr<B, T>(node, arg...);
	}
	
	template<typename B, typename T, typename ...Arg>
	auto convert_default_box_ptr(const YAML::Node& node, Arg&&... arg) -> BoxPtr<B> {
		return node.IsDefined() ? node.as<BoxPtr<B> >() : make_box_ptr<T>(arg...);
	}
	
	template<typename B, typename T, typename ...Arg>
	auto conv_def_box_ptr(const YAML::Node& node, Arg&&... arg) -> BoxPtr<B> {
		return convert_default_box_ptr<B, T>(node, arg...);
	}
	
	template<typename T>
	auto Decode<BoxPtr<T> >::decode(const YAML::Node& node, BoxPtr<T>& object) -> std::enable_if_t<std::is_class_v<T>, bool> {
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
