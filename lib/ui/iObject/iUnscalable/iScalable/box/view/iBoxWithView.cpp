#include "iBoxWithView.hpp"

namespace ui {
	IBoxWithView::IBoxWithView(sf::Vector2f minSize) : Box(minSize), renderTarget(nullptr) {
	}
	
	void IBoxWithView::init(InitInfo initInfo) {
		this->renderTarget = &initInfo.renderTarget;
		initInfo.drawManager.add(*this);
	}
	
	void IBoxWithView::draw() {
		sf::View oldView = renderTarget->getView();
		renderTarget->setView(view);
		drawManager.draw();
		renderTarget->setView(oldView);
	}
	
	void IBoxWithView::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		
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
	
	void IBoxWithView::copy(IBoxWithView* iBoxWithView) {
		iBoxWithView->renderTarget = renderTarget;
		iBoxWithView->drawManager = drawManager;
		iBoxWithView->view = view;
	}
}