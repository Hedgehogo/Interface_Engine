#pragma once

#include "IE/Interaction/IEvent/KeyEvent/KeyEvent.hpp"
#include "../initInfo/textInteractionInitInfo.hpp"

namespace ui {
	class Text;
	
	class TextEvent : public virtual KeyEvent {
	public:
		virtual void init(TextInteractionInitInfo textInteractionInitInfo);
		
		virtual void setText(Text* text);
		
		virtual Text* getText() const;
	
	protected:
		Text* text = nullptr;
	};
}