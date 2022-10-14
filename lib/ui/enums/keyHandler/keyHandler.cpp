#include "keyHandler.hpp"

#include "../../sfmlEvents/mouseWheel/mouseWheel.hpp"

namespace ui {
    std::vector<KeyHandler::Key> KeyHandler::keysPressed{};

    std::vector<KeyHandler::Key> KeyHandler::getKeysPressed() {
        return keysPressed;
    }

    void KeyHandler::setKeysPressed(std::vector<Key> keysPressed) {
        KeyHandler::keysPressed = keysPressed;
    }

    void KeyHandler::addKey(KeyHandler::Key key) {

        if (std::find(keysPressed.begin(), keysPressed.end(), key) == keysPressed.end()){
            keysPressed.push_back(key);
        }
    }

    void KeyHandler::deleteKey(KeyHandler::Key key) {
        auto element = std::find(keysPressed.begin(), keysPressed.end(), key);
        if (element != keysPressed.end()){
            keysPressed.erase(element);
        }
    }

    void KeyHandler::clear() {
        keysPressed.clear();
    }

    std::string KeyHandler::toString(KeyHandler::Key key){
        if (key == KeyHandler::Key::a) return "a";
        else if (key == Key::b) return "b";
        else if (key == Key::c) return "c";
        else if (key == Key::d) return "d";
        else if (key == Key::e) return "e";
        else if (key == Key::f) return "f";
        else if (key == Key::g) return "g";
        else if (key == Key::h) return "h";
        else if (key == Key::i) return "i";
        else if (key == Key::j) return "j";
        else if (key == Key::k) return "k";
        else if (key == Key::l) return "l";
        else if (key == Key::m) return "m";
        else if (key == Key::n) return "n";
        else if (key == Key::o) return "o";
        else if (key == Key::p) return "p";
        else if (key == Key::q) return "q";
        else if (key == Key::r) return "r";
        else if (key == Key::s) return "s";
        else if (key == Key::t) return "t";
        else if (key == Key::u) return "u";
        else if (key == Key::v) return "v";
        else if (key == Key::w) return "w";
        else if (key == Key::x) return "x";
        else if (key == Key::y) return "y";
        else if (key == Key::z) return "z";
        else if (key == Key::num0) return "num0";
        else if (key == Key::num1) return "num1";
        else if (key == Key::num2) return "num2";
        else if (key == Key::num3) return "num3";
        else if (key == Key::num4) return "num4";
        else if (key == Key::num5) return "num5";
        else if (key == Key::num6) return "num6";
        else if (key == Key::num7) return "num7";
        else if (key == Key::num8) return "num8";
        else if (key == Key::num9) return "num9";
        else if (key == Key::escape) return "escape";
        else if (key == Key::lControl) return "lControl";
        else if (key == Key::lShift) return "lShift";
        else if (key == Key::lAlt) return "lAlt";
        else if (key == Key::lSystem) return "lSystem";
        else if (key == Key::rControl) return "rControl";
        else if (key == Key::rShift) return "rShift";
        else if (key == Key::rAlt) return "rAlt";
        else if (key == Key::rSystem) return "rSystem";
        else if (key == Key::menu) return "menu";
        else if (key == Key::lBracket) return "lBracket";
        else if (key == Key::rBracket) return "rBracket";
        else if (key == Key::semicolon) return "semicolon";
        else if (key == Key::comma) return "comma";
        else if (key == Key::period) return "period";
        else if (key == Key::quote) return "quote";
        else if (key == Key::slash) return "slash";
        else if (key == Key::backslash) return "backslash";
        else if (key == Key::tilde) return "tilde";
        else if (key == Key::equal) return "equal";
        else if (key == Key::hyphen) return "hyphen";
        else if (key == Key::space) return "space";
        else if (key == Key::enter) return "enter";
        else if (key == Key::backspace) return "backspace";
        else if (key == Key::tab) return "tab";
        else if (key == Key::pageUp) return "pageUp";
        else if (key == Key::pageDown) return "pageDown";
        else if (key == Key::end) return "end";
        else if (key == Key::home) return "home";
        else if (key == Key::insert) return "insert";
        else if (key == Key::del) return "del";
        else if (key == Key::add) return "add";
        else if (key == Key::subtract) return "subtract";
        else if (key == Key::multiply) return "multiply";
        else if (key == Key::divide) return "divide";
        else if (key == Key::left) return "left";
        else if (key == Key::right) return "right";
        else if (key == Key::up) return "up";
        else if (key == Key::down) return "down";
        else if (key == Key::numpad0) return "numpad0";
        else if (key == Key::numpad1) return "numpad1";
        else if (key == Key::numpad2) return "numpad2";
        else if (key == Key::numpad3) return "numpad3";
        else if (key == Key::numpad4) return "numpad4";
        else if (key == Key::numpad5) return "numpad5";
        else if (key == Key::numpad6) return "numpad6";
        else if (key == Key::numpad7) return "numpad7";
        else if (key == Key::numpad8) return "numpad8";
        else if (key == Key::numpad9) return "numpad9";
        else if (key == Key::f1) return "f1";
        else if (key == Key::f2) return "f2";
        else if (key == Key::f3) return "f3";
        else if (key == Key::f4) return "f4";
        else if (key == Key::f5) return "f5";
        else if (key == Key::f6) return "f6";
        else if (key == Key::f7) return "f7";
        else if (key == Key::f8) return "f8";
        else if (key == Key::f9) return "f9";
        else if (key == Key::f10) return "f10";
        else if (key == Key::f11) return "f11";
        else if (key == Key::f12) return "f12";
        else if (key == Key::f13) return "f13";
        else if (key == Key::f14) return "f14";
        else if (key == Key::f15) return "f15";
        else if (key == Key::pause) return "pause";

        else if (key == Key::mouseLeft) return "mouseLeft";
        else if (key == Key::mouseRight) return "mouseRight";
        else if (key == Key::mouseMiddle) return "mouseMiddle";
        else if (key == Key::mouseXButton1) return "mouseXButton1";
        else if (key == Key::mouseXButton2) return "mouseXButton2";

        else if (key == Key::mouseWheelUp) return "mouseWheelUp";
        else if (key == Key::mouseWheelDown) return "mouseWheelDown";
        else if (key == Key::mouseWheelLeft) return "mouseWheelLeft";
        else if (key == Key::mouseWheelRight) return "mouseWheelRight";
        return "unknown";
    }

    bool KeyHandler::isKeyPressed(Key key) {

        if (std::find(keysPressed.begin(), keysPressed.end(), key) != keysPressed.end()){
            return true;
        } else if (key <= Key::mouseWheelRight) {
            sf::Vector2f delta = MouseWheel::getDelta();
            switch (key) {
                case Key::mouseWheelUp:
                    return delta.y > 0;
                case Key::mouseWheelDown:
                    return delta.y < 0;
                case Key::mouseWheelRight:
                    return delta.x > 0;
                case Key::mouseWheelLeft:
                    return delta.x < 0;
            }
        }

        return false;
    }

    template<>
    bool convert(const YAML::Node &node, KeyHandler::Key &key) {
        std::string str = node.as<std::string>();
        if (str == "a") key = KeyHandler::Key::a;
        else if(str == "b") key = KeyHandler::Key::b;
        else if(str == "c") key = KeyHandler::Key::c;
        else if(str == "d") key = KeyHandler::Key::d;
        else if(str == "e") key = KeyHandler::Key::e;
        else if(str == "f") key = KeyHandler::Key::f;
        else if(str == "g") key = KeyHandler::Key::g;
        else if(str == "h") key = KeyHandler::Key::h;
        else if(str == "i") key = KeyHandler::Key::i;
        else if(str == "j") key = KeyHandler::Key::j;
        else if(str == "k") key = KeyHandler::Key::k;
        else if(str == "l") key = KeyHandler::Key::l;
        else if(str == "m") key = KeyHandler::Key::m;
        else if(str == "n") key = KeyHandler::Key::n;
        else if(str == "o") key = KeyHandler::Key::o;
        else if(str == "p") key = KeyHandler::Key::p;
        else if(str == "q") key = KeyHandler::Key::q;
        else if(str == "r") key = KeyHandler::Key::r;
        else if(str == "s") key = KeyHandler::Key::s;
        else if(str == "t") key = KeyHandler::Key::t;
        else if(str == "u") key = KeyHandler::Key::u;
        else if(str == "v") key = KeyHandler::Key::v;
        else if(str == "w") key = KeyHandler::Key::w;
        else if(str == "x") key = KeyHandler::Key::x;
        else if(str == "y") key = KeyHandler::Key::y;
        else if(str == "z") key = KeyHandler::Key::z;
        else if(str == "num0") key = KeyHandler::Key::num0;
        else if(str == "num1") key = KeyHandler::Key::num1;
        else if(str == "num2") key = KeyHandler::Key::num2;
        else if(str == "num3") key = KeyHandler::Key::num3;
        else if(str == "num4") key = KeyHandler::Key::num4;
        else if(str == "num5") key = KeyHandler::Key::num5;
        else if(str == "num6") key = KeyHandler::Key::num6;
        else if(str == "num7") key = KeyHandler::Key::num7;
        else if(str == "num8") key = KeyHandler::Key::num8;
        else if(str == "num9") key = KeyHandler::Key::num9;
        else if(str == "escape") key = KeyHandler::Key::escape;
        else if(str == "l-control") key = KeyHandler::Key::lControl;
        else if(str == "l-shift") key = KeyHandler::Key::lShift;
        else if(str == "l-alt") key = KeyHandler::Key::lAlt;
        else if(str == "l-system") key = KeyHandler::Key::lSystem;
        else if(str == "r-control") key = KeyHandler::Key::rControl;
        else if(str == "r-shift") key = KeyHandler::Key::rShift;
        else if(str == "r-alt") key = KeyHandler::Key::rAlt;
        else if(str == "r-system") key = KeyHandler::Key::rSystem;
        else if(str == "menu") key = KeyHandler::Key::menu;
        else if(str == "l-bracket") key = KeyHandler::Key::lBracket;
        else if(str == "r-bracket") key = KeyHandler::Key::rBracket;
        else if(str == "semicolon") key = KeyHandler::Key::semicolon;
        else if(str == "comma") key = KeyHandler::Key::comma;
        else if(str == "period") key = KeyHandler::Key::period;
        else if(str == "quote") key = KeyHandler::Key::quote;
        else if(str == "slash") key = KeyHandler::Key::slash;
        else if(str == "backslash") key = KeyHandler::Key::backslash;
        else if(str == "tilde") key = KeyHandler::Key::tilde;
        else if(str == "equal") key = KeyHandler::Key::equal;
        else if(str == "hyphen") key = KeyHandler::Key::hyphen;
        else if(str == "space") key = KeyHandler::Key::space;
        else if(str == "enter") key = KeyHandler::Key::enter;
        else if(str == "backspace") key = KeyHandler::Key::backspace;
        else if(str == "tab") key = KeyHandler::Key::tab;
        else if(str == "page-up") key = KeyHandler::Key::pageUp;
        else if(str == "page-down") key = KeyHandler::Key::pageDown;
        else if(str == "end") key = KeyHandler::Key::end;
        else if(str == "home") key = KeyHandler::Key::home;
        else if(str == "insert") key = KeyHandler::Key::insert;
        else if(str == "del") key = KeyHandler::Key::del;
        else if(str == "add") key = KeyHandler::Key::add;
        else if(str == "subtract") key = KeyHandler::Key::subtract;
        else if(str == "multiply") key = KeyHandler::Key::multiply;
        else if(str == "divide") key = KeyHandler::Key::divide;
        else if(str == "left") key = KeyHandler::Key::left;
        else if(str == "right") key = KeyHandler::Key::right;
        else if(str == "up") key = KeyHandler::Key::up;
        else if(str == "down") key = KeyHandler::Key::down;
        else if(str == "numpad0") key = KeyHandler::Key::numpad0;
        else if(str == "numpad1") key = KeyHandler::Key::numpad1;
        else if(str == "numpad2") key = KeyHandler::Key::numpad2;
        else if(str == "numpad3") key = KeyHandler::Key::numpad3;
        else if(str == "numpad4") key = KeyHandler::Key::numpad4;
        else if(str == "numpad5") key = KeyHandler::Key::numpad5;
        else if(str == "numpad6") key = KeyHandler::Key::numpad6;
        else if(str == "numpad7") key = KeyHandler::Key::numpad7;
        else if(str == "numpad8") key = KeyHandler::Key::numpad8;
        else if(str == "numpad9") key = KeyHandler::Key::numpad9;
        else if(str == "f1") key = KeyHandler::Key::f1;
        else if(str == "f2") key = KeyHandler::Key::f2;
        else if(str == "f3") key = KeyHandler::Key::f3;
        else if(str == "f4") key = KeyHandler::Key::f4;
        else if(str == "f5") key = KeyHandler::Key::f5;
        else if(str == "f6") key = KeyHandler::Key::f6;
        else if(str == "f7") key = KeyHandler::Key::f7;
        else if(str == "f8") key = KeyHandler::Key::f8;
        else if(str == "f9") key = KeyHandler::Key::f9;
        else if(str == "f10") key = KeyHandler::Key::f10;
        else if(str == "f11") key = KeyHandler::Key::f11;
        else if(str == "f12") key = KeyHandler::Key::f12;
        else if(str == "f13") key = KeyHandler::Key::f13;
        else if(str == "f14") key = KeyHandler::Key::f14;
        else if(str == "f15") key = KeyHandler::Key::f15;
        else if(str == "pause") key = KeyHandler::Key::pause;
        else if(str == "dash") key = KeyHandler::Key::dash;
        else if(str == "back-space") key = KeyHandler::Key::backSpace;
        else if(str == "back-slash") key = KeyHandler::Key::backSlash;
        else if(str == "semi-colon") key = KeyHandler::Key::semiColon;
        else if(str == "mouse-left") key = KeyHandler::Key::mouseLeft;
        else if(str == "mouse-right") key = KeyHandler::Key::mouseRight;
        else if(str == "mouse-middle") key = KeyHandler::Key::mouseMiddle;
        else if(str == "mouse-x-button1") key = KeyHandler::Key::mouseXButton1;
        else if(str == "mouse-x-button2") key = KeyHandler::Key::mouseXButton2;
        else if(str == "mouse-wheel-up") key = KeyHandler::Key::mouseWheelUp;
        else if(str == "mouse-wheel-down") key = KeyHandler::Key::mouseWheelDown;
        else if(str == "mouse-wheel-left") key = KeyHandler::Key::mouseWheelLeft;
        else if(str == "mouse-wheel-right") key = KeyHandler::Key::mouseWheelRight;
        else key = KeyHandler::Key::unknown;
        return true;
    }

    KeyHandler::Key createKeyFromYaml(YAML::Node node){
        KeyHandler::Key key;
        convert(node, key);
        return key;
    }
} // ui