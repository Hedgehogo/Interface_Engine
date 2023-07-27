#include "onlyDrawable.hpp"

namespace ui {
	void OnlyDrawable::init(InitInfo initInfo) {
		initInfo.drawManager.add(*this);
		this->renderTarget = &initInfo.renderTarget;
	}
	
	OnlyDrawable::OnlyDrawable() : renderTarget(nullptr) {
	}
	
	void OnlyDrawable::copy(OnlyDrawable* onlyDrawable) {
		onlyDrawable->renderTarget = this->renderTarget;
	}
}