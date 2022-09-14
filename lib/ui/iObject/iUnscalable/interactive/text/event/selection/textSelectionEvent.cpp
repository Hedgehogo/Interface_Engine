#include "textSelectionEvent.hpp"

#include "../../text.h"

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
            std::vector<BaseCharacter*>::iterator localStart;
            std::vector<BaseCharacter*>::iterator localEnd;
            if (std::distance(start, end) < 0){
                localStart = end;
                localEnd = start;
            } else{
                localStart = start;
                localEnd = end;
            }
            for (auto iterator = localStart; iterator != localEnd; ++iterator) {
                (*iterator)->setSelection(true);
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
            std::vector<BaseCharacter*>::iterator localStart;
            std::vector<BaseCharacter*>::iterator localEnd;
            if (std::distance(start, end) < 0){
                localStart = end;
                localEnd = start;
            } else{
                localStart = start;
                localEnd = end;
            }
            for (auto iterator = localStart; iterator != localEnd; ++iterator) {
                (*iterator)->setSelection(false);
            }
        }
        ButtonEvent_Simple::update(mousePosition, press);
    }

    TextSelectionEvent *TextSelectionEvent::copy() {
        return new TextSelectionEvent{};
    }
}