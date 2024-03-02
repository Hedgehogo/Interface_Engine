#include "TestObject.hpp"

template<typename T>
TestObject<T>::Make::Make(std::shared_ptr<T> object) : object(std::move(object)) {
}

template<typename T>
TestObject<T>* TestObject<T>::Make::make(ie::InitInfo init_info) {
	return new TestObject{std::move(*this), init_info};
}

template<typename T>
TestObject<T>::TestObject(Make&& make, ie::InitInfo init_info) : object(make.object->make(init_info)) {
}

template<typename T>
void TestObject<T>::init(ie::InitInfo init_info) {
	object->init(init_info);
}

template<typename T>
void TestObject<T>::resize(sf::Vector2f size, sf::Vector2f position) {
	object->resize(size, position);
}

template<typename T>
sf::Vector2f TestObject<T>::get_min_size() const {
	return object->get_min_size();
}

template<typename T>
sf::Vector2f TestObject<T>::get_normal_size() const {
	return object->get_normal_size();
}

template<typename T>
TestObject<T>* TestObject<T>::copy() {
	return new TestObject<T>{*this};
}
