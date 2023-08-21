#include "OnlyDrawable.hpp"

namespace ui {
	OnlyDrawable::OnlyDrawable() : renderTarget(nullptr) {
	}
	
	void OnlyDrawable::init(InitInfo initInfo) {
		initInfo.drawManager.add(*this);
		this->renderTarget = &initInfo.renderTarget;
	}
	
	OnlyDrawable::OnlyDrawable(InitInfo initInfo) : renderTarget(&initInfo.renderTarget) {
		initInfo.drawManager.add(*this);
	}
	
	sf::RenderTarget& OnlyDrawable::getRenderTarget() {
		return *renderTarget;
	}
}