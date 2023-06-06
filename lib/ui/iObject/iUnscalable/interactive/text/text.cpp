#include "text.hpp"

#include <cmath>
#include "../../../../../modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
	std::vector<BaseCharacter*>::iterator nullBaseCharacterIterator{nullptr};
	
	Text::Text(std::vector<BaseTextBlock*> textBlocks, IUninteractive* background, int size, sf::Font* font, sf::Color textColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor,
			   sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor, BaseResizer* resizer, TextInteraction* textInteraction) :
		background(background), size(size), textBocks(textBlocks), resizer(resizer), textInteraction(textInteraction) {
		for(BaseTextBlock* textBlock: textBlocks) {
			textBlock->setTextVariables(textColor, textSelectionColor, backgroundSelectionColor, (inactiveTextSelectionColor == nullColor ? textColor : inactiveTextSelectionColor), inactiveBackgroundSelectionColor, font,
										size);
			std::vector<BaseCharacter*> characters = textBlock->getCharacters();
			textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
		}
		resizer->init(textCharacters, lines);
	}
	
	Text::~Text() {
		for(BaseLine*& line: lines) {
			delete line;
		}
		for(BaseCharacter*& textCharacter: textCharacters) {
			delete textCharacter;
		}
		for(BaseTextBlock*& textBlock: textBocks) {
			delete textBlock;
		}
		delete background;
		delete resizer;
		delete textInteraction;
	}
	
	void Text::init(InteractiveInitInfo interactiveInitInfo) {
		interactiveInitInfo.updateManager.add(*this);
		this->renderTarget = &interactiveInitInfo.renderTarget;
		InitInfo initInfo{interactiveInitInfo.window, renderTexture, drawManager, interactiveInitInfo.updateManager, *interactionManager, *interactionStack, interactiveInitInfo.panelManager};
		background->init(interactiveInitInfo.toGeneral(*interactionManager, *interactionStack));
		interactiveInitInfo.drawManager.add(*this);
		for(BaseTextBlock* textBlock: textBocks) {
			textBlock->init(initInfo, interactiveInitInfo.toGeneral(*interactionManager, *interactionStack));
		}
		
		textInteraction->init({interactiveInitInfo.toGeneral(*interactionManager, *interactionStack), *this});
	}
	
	void Text::setSelection(Text::Selection selection) {
		this->selection = selection;
	}
	
	void Text::setSelectionStart(std::vector<BaseCharacter*>::iterator start) {
		selection.start = start;
	}
	
	void Text::setSelectionEnd(std::vector<BaseCharacter*>::iterator end) {
		selection.end = end;
	}
	
	Text::Selection Text::getSelection() const {
		return selection;
	}
	
	std::vector<BaseCharacter*>::iterator Text::getSelectionStart() const {
		return selection.start;
	}
	
	std::vector<BaseCharacter*>::iterator Text::getSelectionEnd() const {
		return selection.end;
	}
	
	std::u32string Text::getSelectionText() {
		if(selection.start != nullBaseCharacterIterator && selection.end != nullBaseCharacterIterator) {
			std::u32string SelectionText{};
			std::vector<BaseCharacter*>::iterator localStart;
			std::vector<BaseCharacter*>::iterator localEnd;
			if(std::distance(selection.start, selection.end) < 0) {
				localStart = selection.end;
				localEnd = selection.start;
			} else {
				localStart = selection.start;
				localEnd = selection.end;
			}
			SelectionText.resize(std::distance(localStart, localEnd));
			
			for(int i = 0; i < SelectionText.length(); ++i) {
				SelectionText[i] = (*(localStart + i))->getChar();
			}
			
			return SelectionText;
		}
		return std::u32string{U""};
	}
	
	float getDistanceY(std::vector<BaseCharacter*>::iterator iterator, float mousePositionY) {
		return std::min(std::abs(mousePositionY - (*iterator)->getPosition().y), std::abs(mousePositionY - ((*iterator)->getPosition().y - (*iterator)->getHeight())));
	}
	
	bool minDistanceX(std::vector<BaseCharacter*>::iterator& a, std::vector<BaseCharacter*>::iterator& b, float find) {
		float distanceToA{std::abs((*a)->getPosition().x - find)},
			distanceToA1{std::abs((*a)->getPosition().x + (*a)->getAdvance() - find)},
			distanceToB{std::abs((*b)->getPosition().x - find)},
			distanceToB1{std::abs((*b)->getPosition().x + (*b)->getAdvance() - find)};
		if(distanceToA > distanceToA1)
			std::swap(distanceToA, distanceToA1);
		if(distanceToB > distanceToB1)
			std::swap(distanceToB, distanceToB1);
		
		if(distanceToA == distanceToB)
			return distanceToA1 < distanceToB1;
		else
			return distanceToA < distanceToB;
	}
	
	
	std::vector<BaseCharacter*>::iterator Text::getCharacter(sf::Vector2f mousePosition) {
		std::vector<BaseCharacter*>::iterator result{nullptr};
		
		for(auto iterator = textCharacters.begin(); iterator != textCharacters.end(); ++iterator) {
			if(result != nullBaseCharacterIterator) {
				float DistanceYToIterator{getDistanceY(iterator, mousePosition.y)};
				float DistanceYToResult{getDistanceY(result, mousePosition.y)};
				if(DistanceYToIterator <= DistanceYToResult) {
					if(DistanceYToIterator < DistanceYToResult) {
						result = iterator;
					}
					if(minDistanceX(iterator, result, mousePosition.x)) {
						result = iterator;
					}
				}
			} else {
				result = iterator;
			}
		}
		
		if(mousePosition.x > (*result)->getPosition().x + (static_cast<float>((*result)->getSizeTexture().x) / 2.f)) {
			++result;
		}
		
		return result;
	}
	
	void Text::update() {
		if(interact != oldInteract) {
			oldInteract = interact;
			
			if(interact) {
				interactionManager->addInteraction(*textInteraction);
			} else {
				interactionManager->deleteInteraction(*textInteraction);
			}
		}
		interact = false;
		
		for(BaseTextBlock* textBlock: textBocks) {
			textBlock->update();
		}
	}
	
	bool Text::updateInteractions(sf::Vector2f mousePosition) {
		interact = true;
		
		for(BaseTextBlock* textBock: textBocks) {
			
			if(textBock->in(mousePosition))
				if(textBock->updateInteractions(mousePosition))
					return true;
		}
		return background->updateInteractions(mousePosition);
	}
	
	void Text::draw() {
		
		bool rerender{false};
		int i = 0;
		for(auto& character: textCharacters) {
			if(character->getRerender()) {
				rerender = true;
				character->setRerender(false);
			}
			i++;
		}
		
		if(rerender) {
			renderTexture.clear(sf::Color{0, 0, 0, 0});
			
			drawManager.draw();
			
			for(BaseCharacter* character: textCharacters) {
				character->draw(true);
			}
			
			for(BaseCharacter* character: textCharacters) {
				character->draw(false);
			}
			
			for(BaseLine*& line: lines) {
				line->draw();
			}
			renderTexture.display();
			texture = renderTexture.getTexture();
			sprite.setTexture(texture);
		}
		
		renderTarget->draw(sprite);
	}
	
	void Text::move(sf::Vector2f position) {
		view.reset({getPosition() + position, view.getSize()});
		renderTexture.setView(view);
		sprite.move(position);
		background->move(position);
		resizer->move(position);
	}
	
	void Text::setPosition(sf::Vector2f position) {
		view.reset({position, view.getSize()});
		renderTexture.setView(view);
		sprite.setPosition(position);
		background->setPosition(position);
		resizer->setPosition(position);
	}
	
	void Text::resize(sf::Vector2f size, sf::Vector2f position) {
		resizer->resize(size, position);
		
		size = max(resizer->getSize(), size);
		background->resize(size, position);
		
		view.reset({position, size});
		renderTexture.create(size.x, size.y);
		renderTexture.setView(view);
		sprite.setTextureRect({{0, 0}, sf::Vector2i(size)});
	}
	
	sf::Vector2f Text::getAreaPosition() const {
		return background->getAreaPosition();
	}
	
	sf::Vector2f Text::getAreaSize() const {
		return max(background->getAreaSize(), resizer->getSize());
	}
	
	sf::Vector2f Text::getMinSize() const {
		return max(resizer->getMinSize(), background->getMinSize());
	}
	
	sf::Vector2f Text::getNormalSize() const {
		return max(resizer->getNormalSize(), background->getNormalSize());
	}
	
	Text::Text(std::vector<BaseTextBlock*> textBlocks, IUninteractive* background, uint size, BaseResizer* resizer, sf::RenderTarget* renderTarget, TextInteraction* textInteraction) :
		textBocks(textBlocks), background(background), size(size), resizer(resizer), renderTarget(renderTarget), textInteraction(textInteraction) {
		for(BaseTextBlock* textBlock: textBlocks) {
			std::vector<BaseCharacter*> characters = textBlock->getCharacters();
			textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
		}
		resizer->init(textCharacters, lines);
	}
	
	Text* Text::copy() {
		std::vector<BaseTextBlock*> copyTextBlocks;
		for(BaseTextBlock* textBlock: textBocks) {
			copyTextBlocks.push_back(textBlock->copy());
		}
		
		return new Text{copyTextBlocks, background->copy(), size, resizer->copy(), renderTarget, textInteraction->copy()};
	}
	
	
	bool DecodePointer<Text>::decodePointer(const YAML::Node& node, Text*& text) {
		text = new Text{
			node["text-block"] ? std::vector{node["text-block"].as<BaseTextBlock*>()} : node["text-blocks"].as<std::vector<BaseTextBlock*>>(),
			convDefPtr<IUninteractive, FullColor>(node["background"], sf::Color::White),
			convDef(node["size"], 14),
			convDef<sf::Font*>(node["font"],  nullptr),
			convDef(node["text-color"], sf::Color::Black),
			convDef(node["text-selection-color"], sf::Color::White),
			convDef(node["background-selection-color"], sf::Color::Blue),
			convDef(node["inactive-text-selection-color"], nullColor),
			convDef(node["inactive-background-selection-color"], sf::Color{150, 150, 150}),
			convDefPtr<BaseResizer, Resizer>(node["resizer"], 1.15f, BaseResizer::Align::left),
			node["text-interaction"] ? node["text-interaction"].as<TextInteraction*>() :
				new TextSelectionAndCopyInteraction{
					{
						{
							new TextPressedInteraction{
								new TextSelectionEvent{},
								{Key::mouseLeft}
							},
							{Key::mouseLeft}
						}
					},
					
				}
		};
		return true;
	}
	
	void Text::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		for(BaseCharacter*& character: textCharacters) {
			character->drawDebug(renderTarget, indentAddition, hue + hueOffset, hueOffset);
		}
		
		background->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
	}
}