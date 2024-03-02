//included into FileBuffer.hpp

namespace ie {
	template<typename T>
	auto LoadFromFile<T>::load(T& object, std::string name) -> void {
		object.loadFromFile(name);
	}
	
	template<typename T>
	absl::flat_hash_map<std::string, T> FileBuffer<T>::objects_ = {};
	
	template<typename T>
	absl::flat_hash_map<std::string, T*> FileBuffer<T>::aliases_ = {};
	
	template<typename T>
	auto FileBuffer<T>::get(const std::string& name) -> T& {
		if(aliases_.find(name) != aliases_.end()) {
			return *aliases_[name];
		}
		if(objects_.find(name) == objects_.end()) {
			LoadFromFile<T>::load(objects_[name], name);
		}
		return objects_[name];
	}
	
	template<typename T>
	auto FileBuffer<T>::set_object(std::string const& name, std::string const& file_path) -> void {
		LoadFromFile<T>::load(objects_[name], file_path);
	}
	
	template<typename T>
	auto FileBuffer<T>::add_alias(std::string const& name, std::string const& alias) -> void {
		aliases_[alias] = &get(name);
	}
}