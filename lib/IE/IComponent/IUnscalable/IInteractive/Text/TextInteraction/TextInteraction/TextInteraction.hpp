#pragma once

#include "IE/Interaction/IInteraction/IInteraction.hpp"
#include "../TextInteractionInitInfo/TextInteractionInitInfo.hpp"

namespace ui {
	class Text;
	
	class TextInteraction : public virtual IInteraction {
	protected:
		void copy(TextInteraction* textInteraction);
		
	public:
		TextInteraction();
		
		virtual void init(TextInteractionInitInfo textInteractionInitInfo);
		
		virtual void setText(Text* text);
		
		virtual Text* getText();
		
		TextInteraction* copy() override = 0;
		
		~TextInteraction() = default;
	
	protected:
		Text* text;
	};
}