#include "baseResizer.h"

namespace ui {
    BaseResizer::BaseResizer(float lineSpacing, Align align) : lineSpacing(lineSpacing), align(align), characters(nullptr), lines(nullptr) {}

    void BaseResizer::init(std::vector<BaseCharacter *> &characters, std::vector<BaseLine *> &lines) {
        this->characters = &characters;
        this->lines = &lines;
    }
/*
    void BaseResizer::addLines(std::vector<BaseLine *> *lines, float startLine, sf::Vector2f endCharacterPos) {
        if (lines) {
            for (BaseLine *&line: *lines) {
                BaseLine *copyLine = line->copy();
                copyLine->resize(startLine, endCharacterPos.x, endCharacterPos.y);
                this->lines->push_back(copyLine);
            }
        }
    }


    void BaseResizer::lineResize() {
        for (BaseLine*& line : *lines) {
            delete line;
        }
        lines->clear();

        std::vector<BaseLine *> *oldLine = nullptr;
        float startLine = 0;
        float oldYPositionCharacter = 0;
        for (int i = 0; i < characters->size(); ++i){
            BaseCharacter* character = (*characters)[i];
            std::vector<BaseLine *> &characterLine = character->getLine();
            sf::Vector2f characterPos = character->getPosition();

            if (oldYPositionCharacter != characterPos.y) {
                if (i != 0)
                    addLines(oldLine, startLine, {(*characters)[i - 1]->getPosition().x, oldYPositionCharacter});

                oldLine = &characterLine;
                startLine = characterPos.x;
                oldYPositionCharacter = characterPos.y;
            } else if (oldLine != &characterLine) {
                addLines(oldLine, startLine, characterPos);

                oldLine = &characterLine;
                startLine = characterPos.x;
            }
        }
        if (characters->size() != 0){
            BaseCharacter* lastCharacter = (*characters)[characters->size() - 1];
            sf::Vector2f lastCharacterPosition = lastCharacter->getPosition();

            addLines(oldLine, startLine, {lastCharacterPosition.x + lastCharacter->getAdvance(), lastCharacterPosition.y});
        }
    }
*/
}