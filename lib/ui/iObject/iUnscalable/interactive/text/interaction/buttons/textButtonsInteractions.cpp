#include "textButtonsInteractions.hpp"
#include "../../text.h"
namespace ui {
    TextButtonsInteractions::TextButtonsInteractions(ButtonEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys) : ButtonsInteraction(event, keys, blackListKeys) {}

    void TextButtonsInteractions::init(ui::Text *text) {
        TextInteraction::init(text);
        dynamic_cast<TextEvent *>(event)->init(text);
    }

    TextButtonsInteractions *TextButtonsInteractions::copy() {
        return new TextButtonsInteractions{event, keys, blackListKeys};
    }
} // ui