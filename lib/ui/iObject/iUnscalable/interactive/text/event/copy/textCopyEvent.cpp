#include <codecvt>
#include "textCopyEvent.hpp"
#include "../../text.h"
#include "../../../../../../../modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

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

    bool convertPointer(const YAML::Node &node, TextCopyEvent *&textCopyEvent) {
        return new TextCopyEvent;
    }
} // ui