#include "button.hpp"

#include <iostream>
#include "../../sfmlEvents/mouseWheel/mouseWheel.hpp"

namespace ui {
    Key createKeyFromYaml(YAML::Node node){
        std::string str = node.as<std::string>();
        if (str == "a") return Key::a;
        else if(str == "b") return Key::b;
        else if(str == "c") return Key::c;
        else if(str == "d") return Key::d;
        else if(str == "e") return Key::e;
        else if(str == "f") return Key::f;
        else if(str == "g") return Key::g;
        else if(str == "h") return Key::h;
        else if(str == "i") return Key::i;
        else if(str == "j") return Key::j;
        else if(str == "k") return Key::k;
        else if(str == "l") return Key::l;
        else if(str == "m") return Key::m;
        else if(str == "n") return Key::n;
        else if(str == "o") return Key::o;
        else if(str == "p") return Key::p;
        else if(str == "q") return Key::q;
        else if(str == "r") return Key::r;
        else if(str == "s") return Key::s;
        else if(str == "t") return Key::t;
        else if(str == "u") return Key::u;
        else if(str == "v") return Key::v;
        else if(str == "w") return Key::w;
        else if(str == "x") return Key::x;
        else if(str == "y") return Key::y;
        else if(str == "z") return Key::z;
        else if(str == "num0") return Key::num0;
        else if(str == "num1") return Key::num1;
        else if(str == "num2") return Key::num2;
        else if(str == "num3") return Key::num3;
        else if(str == "num4") return Key::num4;
        else if(str == "num5") return Key::num5;
        else if(str == "num6") return Key::num6;
        else if(str == "num7") return Key::num7;
        else if(str == "num8") return Key::num8;
        else if(str == "num9") return Key::num9;
        else if(str == "escape") return Key::escape;
        else if(str == "l-control") return Key::lControl;
        else if(str == "l-shift") return Key::lShift;
        else if(str == "l-alt") return Key::lAlt;
        else if(str == "l-system") return Key::lSystem;
        else if(str == "r-control") return Key::rControl;
        else if(str == "r-shift") return Key::rShift;
        else if(str == "r-alt") return Key::rAlt;
        else if(str == "r-system") return Key::rSystem;
        else if(str == "menu") return Key::menu;
        else if(str == "l-bracket") return Key::lBracket;
        else if(str == "r-bracket") return Key::rBracket;
        else if(str == "semicolon") return Key::semicolon;
        else if(str == "comma") return Key::comma;
        else if(str == "period") return Key::period;
        else if(str == "quote") return Key::quote;
        else if(str == "slash") return Key::slash;
        else if(str == "backslash") return Key::backslash;
        else if(str == "tilde") return Key::tilde;
        else if(str == "equal") return Key::equal;
        else if(str == "hyphen") return Key::hyphen;
        else if(str == "space") return Key::space;
        else if(str == "enter") return Key::enter;
        else if(str == "backspace") return Key::backspace;
        else if(str == "tab") return Key::tab;
        else if(str == "page-up") return Key::pageUp;
        else if(str == "page-down") return Key::pageDown;
        else if(str == "end") return Key::end;
        else if(str == "home") return Key::home;
        else if(str == "insert") return Key::insert;
        else if(str == "del") return Key::del;
        else if(str == "add") return Key::add;
        else if(str == "subtract") return Key::subtract;
        else if(str == "multiply") return Key::multiply;
        else if(str == "divide") return Key::divide;
        else if(str == "left") return Key::left;
        else if(str == "right") return Key::right;
        else if(str == "up") return Key::up;
        else if(str == "down") return Key::down;
        else if(str == "numpad0") return Key::numpad0;
        else if(str == "numpad1") return Key::numpad1;
        else if(str == "numpad2") return Key::numpad2;
        else if(str == "numpad3") return Key::numpad3;
        else if(str == "numpad4") return Key::numpad4;
        else if(str == "numpad5") return Key::numpad5;
        else if(str == "numpad6") return Key::numpad6;
        else if(str == "numpad7") return Key::numpad7;
        else if(str == "numpad8") return Key::numpad8;
        else if(str == "numpad9") return Key::numpad9;
        else if(str == "f1") return Key::f1;
        else if(str == "f2") return Key::f2;
        else if(str == "f3") return Key::f3;
        else if(str == "f4") return Key::f4;
        else if(str == "f5") return Key::f5;
        else if(str == "f6") return Key::f6;
        else if(str == "f7") return Key::f7;
        else if(str == "f8") return Key::f8;
        else if(str == "f9") return Key::f9;
        else if(str == "f10") return Key::f10;
        else if(str == "f11") return Key::f11;
        else if(str == "f12") return Key::f12;
        else if(str == "f13") return Key::f13;
        else if(str == "f14") return Key::f14;
        else if(str == "f15") return Key::f15;
        else if(str == "pause") return Key::pause;
        else if(str == "dash") return Key::dash;
        else if(str == "back-space") return Key::backSpace;
        else if(str == "back-slash") return Key::backSlash;
        else if(str == "semi-colon") return Key::semiColon;
        else if(str == "mouse-left") return Key::mouseLeft;
        else if(str == "mouse-right") return Key::mouseRight;
        else if(str == "mouse-middle") return Key::mouseMiddle;
        else if(str == "mouse-x-button1") return Key::mouseXButton1;
        else if(str == "mouse-x-button2") return Key::mouseXButton2;
        else if(str == "mouse-wheel-up") return Key::mouseWheelUp;
        else if(str == "mouse-wheel-down") return Key::mouseWheelDown;
        else if(str == "mouse-wheel-left") return Key::mouseWheelLeft;
        else if(str == "mouse-wheel-right") return Key::mouseWheelRight;
        else return Key::unknown;
    }

    std::string toString(Key key){
        if (key == Key::a) return "a";
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

    bool isKeyPressed(Key key) {
        if (key <= Key::pause) {
            return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
        } else if (key <= Key::mouseXButton2) {
            return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(static_cast<int>(key) - static_cast<int>(Key::mouseLeft)));
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
} // ui