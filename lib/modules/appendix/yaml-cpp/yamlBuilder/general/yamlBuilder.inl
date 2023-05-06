//included into yamlBuilder.hpp
#include <utility>

namespace ui {
	template<typename T>
	YamlBuilder<T> YamlBuilder<T>::builder = {};
	template<typename T>
	std::vector<detail::IYamlBuilder*> YamlBuilder<T>::types = {};
	template<typename T>
	std::vector<std::string> YamlBuilder<T>::names = {};
	template<typename T>
	std::vector<detail::DetermineTypeFunc> YamlBuilder<T>::determiners = {};
	
	template<typename Type>
	bool YamlBuilder<Type>::build(const YAML::Node& node, void*& object) const {
		if constexpr(std::is_class_v<Type>){
			if constexpr(std::is_abstract_v<Type>){
				throw AbstractTypeYamlException{node.Mark(), IYamlBuilder::typeNameDeform(type_name<Type>())};
			} else {
				return DecodePointer<Type>::decodePointer(node, reinterpret_cast<Type*&>(object));
			}
		} else {
			static_assert("The YamlBuilder<Type>::build function was not requested by the class");
		}
	}
	
	template<typename Type>
	detail::IYamlBuilder* YamlBuilder<Type>::getBuilder(const std::string& type) {
		if(std::find(names.begin(), names.end(), type) != names.end()) {
			return this;
		} else {
			for(const auto& item: types) {
				if(auto result = item->getBuilder(type); *result) {
					return result;
				}
			}
			return &detail::EmptyYamlBuilder::builder;
		}
	}
	
	template<typename Type>
	bool YamlBuilder<Type>::determine(const YAML::Node& node, std::string& type) {
		return std::any_of(determiners.begin(), determiners.end(), [&node, &type](DetermineType& determiner) {
			return determiner(node, type);
		}) || std::any_of(types.begin(), types.end(), [&node, &type](detail::IYamlBuilder*& builder) {
			return builder->determine(node, type);
		});
	}
	
	template<typename Type>
	bool YamlBuilder<Type>::build(const YAML::Node& node, const std::string& type, void*& object) {
		if(auto result = getBuilder(type); *result) {
			return result->build(node, object);
		} else {
			throw NonexistentTypeYamlException{node.Mark(), type, names[0]};
		}
	}
	
	template<typename Type>
	void YamlBuilder<Type>::addType(detail::IYamlBuilder* builder) {
		types.emplace_back(builder);
	}
	
	template<typename Type>
	template<typename Derived>
	typename YamlBuilder<Type>::template is_derived<Derived, void> YamlBuilder<Type>::addType() {
		if(names.empty())
			names.push_back(typeNameDeform(type_name<Type>()));
		types.push_back(&YamlBuilder<Derived>::builder);
	}
	
	template<typename Type>
	void YamlBuilder<Type>::addType(detail::FuncYamlBuilder::BuildFunc<Type> function, std::vector<std::string> aliases) {
		if(names.empty())
			names.push_back(typeNameDeform(type_name<Type>()));
		types.push_back(&detail::FuncYamlBuilder::addBuilder<Type>(function, aliases));
	}
	
	template<typename Type>
	void YamlBuilder<Type>::addAlias(const std::string& alias) {
		if(names.empty())
			names.push_back(typeNameDeform(type_name<Type>()));
		names.push_back(alias);
	}
	
	template<typename Type>
	void YamlBuilder<Type>::addAliases(std::vector<std::string> aliases) {
		if(names.empty())
			names.push_back(typeNameDeform(type_name<Type>()));
		names.insert(names.end(), std::make_move_iterator(aliases.begin()), std::make_move_iterator(aliases.end()));
	}
	
	template<typename Type>
	void YamlBuilder<Type>::addDetermine(const YamlBuilder::DetermineType& function) {
		determiners.push_back(function);
	}
	
	template<typename Type>
	void YamlBuilder<Type>::addDetermine(const YamlBuilder::SimpleDetermineType& function) {
		determiners.push_back(DetermineType{[function](const YAML::Node& node, std::string& type) {
			type = names[0];
			return function(node);
		}});
	}
	
	template<typename Type>
	void YamlBuilder<Type>::determineType(const YAML::Node& node, std::string& type) {
		if(!builder.determine(node, type)) {
			throw FailedDetermineTypeYamlException{node.Mark(), names[0]};
		}
	}
	
	template<typename Type>
	bool YamlBuilder<Type>::build(const YAML::Node& node, const std::string& type, Type*& object) {
		return builder.build(node, type, reinterpret_cast<void*&>(object));
	}
	
	template<typename T>
	std::enable_if_t<std::is_class_v<T>, YAML::Node>
	convert(const T*& object) {
		YAML::Node node;
		return node;
	}
	
	template<typename T>
	void addToYamlBuilders() {
		detail::yamlBuilders.emplace(get_type_name<T>(), &YamlBuilder<T>::builder);
	}
}
