//included into buffer.hpp

#include "modules/appendix/yaml-cpp/shared/value/general/sValue.hpp"

namespace ui {
	template <typename T, typename... A>
	void Buffer::emplace(const std::string& name, A &&... args) {
		objectsLevels[objectsLevels.size() - 1].try_emplace(name, std::make_shared<T>(args...));
	}
	
	template <typename T>
	void Buffer::insert(const std::string &name, const YAML::Node &node) {
		T* ptr;
		long long level{static_cast<long long>(objectsLevels.size()) - 1};
		
		node >> ptr;
		if(node["level"]) {
			if(node["level"]["relative"]) {
				long long relative;
				node["level"]["relative"] >> relative;
				level -= relative;
			} else {
				if(node.IsScalar()) {
					node["level"] >> level;
				} else {
					node["level"]["absolute"] >> level;
				}
			}
		}
		
		if(level >= 0 && level < objectsLevels.size()) {
			objectsLevels[level].try_emplace(name, ptr);
		} else {
			throw BufferNonExistentNestingLevelException{node.Mark(), name, level};
		}
	}
	
	template <typename T>
	void Buffer::insert(const YAML::Node &node) {
		std::string name;
		node["var"] >> name;
		if(!existAtLevel(name)) {
			insert<T>(name, node);
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
	}
	
	template <typename T>
	std::shared_ptr<T> Buffer::at(const std::string &fullName) {
		std::shared_ptr<T> ptr;
		std::vector<std::string> names{splitByDelimiter(fullName, '.')};
		std::string name{names[0]};
		names.erase(names.begin());
		for(auto level = objectsLevels.rbegin(); level != objectsLevels.rend(); ++level) {
			if(auto object = level->find(name); object != level->end()) {
				ptr = std::dynamic_pointer_cast<T>(getVariable(object->second, names));
				if(ptr.get() != nullptr) {
					return ptr;
				}
			}
		}
		throw BufferVariableNotFoundException{fullName, type_name<T>()};
	}
	
	template <typename T>
	std::shared_ptr<T> Buffer::get(const YAML::Node &node, bool createIfNotExist) {
		std::string name;
		if(node.IsScalar()) {
			node >> name;
		} else {
			node["var"] >> name;
			if(createIfNotExist && !existAtLevel(name)) {
				insert<T>(name, node);
			}
		}
		try {
			return at<T>(name);
		} catch (BufferVariableNotFoundException &exception) {
			throw YamlBufferVariableNotFoundException{node.Mark(), exception};
		}
	}

	template <typename T>
	std::shared_ptr<T> atSValue(std::string name) {
		return Buffer::at<T>(name);
	}
	
	template <typename T, typename... A>
	void emplaceSValue(const std::string& name, A &&... args) {
		Buffer::insert<T>(name, args...);
	}

	template<typename T>
	std::shared_ptr<T> getSValue(const YAML::Node &node, bool createIfNotExist){
		return Buffer::get<T>(node, createIfNotExist);
	}
}