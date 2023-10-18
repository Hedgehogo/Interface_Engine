//included into file_buffer.hpp

namespace ie {
	template<typename T>
	void LoadFromFile<T>::load(T& object, std::string name) {
		object.loadFromFile(name);
	}
	
	template<typename T>
	std::map<std::string, T> FileBuffer<T>::objects = {};
	
	template<typename T>
	std::map<std::string, T*> FileBuffer<T>::aliases = {};
	
	template<typename T>
	T& FileBuffer<T>::get(const std::string& name) {
		if(aliases.find(name) != aliases.end()) {
			return *aliases[name];
		}
		if(objects.find(name) == objects.end()) {
			LoadFromFile<T>::load(objects[name], name);
		}
		return objects[name];
	}
	
	template<typename T>
	void FileBuffer<T>::set_object(const std::string& name, const std::string& file_path) {
		LoadFromFile<T>::load(objects[name], file_path);
	}
	
	template<typename T>
	void FileBuffer<T>::add_alias(const std::string& name, const std::string& alias) {
		aliases[alias] = &get(name);
	}
}