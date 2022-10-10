#include "textEmptyInteraction.hpp"

namespace ui {
    TextEmptyInteraction *TextEmptyInteraction::copy() {
        return new TextEmptyInteraction{};
    }

    bool convertPointer(const YAML::Node &node, TextEmptyInteraction *&textEmptyInteraction) {
        { textEmptyInteraction = new TextEmptyInteraction{}; return true; }
    }
} // ui