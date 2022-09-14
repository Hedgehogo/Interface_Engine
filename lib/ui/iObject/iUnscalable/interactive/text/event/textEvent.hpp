#pragma once

#include "../../../../../interaction/event/button/buttonEvent.hpp"

namespace ui {
    class Text;

    class TextEvent : public virtual ButtonEvent{
    protected:
        Text* text = nullptr;
    public:
        virtual void init(Text *text);

        virtual void setText(Text *text);

        virtual Text *getText() const;
    };

} // ui