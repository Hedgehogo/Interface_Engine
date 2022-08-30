//included into buffer.hpp

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
			throw BufferNonExistentNestingLevelException{name, level};
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
		return at<T>(name);
	}
	
	template<typename T>
	WithVector2<T> *WithVector2<T>::createFromYaml(const YAML::Node &node) {
		if(node["x"] && node["y"]) {
			return new WithVector2<T>(Buffer::get<T>(node["x"]), Buffer::get<T>(node["y"]));
		} else {
			sf::Vector2<typename WithVector2<T>::V> vector;
			
			if(node["vector"]) node["vector"] >> vector;
			
			return new WithVector2<T>(vector);
		}
	}
	
	template <typename T>
	std::shared_ptr<T> atYaml(std::string name) {
		return Buffer::at<T>(name);
	}
	
	template <typename T, typename... A>
	void insertYaml(const std::string& name, A &&... args) {
		Buffer::insert<T>(name, args...);
	}
}