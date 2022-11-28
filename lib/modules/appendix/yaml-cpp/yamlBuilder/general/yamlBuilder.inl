//included into yamlBuilder.hpp
#include <utility>

namespace ui {
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
	
	template<typename T>
	YamlBuilder<T> YamlBuilder<T>::builder = {};
	template<typename T>
	std::vector<detail::IYamlBuilder*> YamlBuilder<T>::types = {};
	template<typename T>
	std::vector<std::string> YamlBuilder<T>::names = {};
	template<typename T>
	std::vector<detail::DetermineTypeFunc> YamlBuilder<T>::determiners = {};
	
	namespace detail {
		template <typename Type>
		std::enable_if_t<std::is_class_v<Type> && std::is_abstract_v<Type>, bool>
		build(const YAML::Node &node, void *&object) {
			throw AbstractTypeYamlException{node.Mark(), IYamlBuilder::typeNameDeform(type_name<Type>())};
		}
		
		template <typename Type>
		std::enable_if_t<std::is_class_v<Type> && !std::is_abstract_v<Type>, bool>
		build(const YAML::Node &node, void *&object) {
			return convertPointer(node, reinterpret_cast<Type*&>(object));
		}
	}
	
	template <typename Type>
	bool YamlBuilder<Type>::build(const YAML::Node &node, void *&object) const {
		return detail::build<Type>(node, object);
	}
	
	template <typename Type>
	detail::IYamlBuilder *YamlBuilder<Type>::getBuilder(const std::string &type) {
		if(std::find(names.begin(), names.end(), type) != names.end()) {
			return this;
		} else {
			for(const auto &item: types) {
				if(auto result = item->getBuilder(type); *result) {
					return result;
				}
			}
			return &detail::EmptyYamlBuilder::builder;
		}
	}
	
	template <typename Type>
	bool YamlBuilder<Type>::determine(const YAML::Node &node, std::string &type) {
		return std::any_of(determiners.begin(), determiners.end(), [&node, &type](DetermineType &determiner) {
			return determiner(node, type);
		}) || std::any_of(types.begin(), types.end(), [&node, &type](detail::IYamlBuilder *&builder) {
			return builder->determine(node, type);
		});
	}
	
	template <typename Type>
	bool YamlBuilder<Type>::build(const YAML::Node &node, const std::string &type, void *&object) {
		if(auto result = getBuilder(type); *result) {
			return result->build(node, object);
		} else {
			throw NonexistentTypeYamlException{node.Mark(), type, names[0]};
		}
	}
	
	template <typename Type>
	template <typename Derived>
	typename YamlBuilder<Type>::template is_derived<Derived, void> YamlBuilder<Type>::addType() {
		types.push_back(&YamlBuilder<Derived>::builder);
	}
	
	template <typename Type>
	void YamlBuilder<Type>::addType(detail::FuncYamlBuilder::BuildFunc<Type> function, std::vector<std::string> aliases) {
		types.push_back(&detail::FuncYamlBuilder::addBuilder<Type>(function, aliases));
	}
	
	template <typename Type>
	void YamlBuilder<Type>::addAlias(const std::string &alias) {
		if(names.empty()) names.push_back(typeNameDeform(type_name<Type>()));
		names.push_back(alias);
	}
	
	template <typename Type>
	void YamlBuilder<Type>::addAliases(std::vector<std::string> aliases) {
		if(names.empty()) names.push_back(typeNameDeform(type_name<Type>()));
		names.insert(names.end(), std::make_move_iterator(aliases.begin()), std::make_move_iterator(aliases.end()));
	}
	
	template <typename Type>
	void YamlBuilder<Type>::addDetermine(const YamlBuilder::DetermineType& function) {
		determiners.push_back(function);
	}
	
	template <typename Type>
	void YamlBuilder<Type>::addDetermine(const YamlBuilder::SimpleDetermineType& function) {
		determiners.push_back(DetermineType{[function](const YAML::Node& node, std::string &type) {
			type = names[0];
			return function(node);
		}});
	}
	
	template <typename Type>
	void YamlBuilder<Type>::determineType(const YAML::Node &node, std::string &type) {
		if(!builder.determine(node, type)) {
			throw FailedDetermineTypeYamlException{node.Mark(), names[0]};
		}
	}
	
	template <typename Type>
	bool YamlBuilder<Type>::build(const YAML::Node &node, const std::string &type, Type *&object) {
		return builder.build(node, type, reinterpret_cast<void *&>(object));
	}
	
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
