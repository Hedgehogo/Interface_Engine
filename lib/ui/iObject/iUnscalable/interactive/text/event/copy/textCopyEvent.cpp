#include <codecvt>
#include "textCopyEvent.hpp"
#include "../../text.h"
#include "../../../../../../../yaml/yamlWithSfml/fileBuffer/fileBuffer.hpp"

namespace ui {

    void TextCopyEvent::startPressed() {
        sf::Clipboard::setString(u32stringToUint32String(text->getSelectionText()));
    }

    void TextCopyEvent::stopPressed() {}

    void TextCopyEvent::whilePressed() {}

    void TextCopyEvent::whileNotPressed() {}

    TextCopyEvent *TextCopyEvent::copy() {
        return new TextCopyEvent{};
    }
} // ui