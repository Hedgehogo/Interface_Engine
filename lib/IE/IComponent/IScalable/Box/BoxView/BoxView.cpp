#include "BoxView.hpp"

namespace ie {
	BoxWithView::BoxWithView(sf::Vector2f minSize, InitInfo initInfo) :
		Box(minSize), renderTarget(&initInfo.renderTarget) {
		initInfo.drawManager.add(*this);
	}
	
	BoxWithView::BoxWithView(sf::Vector2f minSize) : Box(minSize), renderTarget(nullptr) {
	}
	
	BoxWithView::BoxWithView(const BoxWithView& other) :
		Box(other), renderTarget(other.renderTarget), view(other.view) {
	}
	
	void BoxWithView::init(InitInfo initInfo) {
		this->renderTarget = &initInfo.renderTarget;
		initInfo.drawManager.add(*this);
	}
	
	void BoxWithView::draw() {
		sf::View oldView = renderTarget->getView();
		renderTarget->setView(view);
		drawManager.draw();
		renderTarget->setView(oldView);
	}
	
	void BoxWithView::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		
		view.setSize(size);
		view.setCenter(position + (size / 2.f));
		
		sf::Vector2f renderTargetSize{renderTarget->getSize()};
		view.setViewport(
			{
				position.x / renderTargetSize.x,
				position.y / renderTargetSize.y,
				size.x / renderTargetSize.x,
				size.y / renderTargetSize.y
			}
		);
	}
}