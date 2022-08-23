//included into yamlBuilder.hpp

namespace ui {
	template <typename T>
	void YamlBuilder<T>::add(YamlBuilder::makeObject function, std::string type, std::vector<std::string> aliases) {
		typeMap[type] = function;
		addAliases(type, aliases);
	}
	
	template <typename T>
	void YamlBuilder<T>::addSubtype(YamlBuilder::makeSubobject function) {
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
	void YamlBuilder<T>::addSubtype() {
		addSubtype(YamlBuilder<Subtype>::build);
	}
	
	template <typename T>
	T *YamlBuilder<T>::build(const YAML::Node &node, std::string type) {
		for(const auto &subtype: subtypeMap) {
			try {
				return subtype(node, type);
			} catch (ui::NonexistentTypeYamlException&) {}
		}
		try {
			return typeMap.at(type)(node);
		} catch (std::out_of_range&) {
			throw ui::NonexistentTypeYamlException{type};
		}
	}
	
	template<typename T>
	std::map<std::string, typename YamlBuilder<T>::makeObject> YamlBuilder<T>::typeMap = {};
	
	template<typename T>
	std::vector<typename YamlBuilder<T>::makeSubobject> YamlBuilder<T>::subtypeMap = {};
	
	template <typename T>
	T *loadFromYaml(std::string filename) {
		YAML::Node node = YAML::LoadFile(filename);
		T* object;
		node >> object;
		return object;
	}
}

template <typename T>
void operator>>(const YAML::Node &node, T *&object) {
	if(node["type"]) {
		std::string type;
		node["type"] >> type;
		object = ui::YamlBuilder<T>::build(node, type);
	} else {
		T* result = dynamic_cast<T*>(T::createFromYaml(node));
		if(!result) throw ui::AbstractTypeYamlException{};
		object = result;
	}
}