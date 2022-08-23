//included into buffer.hpp

namespace ui {
	template <typename T, typename... A>
	void Buffer::addObject(const std::string name, A &&... args) {
		objects.try_emplace(name, std::make_shared<T>(args...));
	}
	
	template <typename T>
	void Buffer::addObject(const std::string &name, const YAML::Node &node) {
		T* ptr;
		node >> ptr;
		objects.try_emplace(name, ptr);
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
		auto ptr = std::dynamic_pointer_cast<T>(objects[name]);
		if(ptr.get() == NULL)
			throw BufferBadCastException{name, typeid(T)};
		return ptr;
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
	void add(const std::string name, A &&... args) {
		Buffer::addObject<T>(name, args...);
	}
}