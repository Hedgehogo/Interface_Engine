#pragma once
#include <vector>
#include "../iInteraction/iInteraction.hpp"

namespace ui {
	class InteractionStack {
	protected:
		std::vector<IInteraction *> interactionStack;
		
	public:
		explicit InteractionStack(std::vector<IInteraction *> &&interactionStack = {});
		
		virtual ~InteractionStack();
		
		IInteraction *at(unsigned index);
		
		void add(IInteraction *element);
	};
}
