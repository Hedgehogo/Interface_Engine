#include "objectTextBlock.h"
#include "../../character/simple/character.h"
ui::ObjectTextBlock::ObjectTextBlock(ui::IObject* object, sf::Vector2f size, bool isCharacter) : BaseTextBlock(), size(size), objectCharacter(new ObjectCharacter(object)), object(object), isCharacter(isCharacter) {
}

void ui::ObjectTextBlock::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
	object->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
    sf::Vector2f minSize{object->getMinSize()};
    object->setSize({std::max(size.x, minSize.x), std::max(size.y, minSize.y)});
}

bool ui::ObjectTextBlock::in(sf::Vector2f mousePosition) {
    return objectCharacter->in(mousePosition);
}

std::vector<ui::BaseCharacter*> ui::ObjectTextBlock::getCharacters() {
    std::vector<ui::BaseCharacter*> result;
    if(!isCharacter){
        result.push_back(new Character{L'\n', textVariables, lines});
    }

    result.push_back(objectCharacter);

    if(!isCharacter){
        result.push_back(new Character{L'\n', textVariables, lines});
    }

    return result;
}

void ui::ObjectTextBlock::update() {}

bool ui::ObjectTextBlock::updateInteractions(sf::Vector2f mousePosition) {
    return object->updateInteractions(mousePosition);
}

ui::BaseTextBlock *ui::ObjectTextBlock::copy() {
    return new ObjectTextBlock{object->copy(), object->getAreaSize(), isCharacter};
}
