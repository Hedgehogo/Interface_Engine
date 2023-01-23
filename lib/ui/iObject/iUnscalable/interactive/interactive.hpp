#pragma once

#include "../iScalable/iScalable.hpp"
#include "../../../interaction/interactionStack/interactionStack.hpp"
#include "initInfo/interactiveInitInfo.hpp"

namespace ui {
	class Interactive : public virtual IUnscalable {
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		
		void copy(Interactive* interactive);
		
	public:
		void init(InitInfo initInfo) override;
		
		virtual void init(InteractiveInitInfo interactiveInitInfo) = 0;
		
		explicit Interactive();
	};
}
