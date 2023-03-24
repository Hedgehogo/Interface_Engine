#pragma once

#include "../../../../../interaction/iInteraction/iInteraction.hpp"

namespace ui {
    class Text;
    class TextInteraction : public virtual IInteraction{
    protected:
		TextInteraction();
	
		Text* text;
    public:
        virtual void init(Text *text, InteractionManager &interactionManager);
        virtual void setText(Text* text);
        virtual Text* getText();

        TextInteraction * copy() override = 0;

        ~TextInteraction() = default;
    };

}