#pragma once

#include "ui/interaction/iInteraction/iInteraction.hpp"
#include "../initInfo/textInteractionInitInfo.hpp"

namespace ui {
	class Text;
	
	class TextInteraction : public virtual IInteraction {
	protected:
		TextInteraction();
		
		Text* text;
		
		void copy(TextInteraction* textInteraction);
		
	public:
		virtual void init(TextInteractionInitInfo textInteractionInitInfo);
		
		virtual void setText(Text* text);
		
		virtual Text* getText();
		
		TextInteraction* copy() override = 0;
		
		~TextInteraction() = default;
	};
	
}