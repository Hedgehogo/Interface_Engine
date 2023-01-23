#include "iLayerWithView.hpp"

namespace ui {
	ILayerWithView::ILayerWithView(sf::Vector2f minSize) : Layer(minSize) {}

	void ILayerWithView::init(InitInfo initInfo) {
		this->renderTarget = &initInfo.renderTarget;
		initInfo.drawManager.add(*this);
	}

	void ILayerWithView::draw() {
		sf::View oldView = renderTarget->getView();
		renderTarget->setView(view);
		drawManager.draw();
		renderTarget->setView(oldView);
	}

	void ILayerWithView::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);

		view.setSize(size);
		view.setCenter(position + (size / 2.f));

		sf::Vector2f renderTargetSize{renderTarget->getSize()};
		view.setViewport({
			position.x / renderTargetSize.x,
			position.y / renderTargetSize.y,
			size.x / renderTargetSize.x,
			size.y / renderTargetSize.y
		});
	}

	ILayerWithView *ILayerWithView::copy() {
		return nullptr;
	}
} // ui