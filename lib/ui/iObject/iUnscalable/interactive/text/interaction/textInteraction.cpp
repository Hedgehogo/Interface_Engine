#include "textInteraction.hpp"

namespace ui {
    void TextInteraction::init(Text *text) {
        this->text = text;
    }

    Text *TextInteraction::getText() {
        return text;
    }

    void TextInteraction::setText(Text *text) {
        this->text = text;
    }
} // ui