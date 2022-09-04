#include "textEvent.hpp"

#include "../text.h"

#include <cmath>

namespace ui {
    std::vector<ui::BaseCharacter *>::iterator nullBaseCharacterIterator{nullptr};

    TextEvent::TextEvent(Text &text) : text(&text), start(nullptr), end(nullptr) {}

    void TextEvent::startPressed(sf::Vector2i mousePosition) {
        start = text->getCharacter(sf::Vector2f(mousePosition));
    }

    void TextEvent::stopPressed(sf::Vector2i mousePosition) {

    }

    void TextEvent::whilePressed(sf::Vector2i mousePosition) {
        end = text->getCharacter(sf::Vector2f(mousePosition));

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

    void TextEvent::whileNotPressed(sf::Vector2i mousePosition) {

    }

    std::vector<BaseCharacter *>::iterator TextEvent::getStart() {
        return start;
    }

    std::vector<BaseCharacter *>::iterator TextEvent::getEnd() {
        return end;
    }

    std::u32string TextEvent::getSelectionText() {
        if (start != nullBaseCharacterIterator && end != nullBaseCharacterIterator){
            std::u32string SelectionText{};
            std::vector<BaseCharacter*>::iterator localStart;
            std::vector<BaseCharacter*>::iterator localEnd;
            if (std::distance(start, end) < 0){
                localStart = end;
                localEnd = start;
            } else{
                localStart = start;
                localEnd = end;
            }
            SelectionText.resize(std::distance(localStart, localEnd));

            for (int i = 0; i < SelectionText.length(); ++i) {
                SelectionText[i] = (*(localStart + i))->getChar();
            }

            return SelectionText;
        }
        return std::u32string{U""};
    }

    void TextEvent::setText(Text &text) {
        this->text = &text;
    }

    void TextEvent::update(sf::Vector2i mousePosition, bool press) {
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

    TextEvent *TextEvent::copy() {
        return nullptr;
    }
}