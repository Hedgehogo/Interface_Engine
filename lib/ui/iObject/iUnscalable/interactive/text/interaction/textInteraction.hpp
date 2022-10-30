#pragma once

#include "../../../../../interaction/iInteraction/iInteraction.hpp"

namespace ui {
    class Text;
    class TextInteraction : public virtual IInteraction{
    protected:
		TextInteraction() {
		}
	
		Text* text = nullptr;
    public:
        virtual void init(Text* text);
        virtual void setText(Text* text);
        virtual Text* getText();

        TextInteraction * copy() override = 0;

        ~TextInteraction() = default;
    };

}