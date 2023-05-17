#include "boxWithSetableObject.hpp"

namespace ui {
	BoxWithSetableObject::BoxWithSetableObject(sf::Vector2f minSize, IScalable* object) : LayoutWithObject(object) {
	}
	
	void BoxWithSetableObject::init(InitInfo initInfo) {
		drawManager.add(this->drawManager);
		updateManager.add(this->updateManager);
		
		this->panelManagerInterceptor.init(initInfo.panelManager);
		
		this->window = &initInfo.window;
		this->renderTarget = &initInfo.renderTarget;
		this->interactionStack = &initInfo.interactionStack;
	}
	
	void BoxWithSetableObject::setObject(IScalable* newObject, bool deleteOld) {
		if(deleteOld)
			delete object;
		drawManager.clear();
		updateManager.clear();
		interactionManager.clear();
		panelManagerInterceptor.clear();
		InitInfo initInfo{*window, *renderTarget, drawManager, updateManager, interactionManager, *interactionStack, panelManagerInterceptor};
		newObject->init(initInfo);
		object = newObject;
	}
	
	IScalable* BoxWithSetableObject::getObject() {
		return object;
	}
	
	void BoxWithSetableObject::draw() {
		this->drawManager.draw();
	}
	
	void BoxWithSetableObject::update() {
		this->updateManager.update();
	}
}