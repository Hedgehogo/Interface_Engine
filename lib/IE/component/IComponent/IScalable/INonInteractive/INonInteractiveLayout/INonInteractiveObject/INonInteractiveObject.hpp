#pragma once

#include "../INonInteractiveLayout.hpp"
#include "../../../IScalableLayout/IScalableObject/IScalableObject.hpp"

namespace ie {
	class INonInteractiveObject : public virtual INonInteractiveLayout, public virtual IScalableObject {
	public:
		struct Make : public virtual INonInteractiveLayout::Make, public virtual IScalableObject::Make {
			auto make(InitInfo init_info) -> INonInteractiveObject* override = 0;
		};
		
		auto handle_event(Event event) -> bool override;
	};
}
