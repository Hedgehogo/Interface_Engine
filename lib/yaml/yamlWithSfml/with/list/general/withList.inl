//included into withList.hpp

namespace ui {
	template <typename T>
	WithList<T>::WithList(const std::vector<typename WithList<T>::V> &list) {
		this->list.resize(list.size());
		for(int i = 0; i < list.size(); ++i) {
			this->list[i] = std::make_shared<T>(list[i]);
		}
	}
	
	template <typename T>
	WithList<T>::WithList(std::vector<std::shared_ptr<T>> list) : list(list) {}
	
	template <typename T>
	std::shared_ptr<IWith> WithList<T>::getElementPtr(std::size_t index) const {
		return std::dynamic_pointer_cast<IWith>(list[index]);
	}
	
	template <typename T>
	void WithList<T>::setElementPtr(std::size_t index, std::shared_ptr<IWith> value) {
		list[index] = std::dynamic_pointer_cast<T>(value);
	}
	
	template <typename T>
	typename WithList<T>::V WithList<T>::getElement(std::size_t index) const {
		return list[index]->getValue();
	}
	
	template <typename T>
	void WithList<T>::setElement(std::size_t index, const typename WithList<T>::V &value) {
		list[index]->setValue(value);
	}
	
	template <typename T>
	std::vector<typename WithList<T>::V> WithList<T>::getValue() const {
		std::vector<typename WithList<T>::V> result{list.size()};
		for(int i = 0; i < list.size(); ++i) {
			this->result[i] = getElement(i);
		}
		return result;
	}
	
	template <typename T>
	void WithList<T>::setValue(const std::vector<typename WithList<T>::V> &list) {
		this->list.resize(list.size());
		for(int i = 0; i < list.size(); ++i) {
			this->list[i] = std::make_shared<T>(list[i]);
		}
	}
}