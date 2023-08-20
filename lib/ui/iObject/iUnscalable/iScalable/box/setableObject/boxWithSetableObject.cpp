#include "boxWithSetableObject.hpp"

namespace ui {
	BoxWithSetableObject::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize) :
		object(std::move(object)), minSize(minSize) {
	}
	
	BoxWithSetableObject* BoxWithSetableObject::Make::make(InitInfo initInfo) {
		return new BoxWithSetableObject{std::move(*this), initInfo};
	}
	
	BoxWithSetableObject::BoxWithSetableObject(Make&& make, InitInfo initInfo) :
		BoxWithSetableObject(std::move(make.object), make.minSize, initInfo) {
	}
	
	BoxWithSetableObject::BoxWithSetableObject(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize, InitInfo initInfo) :
		Box(minSize),
		window(&initInfo.window),
		renderTarget(&initInfo.renderTarget),
		interactionStack(&initInfo.interactionStack),
		panelManagerInterceptor(initInfo.panelManager),
		object(object->make(
			{
				initInfo.window,
				initInfo.renderTarget,
				drawManager,
				updateManager,
				interactionManager,
				initInfo.interactionStack,
				panelManagerInterceptor
			}
		)) {
		initInfo.drawManager.add(*this);
		initInfo.updateManager.add(*this);
	}
	
	BoxWithSetableObject::BoxWithSetableObject(BoxPtr<IScalable>&& object, sf::Vector2f minSize) : Box(minSize), object(std::move(object)) {
	}
	
	void BoxWithSetableObject::init(InitInfo initInfo) {
		drawManager.add(this->drawManager);
		updateManager.add(this->updateManager);
		
		this->panelManagerInterceptor.init(initInfo.panelManager);
		
		this->window = &initInfo.window;
		this->renderTarget = &initInfo.renderTarget;
		this->interactionStack = &initInfo.interactionStack;
	}
	
	void BoxWithSetableObject::setObject(BoxPtr<IScalable>&& newObject) {
		drawManager.clear();
		updateManager.clear();
		interactionManager.clear();
		panelManagerInterceptor.clear();
		InitInfo initInfo{*window, *renderTarget, drawManager, updateManager, interactionManager, *interactionStack, panelManagerInterceptor};
		newObject->init(initInfo);
		object = newObject;
	}
	
	void BoxWithSetableObject::setObject(BoxPtr<IScalable::Make>&& newObject) {
		drawManager.clear();
		updateManager.clear();
		interactionManager.clear();
		panelManagerInterceptor.clear();
		InitInfo initInfo{*window, *renderTarget, drawManager, updateManager, interactionManager, *interactionStack, panelManagerInterceptor};
		object = BoxPtr{newObject->make(initInfo)};
	}
	
	void BoxWithSetableObject::draw() {
		this->drawManager.draw();
	}
	
	void BoxWithSetableObject::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
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
	
	BoxWithSetableObject* BoxWithSetableObject::copy() {
		return new BoxWithSetableObject{*this};
	}
}