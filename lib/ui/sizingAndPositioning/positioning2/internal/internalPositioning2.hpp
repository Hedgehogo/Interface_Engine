#pragma once

#include "../basePositioning2.hpp"
#include "../../positioning/internal/parent/internalPositioning.hpp"

namespace ui {
    class InternalPositioning2 : public BasePositioning2{
    protected:
        InternalPositioning vertical;
        InternalPositioning horizontal;

    public:
        InternalPositioning2(sf::Vector2f coefficient);
		
        void init(sf::RenderTarget& renderTarget);
		
        sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize);

    private:
        InternalPositioning2(InternalPositioning vertical, InternalPositioning horizontal);

    public:
        InternalPositioning2* copy();
    };
	
	bool convertPointer(const YAML::Node &node, InternalPositioning2 *&internalPositioning2);
}