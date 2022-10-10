//included into withList.hpp

namespace ui {
	template <typename T>
	SList<T>::SList(const std::vector<typename SList<T>::V> &list) {
		this->list.resize(list.size());
		for(int i = 0; i < list.size(); ++i) {
			this->list[i] = std::make_shared<T>(list[i]);
		}
	}
	
	template <typename T>
	SList<T>::SList(std::vector<std::shared_ptr<T>> list) : list(list) {}
	
	template <typename T>
	PIShared SList<T>::getElementPtr(std::size_t index) const {
		return std::dynamic_pointer_cast<IShared>(list[index]);
	}
	
	template <typename T>
	void SList<T>::setElementPtr(std::size_t index, PIShared value) {
		list[index] = std::dynamic_pointer_cast<T>(value);
	}
	
	template <typename T>
	typename SList<T>::V SList<T>::getElement(std::size_t index) const {
		return list[index]->getValue();
	}
	
	template <typename T>
	void SList<T>::setElement(std::size_t index, const typename SList<T>::V &value) {
		list[index]->setValue(value);
	}
	
	template <typename T>
	std::vector<typename SList<T>::V> SList<T>::getValue() const {
		std::vector<typename SList<T>::V> result{list.size()};
		for(int i = 0; i < list.size(); ++i) {
			this->result[i] = getElement(i);
		}
		return result;
	}
	
	template <typename T>
	void SList<T>::setValue(const std::vector<typename SList<T>::V> &list) {
		this->list.resize(list.size());
		for(int i = 0; i < list.size(); ++i) {
			this->list[i] = std::make_shared<T>(list[i]);
		}
	}
}