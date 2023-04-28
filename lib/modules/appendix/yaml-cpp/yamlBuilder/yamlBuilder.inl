namespace ui{
	template<typename Type>
	bool buildOrProcess(const YAML::Node& node, Type *&object) {
		auto type{node["type"].as<std::string>()};
		if(type == "file") {
			return loadFromYamlFile(node, object);
		} else if(type == "if") {
			return loadFromYamlIf(node, object);
		} else if(type == "copy") {
			return loadFromYamlObject(node, object);
		} else {
			return YamlBuilder<Type>::build(node, type, object);
		}
	}
	
	template <typename T>
	bool loadFromYamlFile(const YAML::Node &node, T *&object) {
		std::string filePath;
		node["file-path"] >> filePath;
		object = loadFromYaml<T>(filePath);
		return true;
	}
	
	template<typename T>
	bool loadFromYamlIf(const YAML::Node &node, T *&object) {
		if(Buffer::exist(node["condition"])) {
			node["first"] >> object;
		} else {
			Buffer::insert<Sbool>(node["condition"]);
			node["second"] >> object;
		}
		return true;
	}
	
	template<typename T>
	bool loadFromYamlObject(const YAML::Node &node, T *&object) {
		std::string name {node["name"].as<std::string>()};
		
		if (node["object"]) {
			ObjectBuffer::add(name, node["object"]);
		}
		if (ObjectBuffer::has(name)) {
			YAML::Node objectNode{ObjectBuffer::get(name)};
			objectNode >> object;
			return true;
		}
		throw YAML::BadConversion(node.Mark());
	}
	
	template <typename T>
	T *loadFromYaml(std::string filePath) {
		YAML::Node node = YAML::LoadFile(filePath);
		T* object;
		Buffer::readLevel([&node, &object](){
			node >> object;
		});
		return object;
	}
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T>, bool> Decode<T*>::decode(const YAML::Node& node, T*& object) {
		if(node.IsMap() && node["type"]) {
			return buildOrProcess<T>(node, object);
		} else {
			if constexpr(std::is_abstract_v<T>) {
				std::string type;
				YamlBuilder<T>::determineType(node, type);
				return YamlBuilder<T>::build(node, type, object);
			} else {
				return createPointer<T>(node, object);
			}
		}
	}
	
	template <typename T>
	std::enable_if_t<std::is_class_v<T> && std::is_abstract_v<T>, bool>
	convert(const YAML::Node &node, T *&object) {
		if(node.IsMap() && node["type"]) {
			return buildOrProcess<T>(node, object);
		} else {
			std::string type;
			YamlBuilder<T>::determineType(node, type);
			return YamlBuilder<T>::build(node, type, object);
		}
	}
	
	template <typename T>
	std::enable_if_t<std::is_class_v<T> && !std::is_abstract_v<T>, bool>
	convert(const YAML::Node &node, T *&object) {
		if(node.IsMap() && node["type"]) {
			return buildOrProcess<T>(node, object);
		} else {
			return createPointer<T>(node, object);
		}
	}
}