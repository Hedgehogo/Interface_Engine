#include "buttonEvent_LambdaSimple.hpp"

namespace ui {
    ButtonEvent_LambdaSimple::ButtonEvent_LambdaSimple(void (*startPressedLambda)(sf::Vector2i), void (*whilePressedLambda)(sf::Vector2i),
                                                       void (*stopPressedLambda)(sf::Vector2i), void (*whileNotPressedLambda)(sf::Vector2i)) :
        ButtonEvent_Simple(), startPressedLambda(startPressedLambda), whilePressedLambda(whilePressedLambda), stopPressedLambda(stopPressedLambda), whileNotPressedLambda(whileNotPressedLambda) {}

    void ButtonEvent_LambdaSimple::startPressed() {
        startPressedLambda(mousePosition);
    }

    void ButtonEvent_LambdaSimple::stopPressed() {
        stopPressedLambda(mousePosition);
    }

    void ButtonEvent_LambdaSimple::whilePressed() {
        whilePressedLambda(mousePosition);
    }

    void ButtonEvent_LambdaSimple::whileNotPressed() {
        whileNotPressedLambda(mousePosition);
    }

    ButtonEvent_LambdaSimple *ButtonEvent_LambdaSimple::copy() {
        ButtonEvent_LambdaSimple* buttonEventLambdaSimple{new ButtonEvent_LambdaSimple{startPressedLambda, whilePressedLambda, stopPressedLambda, whileNotPressedLambda}};
        ButtonEvent::copy(buttonEventLambdaSimple);
        return buttonEventLambdaSimple;
    }

}

