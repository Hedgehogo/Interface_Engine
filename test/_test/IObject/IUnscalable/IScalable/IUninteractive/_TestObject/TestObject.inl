#include "TestObject.hpp"

template<typename T>
TestObject<T>::Make::Make(std::shared_ptr<T> object) : object(std::move(object)) {
}

template<typename T>
TestObject<T>* TestObject<T>::Make::make(ui::InitInfo initInfo) {
	return new TestObject{std::move(*this), initInfo};
}

template<typename T>
TestObject<T>::TestObject(Make&& make, ui::InitInfo initInfo) : object(make.object->make(initInfo)) {
}

template<typename T>
void TestObject<T>::init(ui::InitInfo initInfo) {
	object->init(initInfo);
}

template<typename T>
void TestObject<T>::resize(sf::Vector2f size, sf::Vector2f position) {
	object->resize(size, position);
}

template<typename T>
sf::Vector2f TestObject<T>::getMinSize() const {
	return object->getMinSize();
}

template<typename T>
sf::Vector2f TestObject<T>::getNormalSize() const {
	return object->getNormalSize();
}

template<typename T>
TestObject<T>* TestObject<T>::copy() {
	return new TestObject<T>{*this};
}
