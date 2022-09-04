#include "textBlock.h"

#include "../../line/underline/underline.h"
#include "../../line/strikeThrough/strikeThrough.h"
#include "../../../../../../../yaml/yamlWithSfml/fileBuffer/fileBuffer.hpp"

std::vector<ui::BaseLine* > generateLines(std::vector<ui::BaseLine* > lines, sf::Text::Style style){
    if (style & sf::Text::Underlined)
        lines.push_back(new ui::Underline);
    if (style & sf::Text::StrikeThrough)
        lines.push_back(new ui::StrikeThrough);
    return lines;
}

ui::TextBlock::TextBlock(std::u32string text, sf::Color textColor, sf::Font *font, sf::Text::Style style, std::vector<BaseLine *> lines, int size, sf::Color textSelectionColor, sf::Color backgroundSelectionColor,
                         sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor) :
    str(text), lines(generateLines(lines, style)){

    textVariables.TextColor = textColor;
    textVariables.font = font;
    textVariables.style = style;
    textVariables.size = size;
    textVariables.textSelectionColor = textSelectionColor;
    textVariables.backgroundSelectionColor = backgroundSelectionColor;
    textVariables.inactiveTextSelectionColor = inactiveTextSelectionColor;
    textVariables.inactiveBackgroundSelectionColor = inactiveBackgroundSelectionColor;
}

ui::TextBlock::TextBlock(std::u32string  str, ui::TextVariables textVariables, std::vector<BaseLine*> lines) : str(str), BaseTextBlock(textVariables), lines(lines) {}

void ui::TextBlock::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
    for (BaseCharacter*& character : textCharacters) {
        character->init(renderTarget);
    }

    for (BaseLine*& line : lines) {
        line->init(textVariables.size, *textVariables.font, textVariables.TextColor, renderTarget);
    }
}

std::vector<ui::BaseCharacter*> ui::TextBlock::getCharacters() {
    for (char32_t character : str) {
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

ui::TextBlock *ui::TextBlock::createFromYaml(const YAML::Node &node) {
    std::u32string  text;
    sf::Color textColor = nullColor;
    sf::Font *font = nullptr;
    sf::Text::Style style = {};
    std::vector<BaseLine*> lines = {};
    int size = 0;
    sf::Color textSelectionColor = nullColor;
    sf::Color backgroundSelectionColor = nullColor;
    sf::Color inactiveTextSelectionColor = nullColor;
    sf::Color inactiveBackgroundSelectionColor = nullColor;

    node["text"] >> text;
    if (node["text-color"]) node["text-color"] >> textColor;
    if (node["text-color"]) node["text-color"] >> textColor;
    if (node["font"]) node["font"] >> font;
    if (node["style"]) node["style"] >> style;
    if (node["size"]) node["size"] >> size;
    if (node["text-selection-color"]) node["text-selection-color"] >> textSelectionColor;
    if (node["background-selection-color"]) node["background-selection-color"] >> backgroundSelectionColor;
    if (node["inactive-text-selection-color"]) node["inactive-text-selection-color"] >> inactiveTextSelectionColor;
    if (node["inactive-background-selection-color"]) node["inactive-background-selection-color"] >> inactiveBackgroundSelectionColor;

    if (node["line"]){
        BaseLine* line;
        node["line"] >> line;
        lines.push_back(line);
    }
    else if (node["lines"]){
        for (const YAML::Node& nodeLine : node["lines"]) {
            BaseLine* line;
            nodeLine >> line;
            lines.push_back(line);
        }
    }

    return new TextBlock{text, textColor, font, style, lines, size, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor};
}
