#pragma once

#include "ui/interaction/event/key/keyEvent.hpp"
#include "../initInfo/textInteractionInitInfo.hpp"

namespace ui {
	class Text;
	
	class TextEvent : public virtual KeyEvent {
	protected:
		void copy(TextEvent* textEvent);
		
	public:
		virtual void init(TextInteractionInitInfo textInteractionInitInfo);
		
		virtual void setText(Text* text);
		
		virtual Text* getText() const;
	
	protected:
		Text* text = nullptr;
	};
}