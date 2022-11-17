#include "textInteraction.hpp"

namespace ui {
	TextInteraction::TextInteraction() : text(nullptr){}

    void TextInteraction::init(Text *text, InteractionManager &interactionManager) {
        this->text = text;
    }

    Text *TextInteraction::getText() {
        return text;
    }

    void TextInteraction::setText(Text *text) {
        this->text = text;
    }
} // ui