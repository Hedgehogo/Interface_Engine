#include "BoxSettable.hpp"

namespace ui {
	BoxSettable::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize) :
		object(std::move(object)), minSize(minSize) {
	}
	
	BoxSettable* BoxSettable::Make::make(InitInfo initInfo) {
		return new BoxSettable{std::move(*this), initInfo};
	}
	
	BoxSettable::BoxSettable(Make&& make, InitInfo initInfo) :
		BoxSettable(std::move(make.object), make.minSize, initInfo) {
	}
	
	BoxSettable::BoxSettable(BoxPtr<IScalable::Make>&& object, sf::Vector2f minSize, InitInfo initInfo) :
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
	
	BoxSettable::BoxSettable(BoxPtr<IScalable>&& object, sf::Vector2f minSize) : Box(minSize), object(std::move(object)) {
	}
	
	void BoxSettable::init(InitInfo initInfo) {
		drawManager.add(this->drawManager);
		updateManager.add(this->updateManager);
		
		this->panelManagerInterceptor.init(initInfo.panelManager);
		
		this->window = &initInfo.window;
		this->renderTarget = &initInfo.renderTarget;
		this->interactionStack = &initInfo.interactionStack;
	}
	
	void BoxSettable::setObject(BoxPtr<IScalable>&& newObject) {
		drawManager.clear();
		updateManager.clear();
		interactionManager.clear();
		panelManagerInterceptor.clear();
		InitInfo initInfo{*window, *renderTarget, drawManager, updateManager, interactionManager, *interactionStack, panelManagerInterceptor};
		newObject->init(initInfo);
		object = newObject;
	}
	
	void BoxSettable::setObject(BoxPtr<IScalable::Make>&& newObject) {
		drawManager.clear();
		updateManager.clear();
		interactionManager.clear();
		panelManagerInterceptor.clear();
		InitInfo initInfo{*window, *renderTarget, drawManager, updateManager, interactionManager, *interactionStack, panelManagerInterceptor};
		object = BoxPtr{newObject->make(initInfo)};
	}
	
	void BoxSettable::draw() {
		this->drawManager.draw();
	}
	
	void BoxSettable::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		object->resize(size, position);
	}
	
	void BoxSettable::update() {
		this->updateManager.update();
	}
	
	IScalable& BoxSettable::getObject() {
		return *object;
	}
	
	const IScalable& BoxSettable::getObject() const {
		return *object;
	}
	
	BoxSettable* BoxSettable::copy() {
		return new BoxSettable{*this};
	}
}