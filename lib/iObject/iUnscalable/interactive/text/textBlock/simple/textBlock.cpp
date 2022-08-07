#include "textBlock.h"


ui::TextBlock::TextBlock(std::wstring text, sf::Color textColor, sf::Font *font, sf::Text::Style style,std::vector<BaseLine*> lines, int size, sf::Color textSelectionColor, sf::Color backgroundSelectionColor) :
    str(text), lines(lines){
    textVariables.TextColor = textColor;
    textVariables.font = font;
    textVariables.style = style;
    textVariables.size = size;
    textVariables.textSelectionColor = textSelectionColor;
    textVariables.backgroundSelectionColor = backgroundSelectionColor;
}

ui::TextBlock::TextBlock(std::wstring str, ui::TextVariables textVariables, std::vector<BaseLine*> lines) : str(str), BaseTextBlock(textVariables), lines(lines) {}

void ui::TextBlock::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
    for (BaseCharacter*& character : textCharacters) {
        character->init(renderTarget);
    }

    for (BaseLine*& line : lines) {
        line->init(textVariables.size, *textVariables.font, textVariables.TextColor, renderTarget);
    }
}

std::vector<ui::BaseCharacter*> ui::TextBlock::getCharacters() {
    for (wchar_t character : str) {
        textCharacters.push_back(new ui::Character(character, textVariables, lines));
    }
    return textCharacters;
}

void ui::TextBlock::update() {}

bool ui::TextBlock::updateInteractions(sf::Vector2f mousePosition) {
    return false;
}

bool ui::TextBlock::in(sf::Vector2f mousePosition) {
    bool result = true;
    for (BaseCharacter*& character : textCharacters) {
        bool buf = character->in(mousePosition);
        if (!buf)
            result = false;
    }
    return result;
}

ui::TextBlock *ui::TextBlock::copy() {
    std::vector<BaseLine*> copyLines{lines.size()};
    for (int i = 0; i < lines.size(); ++i) {
        copyLines[i] = lines[i];
    }
    return new TextBlock(str, textVariables, copyLines);
}

ui::TextBlock::~TextBlock() {
    for (BaseLine*& line : lines) {
        delete line;
    }
}