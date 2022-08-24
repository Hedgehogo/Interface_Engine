//included into fileBuffer.hpp

namespace ui {
	template<typename T>
	std::map<std::string, T> FileBuffer<T>::objects = {};
	
	template<typename T>
	std::map<std::string, T*> FileBuffer<T>::aliases = {};
	
	template <typename T>
	T &FileBuffer<T>::getObjectReference(const std::string &name) {
		if(aliases.find(name) != aliases.end()) {
			return *aliases[name];
		}
		if(objects.find(name) == objects.end()) {
			objects[name].loadFromFile(name);
		}
		return objects[name];
	}
	
	template <typename T>
	void FileBuffer<T>::setObject(const std::string &name, const std::string &filePath) {
		objects[name].loadFromFile(filePath);
	}
	
	template <typename T>
	void FileBuffer<T>::addAlias(const std::string &name, const std::string &alias) {
		aliases[alias] = &getObjectReference(name);
	}
}