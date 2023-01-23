#include "layerWithSetableObject.hpp"

namespace ui
{
	LayerWithSetableObject::LayerWithSetableObject(sf::Vector2f minSize, IScalable* object) : LayoutWithObject(object) {}

	void
	LayerWithSetableObject::init(InitInfo initInfo) {
		drawManager.add(this->drawManager);
		updateManager.add(this->updateManager);

		this->panelManagerInterceptor.init(initInfo.panelManager);

		this->renderTarget = &initInfo.renderTarget;
		this->interactionStack = &initInfo.interactionStack;
	}

	void LayerWithSetableObject::setObject(IScalable* newObject, bool deleteOld)
	{
		if (deleteOld) delete object;
		drawManager.clear();
		updateManager.clear();
		interactionManager.clear();
		panelManagerInterceptor.clear();
		InitInfo initInfo{*renderTarget, drawManager, updateManager, interactionManager, *interactionStack, panelManagerInterceptor};
		newObject->init(initInfo);
		object = newObject;
	}

	IScalable *LayerWithSetableObject::getObject()
	{
		return object;
	}

	void LayerWithSetableObject::draw()
	{
		this->drawManager.draw();
	}

	void LayerWithSetableObject::update()
	{
		this->updateManager.update();
	}
} // ui