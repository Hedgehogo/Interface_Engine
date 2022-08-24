//included into buffer.hpp

namespace ui {
	template <typename T, typename... A>
	void Buffer::addObject(const std::string& name, A &&... args) {
		objectsLevels[objectsLevels.size() - 1].try_emplace(name, std::make_shared<T>(args...));
	}
	
	template <typename T>
	void Buffer::addObject(const std::string &name, const YAML::Node &node) {
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
	void Buffer::addObject(const YAML::Node &node) {
		std::string name;
		node["name"] >> name;
		if(!existObject(name)) {
			addObject<T>(name, node);
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
	}
	
	template <typename T>
	std::shared_ptr<T> Buffer::getObject(const std::string &name) {
		std::shared_ptr<T> ptr;
		for(auto level = objectsLevels.rbegin(); level != objectsLevels.rend(); ++level) {
			try {
				ptr = std::dynamic_pointer_cast<T>(level->at(name));
				if(ptr.get() != NULL)
					return ptr;
			} catch(std::out_of_range&) {}
		}
		throw BufferVariableNotFoundException{name, typeid(T)};
	}
	
	template <typename T>
	std::shared_ptr<T> Buffer::getObject(const YAML::Node &node) {
		std::string name;
		if(node.IsScalar()) {
			node >> name;
		} else {
			node["name"] >> name;
			if(!existObject(name)) {
				addObject<T>(name, node);
			}
		}
		return getObject<T>(name);
	}
	
	template <typename T>
	std::shared_ptr<T> getRef(std::string name) {
		return Buffer::getObject<T>(name);
	}
	
	template <typename T, typename... A>
	void add(const std::string& name, A &&... args) {
		Buffer::addObject<T>(name, args...);
	}
}