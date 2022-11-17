#include "textSelectionEvent.hpp"

#include "../../text.hpp"

#include <cmath>

namespace ui {
    TextSelectionEvent::TextSelectionEvent() : start(nullptr), end(nullptr) {}

    void TextSelectionEvent::startPressed() {
        text->setSelectionStart(start = text->getCharacter(sf::Vector2f(mousePosition)));
    }

    void TextSelectionEvent::stopPressed() {}

    void TextSelectionEvent::whilePressed() {
        text->setSelectionEnd(end = text->getCharacter(sf::Vector2f(mousePosition)));


        if (start != nullBaseCharacterIterator && end != nullBaseCharacterIterator){
            auto localStart = start,  localEnd = end;

            if (start > end) std::swap(localStart, localEnd);

            for (auto iterator = localStart; iterator != localEnd; ++iterator) {
                (*iterator)->setSelection(true);
	            (*iterator)->setActive(true);
            }
        }
    }

    void TextSelectionEvent::whileNotPressed() {}

    std::vector<BaseCharacter *>::iterator TextSelectionEvent::getStart() {
        return start;
    }

    std::vector<BaseCharacter *>::iterator TextSelectionEvent::getEnd() {
        return end;
    }

    void TextSelectionEvent::update(sf::Vector2i mousePosition, bool press) {
        if (press && start != nullBaseCharacterIterator && end != nullBaseCharacterIterator){
	        auto localStart = start,  localEnd = end;

	        if (start > end) std::swap(localStart, localEnd);

            for (auto iterator = localStart; iterator != localEnd; ++iterator) {
                (*iterator)->setSelection(false);
            }
        }
        KeyEvent_Simple::update(mousePosition, press);
    }

    TextSelectionEvent *TextSelectionEvent::copy() {
        return new TextSelectionEvent{};
    }

    bool convertPointer(const YAML::Node &node, TextSelectionEvent *&textSelectionEvent) {
        { textSelectionEvent = new TextSelectionEvent{}; return true; }
    }
}