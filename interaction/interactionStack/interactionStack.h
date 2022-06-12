#pragma once
#include <vector>
#include "../iInteraction/iInteraction.h"
namespace ui {
    class InteractionStack {
    protected:
        std::vector<ui::IInteraction *> interactionStack;
    public:
        InteractionStack(std::vector<ui::IInteraction *> &&interactionStack);

        ui::IInteraction *at(unsigned index);

        void add(ui::IInteraction *element);
    };
}