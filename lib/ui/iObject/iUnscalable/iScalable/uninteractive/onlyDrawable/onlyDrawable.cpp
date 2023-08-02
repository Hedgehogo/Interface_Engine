#include "onlyDrawable.hpp"

namespace ui {
	OnlyDrawable::OnlyDrawable() : renderTarget(nullptr) {
	}
	
	void OnlyDrawable::init(InitInfo initInfo) {
		initInfo.drawManager.add(*this);
		this->renderTarget = &initInfo.renderTarget;
	}
}