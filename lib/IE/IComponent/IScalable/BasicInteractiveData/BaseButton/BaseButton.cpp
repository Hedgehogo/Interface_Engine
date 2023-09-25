#include "BaseButton.hpp"

namespace ie {
	BaseButton::BaseButton(BoxPtr<IScalable::Make>&& background, InitInfo initInfo) :
		background(background->make(initInfo)) {
		initInfo.updateManager.add(*this);
	}
	
	BaseButton::BaseButton(BoxPtr<IScalable>&& background) :
		background(std::move(background)) {
	}
	
	void BaseButton::init(InitInfo initInfo) {
		initInfo.updateManager.add(*this);
		background->init(initInfo);
	}
	
	IScalable& BaseButton::getObject() {
		return *background;
	}
	
	const IScalable& BaseButton::getObject() const {
		return *background;
	}
	
	bool BaseButton::updateInteractions(sf::Vector2f mousePosition) {
		return background->updateInteractions(mousePosition);
	}
	
	LayoutData& BaseButton::layoutGetData() {
		return layout;
	}
	
	const LayoutData& BaseButton::layoutGetData() const {
		return layout;
	}
	
	void BaseButton::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}