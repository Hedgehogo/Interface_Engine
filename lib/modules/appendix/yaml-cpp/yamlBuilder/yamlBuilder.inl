//included into yamlBuilder.hpp
#include <utility>

namespace ui {
	template <typename T>
	T *loadFromYamlFile(const YAML::Node &node, bool &correctly) {
		std::string filePath;
		node["file-path"] >> filePath;
		correctly = true;
		return loadFromYaml<T>(filePath);
	}
	
	template<typename T>
	T* loadFromYamlIf(const YAML::Node &node, bool &correctly) {
		T* object;
		if(Buffer::exist(node["condition"])) {
			node["first"] >> object;
		} else {
			Buffer::insert<WithValue<bool>>(node["condition"]);
			node["second"] >> object;
		}
		correctly = true;
		return object;
	}

	template<typename T>
	T *loadFromYamlObject(const YAML::Node &node, bool &correctly) {
		std::string name {node["name"].as<std::string>()};

		if (node["object"]) {
			ObjectBuffer::add(name, node["object"]);
		}
		if (ObjectBuffer::has(name)) {
			YAML::Node objectNode{ObjectBuffer::get(name)};
			T* object;
			objectNode >> object;
			correctly = true;
			return object;
		}
		throw YAML::BadConversion(node.Mark());
	}
	
	template<typename T>
	std::map<std::string, typename YamlBuilder<T>::MakeObject> YamlBuilder<T>::typeMap = {
		std::make_pair("file", loadFromYamlFile<T>),
		std::make_pair("if", loadFromYamlIf<T>),
		std::make_pair("copy", loadFromYamlObject<T>),
	};
	
	template<typename T>
	std::vector<typename YamlBuilder<T>::MakeSubobject> YamlBuilder<T>::subtypeMap = {};
	template<typename T>
	typename YamlBuilder<T>::TypeNameDeformer YamlBuilder<T>::typeNameDeform = [](std::string typeName)->std::string {
		return removeNamespace(typeName, "ui");
	};
	
	template <typename T>
	void YamlBuilder<T>::setTypeNameDeformer(YamlBuilder<T>::TypeNameDeformer typeNameDeform) {
		YamlBuilder<T>::typeNameDeform = typeNameDeform;
	}
	
	template <typename T>
	void YamlBuilder<T>::add(YamlBuilder::MakeObject function, std::string type, std::vector<std::string> aliases) {
		typeMap[type] = function;
		addAliases(type, aliases);
	}
	
	template <typename T>
	void YamlBuilder<T>::addSubtype(YamlBuilder::MakeSubobject function) {
		subtypeMap.push_back(function);
	}
	
	template <typename T>
	void YamlBuilder<T>::addAlias(std::string type, std::string alias) {
		typeMap[alias] = typeMap.at(type);
	}
	
	template <typename T>
	void YamlBuilder<T>::addAliases(std::string type, std::vector<std::string> aliases) {
		for(const auto &alias: aliases) {
			addAlias(type, alias);
		}
	}
	
	template <typename T>
	template <typename Subtype>
	void YamlBuilder<T>::add(std::vector<std::string> aliases) {
		add(createPointer<Subtype>, typeNameDeform(type_name<Subtype>()), aliases);
	}
	
	template <typename T>
	template <typename Subtype>
	void YamlBuilder<T>::addSubtype() {
		addSubtype(YamlBuilder<Subtype>::build);
	}
	
	template <typename T>
	template <typename Subtype>
	void YamlBuilder<T>::addAlias(std::string alias) {
		addAlias(removeNamespace(type_name<Subtype>()), alias);
	}
	
	template <typename T>
	template <typename Subtype>
	void YamlBuilder<T>::addAliases(std::vector<std::string> aliases) {
		addAliases(removeNamespace(type_name<Subtype>()), aliases);
	}
	
	template <typename T>
	T *YamlBuilder<T>::build(const YAML::Node &node, std::string type, bool &correctly) {
		if(auto objectType = typeMap.find(type); objectType != typeMap.end()) {
			return objectType->second(node, correctly);
		} else {
			for(const auto &subtype: subtypeMap) {
				try {
					return subtype(node, type, correctly);
				} catch (ui::NonexistentTypeYamlException&) {}
			}
			throw ui::NonexistentTypeYamlException{node.Mark(), type, typeNameDeform(type_name<T>())};
		}
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
	
	template <typename T>
	std::enable_if_t<std::is_class_v<T>, YAML::Node>
	convert(const T *&object) {
		YAML::Node node;
		return node;
	}
	
	template <typename T>
	std::enable_if_t<std::is_class_v<T> && std::is_abstract_v<T>, bool>
	convert(const YAML::Node &node, T *&object) {
		bool correctly{true};
		std::string type;
		node["type"] >> type;
		object = ui::YamlBuilder<T>::build(node, type, correctly);
		return correctly;
	}
	
	template <typename T>
	std::enable_if_t<std::is_class_v<T> && !std::is_abstract_v<T>, bool>
	convert(const YAML::Node &node, T *&object) {
		bool correctly{true};
		if(node["type"]) {
			std::string type;
			node["type"] >> type;
			object = ui::YamlBuilder<T>::build(node, type, correctly);
		} else {
			T* result = dynamic_cast<T*>(createPointer<T>(node, correctly));
			object = result;
		}
		return correctly;
	}
}
