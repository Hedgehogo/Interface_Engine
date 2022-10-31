#pragma once

#include "../../../../../interaction/event/key/keyEvent.hpp"

namespace ui {
    class Text;

    class TextEvent : public virtual KeyEvent{
    protected:
        Text* text = nullptr;
    public:
        virtual void init(Text *text);

        virtual void setText(Text *text);

        virtual Text *getText() const;
    };
}