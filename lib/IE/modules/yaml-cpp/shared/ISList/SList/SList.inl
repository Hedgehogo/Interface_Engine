//included into with_list.hpp

namespace ie {
	template<typename T>
	SList<T>::SList(const std::vector<typename SList<T>::V>& list) : setters_(), list_() {
		list_.resize(list.size_());
		for(int i = 0; i < list.size_(); ++i) {
			this->list_[i] = std::make_shared<T>(list[i]);
		}
	}
	
	template<typename T>
	SList<T>::SList(std::vector <std::shared_ptr<T>> list) : list_(list), setters_() {
	}
	
	template<typename T>
	void SList<T>::set() {
		for(const auto& setter: setters_) {
			setter(get_value());
		}
	}
	
	template<typename T>
	PIShared SList<T>::get_element_ptr(size_t index) const {
		return std::dynamic_pointer_cast<IShared>(list_[index]);
	}
	
	template<typename T>
	void SList<T>::set_element_ptr(size_t index, PIShared value) {
		list_[index] = std::dynamic_pointer_cast<T>(value);
		set();
	}
	
	template<typename T>
	typename SList<T>::V SList<T>::get_element(size_t index) const {
		return list_[index]->get_value();
	}
	
	template<typename T>
	void SList<T>::set_element(size_t index, const typename SList<T>::V& value) {
		list_[index]->set_value(value);
		set();
	}
	
	template<typename T>
	std::vector<typename SList<T>::V> SList<T>::get_value() const {
		std::vector<typename SList<T>::V> result{list_.size_()};
		for(int i = 0; i < list_.size_(); ++i) {
			result[i] = get_element(i);
		}
		return result;
	}
	
	template<typename T>
	void SList<T>::set_value(const std::vector<typename SList<T>::V>& list) {
		list_.resize(list.size_());
		for(int i = 0; i < list.size_(); ++i) {
			list_[i] = std::make_shared<T>(list[i]);
		}
		set();
	}
	
	template<typename T>
	bool DecodePointer<SList<T> >::decode_pointer(const YAML::Node& node, SList<T>*& with_list) {
		if(node["list"]) {
			std::vector<typename SList<T>::V> list{node["list"].size_()};
			for(int i = 0; i < list.size(); ++i) {
				node["list"][i] >> list[i];
			}
			with_list = new SList <T>{list};
		} else {
			std::vector<std::shared_ptr<T> > list{node["vars"].size_()};
			for(int i = 0; i < list.size(); ++i) {
				list[i] = get_s_value<T>(node["vars"][i]);
			}
			with_list = new SList <T>{list};
		}
		return true;
	}
}