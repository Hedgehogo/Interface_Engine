#pragma once

#include "../iScalable/iScalable.hpp"
#include "../../../interaction/interactionStack/interactionStack.hpp"
#include "initInfo/interactiveInitInfo.hpp"

namespace ui {
	class Interactive : public virtual IUnscalable {
	public:
		void init(InitInfo initInfo) override;
		
		explicit Interactive();
	
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
	};
}
