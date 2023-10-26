//included into file_buffer.hpp

namespace ie {
	template<typename T>
	void LoadFromFile<T>::load(T& object, std::string name) {
		object.loadFromFile(name);
	}
	
	template<typename T>
	std::map<std::string, T> FileBuffer<T>::objects_ = {};
	
	template<typename T>
	std::map<std::string, T*> FileBuffer<T>::aliases_ = {};
	
	template<typename T>
	T& FileBuffer<T>::get(const std::string& name) {
		if(aliases_.find(name) != aliases_.end()) {
			return *aliases_[name];
		}
		if(objects_.find(name) == objects_.end()) {
			LoadFromFile<T>::load(objects_[name], name);
		}
		return objects_[name];
	}
	
	template<typename T>
	void FileBuffer<T>::set_object(const std::string& name, const std::string& file_path) {
		LoadFromFile<T>::load(objects_[name], file_path);
	}
	
	template<typename T>
	void FileBuffer<T>::add_alias(const std::string& name, const std::string& alias) {
		aliases_[alias] = &get(name);
	}
}