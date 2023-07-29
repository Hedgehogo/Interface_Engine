#include "boxWithSetableObject.hpp"

namespace ui {
	BoxWithSetableObject::BoxWithSetableObject(BoxPtr<IScalable>&& object, sf::Vector2f minSize) : Box(minSize), object(object) {
	}
	
	void BoxWithSetableObject::init(InitInfo initInfo) {
		drawManager.add(this->drawManager);
		updateManager.add(this->updateManager);
		
		this->panelManagerInterceptor.init(initInfo.panelManager);
		
		this->window = &initInfo.window;
		this->renderTarget = &initInfo.renderTarget;
		this->interactionStack = &initInfo.interactionStack;
	}
	
	void BoxWithSetableObject::setObject(BoxPtr<IScalable>&& newObject, bool deleteOld) {
		drawManager.clear();
		updateManager.clear();
		interactionManager.clear();
		panelManagerInterceptor.clear();
		InitInfo initInfo{*window, *renderTarget, drawManager, updateManager, interactionManager, *interactionStack, panelManagerInterceptor};
		newObject->init(initInfo);
		object = newObject;
	}
	
	void BoxWithSetableObject::draw() {
		this->drawManager.draw();
	}
	
	void BoxWithSetableObject::resize(sf::Vector2f size, sf::Vector2f position) {
		object->resize(size, position);
	}
	
	void BoxWithSetableObject::update() {
		this->updateManager.update();
	}
	
	IScalable& BoxWithSetableObject::getObject() {
		return *object;
	}
	
	const IScalable& BoxWithSetableObject::getObject() const {
		return *object;
	}
}