#include "layerWithSetableObject.hpp"

namespace ui
{
	LayerWithSetableObject::LayerWithSetableObject(sf::Vector2f minSize, IScalable* object) : LayoutWithObject(object) {}

	void LayerWithSetableObject::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
		drawManager.add(this->drawManager);
		updateManager.add(this->updateManager);

		this->panelManagerInterceptor.init(panelManager);

		this->renderTarget = &renderTarget;
		this->interactionStack = &interactionStack;
	}

	void LayerWithSetableObject::setObject(IScalable* newObject, bool deleteOld)
	{
		if (deleteOld) delete object;
		drawManager.clear();
		updateManager.clear();
		interactionManager.clear();
		panelManagerInterceptor.clear();
		newObject->init(*renderTarget, drawManager, updateManager, interactionManager, *interactionStack, panelManagerInterceptor);
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