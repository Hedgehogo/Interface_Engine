#include "textEmptyInteraction.hpp"

namespace ui {
    TextEmptyInteraction *TextEmptyInteraction::copy() {
        return new TextEmptyInteraction{};
    }
} // ui