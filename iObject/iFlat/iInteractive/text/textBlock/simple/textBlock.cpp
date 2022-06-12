#include "textBlock.h"
#include "../../indivisible/simple/indivisible.h"

ui::TextBlock::TextBlock(std::wstring text, sf::Color color, sf::Font &font, sf::Text::Style style, int size)
        : BaseTextBlock(text, color, style, font, size) {

}
ui::TextBlock::TextBlock(std::wstring text, sf::Color color, sf::Text::Style style, int size) :
        BaseTextBlock(text, color, style, size) {}

std::vector<ui::BaseIndivisible*> ui::TextBlock::divide() {
    std::vector<ui::BaseIndivisible*> result;

    sf::Text spase = text;
    spase.setString(L" ");

    sf::Text enter = text;
    enter.setString("\n");

    sf::Text divideText = text;
    divideText.setString(L"");
    std::wstring divideStr = L"";
    for (wchar_t ch : text.getString()) {
        if (ch == L' ' || ch == L'\n'){
            if (divideStr != L""){
                divideText.setString(divideStr);
                result.push_back(new ui::Indivisible(divideText, this));
                divideStr = L"";
            }

            result.push_back(new ui::Indivisible(ch == ' ' ? spase : enter, this));
        } else{
            divideStr.push_back(ch);
        }
    }
    if (divideStr != L""){
        divideText.setString(divideStr);
        result.push_back(new ui::Indivisible(divideText, this));
    }
    return result;
}

void ui::TextBlock::update() {

}
bool ui::TextBlock::updateInteractions(sf::Vector2f mousePosition) {
    return false;
}

