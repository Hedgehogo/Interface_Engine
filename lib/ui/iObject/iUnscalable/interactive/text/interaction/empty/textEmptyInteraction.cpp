#include "textEmptyInteraction.hpp"

namespace ui {
    TextEmptyInteraction *TextEmptyInteraction::copy() {
        return new TextEmptyInteraction{};
    }

    TextEmptyInteraction *TextEmptyInteraction::createFromYaml(const YAML::Node &node) {
        return new TextEmptyInteraction{};
    }
} // ui