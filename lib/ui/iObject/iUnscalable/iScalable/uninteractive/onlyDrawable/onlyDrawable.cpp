#include "onlyDrawable.hpp"

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
}