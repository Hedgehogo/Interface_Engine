namespace ie {
	template<typename Type>
	bool build_or_process(const YAML::Node& node, Type*& object) {
		auto type{node["type"].as<std::string>()};
		if(type == "file") {
			return load_from_yaml_file(node, object);
		} else if(type == "if") {
			return load_from_yaml_if(node, object);
		} else if(type == "copy") {
			return load_from_yaml_object(node, object);
		} else {
			return YamlBuilder<Type>::build(node, type, object);
		}
	}
	
	template<typename T>
	bool load_from_yaml_file(const YAML::Node& node, T*& object) {
		std::string file_path;
		node["file-path"] >> file_path;
		object = load_from_yaml<T>(file_path);
		return true;
	}
	
	template<typename T>
	bool load_from_yaml_if(const YAML::Node& node, T*& object) {
		if(Buffer::exist(node["condition"])) {
			node["first"] >> object;
		} else {
			Buffer::insert<Sbool>(node["condition"]);
			node["second"] >> object;
		}
		return true;
	}
	
	template<typename T>
	bool load_from_yaml_object(const YAML::Node& node, T*& object) {
		std::string name{node["name"].as<std::string>()};
		
		if(node["object"]) {
			ObjectBuffer::add(name, node["object"]);
		}
		if(ObjectBuffer::has(name)) {
			YAML::Node object_node{ObjectBuffer::get(name)};
			object_node >> object;
			return true;
		}
		throw YAML::BadConversion(node.Mark());
	}
	
	template<typename T>
	T* load_from_yaml(std::string file_path) {
		YAML::Node node = YAML::LoadFile(file_path);
		T* object;
		Buffer::read_level([&node, &object]() {
			node >> object;
		});
		return object;
	}
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T>, bool> Decode<T*>::decode(const YAML::Node& node, T*& object) {
		if(node.IsMap() && node["type"]) {
			return build_or_process<T>(node, object);
		} else {
			if constexpr(std::is_abstract_v<T>) {
				std::string type;
				YamlBuilder<T>::determine_type(node, type);
				return YamlBuilder<T>::build(node, type, object);
			} else {
				return create_pointer<T>(node, object);
			}
		}
	}
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T> && std::is_abstract_v<T>, bool>
	convert(const YAML::Node& node, T*& object) {
		if(node.IsMap() && node["type"]) {
			return build_or_process<T>(node, object);
		} else {
			std::string type;
			YamlBuilder<T>::determine_type(node, type);
			return YamlBuilder<T>::build(node, type, object);
		}
	}
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T> && !std::is_abstract_v<T>, bool>
	convert(const YAML::Node& node, T*& object) {
		if(node.IsMap() && node["type"]) {
			return build_or_process<T>(node, object);
		} else {
			return create_pointer<T>(node, object);
		}
	}
}