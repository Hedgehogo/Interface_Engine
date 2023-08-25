#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicKeyEvent.hpp"
#include "../TextInteractionInitInfo/TextInteractionInitInfo.hpp"

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