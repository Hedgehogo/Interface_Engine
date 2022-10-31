#include "keyEvent_LambdaSimple.hpp"

namespace ui {
    KeyEvent_LambdaSimple::KeyEvent_LambdaSimple(void (*startPressedLambda)(sf::Vector2i), void (*whilePressedLambda)(sf::Vector2i),
												 void (*stopPressedLambda)(sf::Vector2i), void (*whileNotPressedLambda)(sf::Vector2i)) :
		KeyEvent_Simple(), startPressedLambda(startPressedLambda), whilePressedLambda(whilePressedLambda), stopPressedLambda(stopPressedLambda), whileNotPressedLambda(whileNotPressedLambda) {}

    void KeyEvent_LambdaSimple::startPressed() {
        startPressedLambda(mousePosition);
    }

    void KeyEvent_LambdaSimple::stopPressed() {
        stopPressedLambda(mousePosition);
    }

    void KeyEvent_LambdaSimple::whilePressed() {
        whilePressedLambda(mousePosition);
    }

    void KeyEvent_LambdaSimple::whileNotPressed() {
        whileNotPressedLambda(mousePosition);
    }

    KeyEvent_LambdaSimple *KeyEvent_LambdaSimple::copy() {
        KeyEvent_LambdaSimple* keyEventLambdaSimple{new KeyEvent_LambdaSimple{startPressedLambda, whilePressedLambda, stopPressedLambda, whileNotPressedLambda}};
        KeyEvent::copy(keyEventLambdaSimple);
        return keyEventLambdaSimple;
    }

}

