#include "button.hpp"

#include "../../sfmlEvents/mouseWheel/mouseWheel.hpp"

namespace ui {
    Button createButtonFromYaml(YAML::Node node){
        if(node["b"]) return Button::b;
        else if(node["c"]) return Button::c;
        else if(node["d"]) return Button::d;
        else if(node["e"]) return Button::e;
        else if(node["f"]) return Button::f;
        else if(node["g"]) return Button::g;
        else if(node["h"]) return Button::h;
        else if(node["i"]) return Button::i;
        else if(node["j"]) return Button::j;
        else if(node["k"]) return Button::k;
        else if(node["l"]) return Button::l;
        else if(node["m"]) return Button::m;
        else if(node["n"]) return Button::n;
        else if(node["o"]) return Button::o;
        else if(node["p"]) return Button::p;
        else if(node["q"]) return Button::q;
        else if(node["r"]) return Button::r;
        else if(node["s"]) return Button::s;
        else if(node["t"]) return Button::t;
        else if(node["u"]) return Button::u;
        else if(node["v"]) return Button::v;
        else if(node["w"]) return Button::w;
        else if(node["x"]) return Button::x;
        else if(node["y"]) return Button::y;
        else if(node["z"]) return Button::z;
        else if(node["num0"]) return Button::num0;
        else if(node["num1"]) return Button::num1;
        else if(node["num2"]) return Button::num2;
        else if(node["num3"]) return Button::num3;
        else if(node["num4"]) return Button::num4;
        else if(node["num5"]) return Button::num5;
        else if(node["num6"]) return Button::num6;
        else if(node["num7"]) return Button::num7;
        else if(node["num8"]) return Button::num8;
        else if(node["num9"]) return Button::num9;
        else if(node["escape"]) return Button::escape;
        else if(node["l-control"]) return Button::lControl;
        else if(node["l-shift"]) return Button::lShift;
        else if(node["l-alt"]) return Button::lAlt;
        else if(node["l-system"]) return Button::lSystem;
        else if(node["r-control"]) return Button::rControl;
        else if(node["r-shift"]) return Button::rShift;
        else if(node["r-alt"]) return Button::rAlt;
        else if(node["r-system"]) return Button::rSystem;
        else if(node["menu"]) return Button::menu;
        else if(node["l-bracket"]) return Button::lBracket;
        else if(node["r-bracket"]) return Button::rBracket;
        else if(node["semicolon"]) return Button::semicolon;
        else if(node["comma"]) return Button::comma;
        else if(node["period"]) return Button::period;
        else if(node["quote"]) return Button::quote;
        else if(node["slash"]) return Button::slash;
        else if(node["backslash"]) return Button::backslash;
        else if(node["tilde"]) return Button::tilde;
        else if(node["equal"]) return Button::equal;
        else if(node["hyphen"]) return Button::hyphen;
        else if(node["space"]) return Button::space;
        else if(node["enter"]) return Button::enter;
        else if(node["backspace"]) return Button::backspace;
        else if(node["tab"]) return Button::tab;
        else if(node["page-up"]) return Button::pageUp;
        else if(node["page-down"]) return Button::pageDown;
        else if(node["end"]) return Button::end;
        else if(node["home"]) return Button::home;
        else if(node["insert"]) return Button::insert;
        else if(node["del"]) return Button::del;
        else if(node["add"]) return Button::add;
        else if(node["subtract"]) return Button::subtract;
        else if(node["multiply"]) return Button::multiply;
        else if(node["divide"]) return Button::divide;
        else if(node["left"]) return Button::left;
        else if(node["right"]) return Button::right;
        else if(node["up"]) return Button::up;
        else if(node["down"]) return Button::down;
        else if(node["numpad0"]) return Button::numpad0;
        else if(node["numpad1"]) return Button::numpad1;
        else if(node["numpad2"]) return Button::numpad2;
        else if(node["numpad3"]) return Button::numpad3;
        else if(node["numpad4"]) return Button::numpad4;
        else if(node["numpad5"]) return Button::numpad5;
        else if(node["numpad6"]) return Button::numpad6;
        else if(node["numpad7"]) return Button::numpad7;
        else if(node["numpad8"]) return Button::numpad8;
        else if(node["numpad9"]) return Button::numpad9;
        else if(node["f1"]) return Button::f1;
        else if(node["f2"]) return Button::f2;
        else if(node["f3"]) return Button::f3;
        else if(node["f4"]) return Button::f4;
        else if(node["f5"]) return Button::f5;
        else if(node["f6"]) return Button::f6;
        else if(node["f7"]) return Button::f7;
        else if(node["f8"]) return Button::f8;
        else if(node["f9"]) return Button::f9;
        else if(node["f10"]) return Button::f10;
        else if(node["f11"]) return Button::f11;
        else if(node["f12"]) return Button::f12;
        else if(node["f13"]) return Button::f13;
        else if(node["f14"]) return Button::f14;
        else if(node["f15"]) return Button::f15;
        else if(node["pause"]) return Button::pause;
        else if(node["dash"]) return Button::dash;
        else if(node["back-space"]) return Button::backSpace;
        else if(node["back-slash"]) return Button::backSlash;
        else if(node["semi-colon"]) return Button::semiColon;
        else if(node["mouse-left"]) return Button::mouseLeft;
        else if(node["mouse-right"]) return Button::mouseRight;
        else if(node["mouse-middle"]) return Button::mouseMiddle;
        else if(node["mouse-x-button1"]) return Button::mouseXButton1;
        else if(node["mouse-x-button2"]) return Button::mouseXButton2;
        else if(node["mouse-wheel-up"]) return Button::mouseWheelUp;
        else if(node["mouse-wheel-down"]) return Button::mouseWheelDown;
        else if(node["mouse-wheel-left"]) return Button::mouseWheelLeft;
        else if(node["mouse-wheel-right"]) return Button::mouseWheelRight;
        else return Button::unknown;
    }

    void operator >>(const YAML::Node& node, Button& button){
        button = createButtonFromYaml(node);
    }

    bool isButtonPressed(Button button) {
        if (button <= Button::pause){
            return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(button));
        } else if (button <= Button::mouseXButton2){
            return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(static_cast<int>(button) - 100));
        } else if (button <= Button::mouseWheelRight){
            sf::Vector2f delta = MouseWheel::getDelta();
            switch (button) {
                case Button::mouseWheelRight:
                    return delta.x > 0;
                case Button::mouseLeft:
                    return delta.x < 0;
                case Button::mouseWheelUp:
                    return delta.y > 0;
                case Button::mouseWheelDown:
                    return delta.y < 0;
            }
        }
        return false;
    }
} // ui