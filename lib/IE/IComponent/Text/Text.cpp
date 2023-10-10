#include "Text.hpp"

#include <cmath>
#include "IE/Modules/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ie {
	Text::Make::Make(
		std::vector<BoxPtr<BaseTextBlock::Make>>&& textBlocks,
		sf::Font* font,
		BoxPtr<IUninteractive::Make>&& background,
		uint size,
		sf::Color textColor,
		sf::Color textSelectionColor,
		sf::Color backgroundSelectionColor,
		sf::Color inactiveTextSelectionColor,
		sf::Color inactiveBackgroundSelectionColor,
		sf::Text::Style style,
		BoxPtr<BaseResizer::Make>&& resizer,
		BoxPtr<IBasicInteraction<Text&>::Make>&& textInteraction
	) : textBlocks(std::move(textBlocks)),
		font(font),
		background(std::move(background)),
		size(size),
		textColor(textColor),
		textSelectionColor(textSelectionColor),
		backgroundSelectionColor(backgroundSelectionColor),
		inactiveTextSelectionColor(inactiveTextSelectionColor),
		inactiveBackgroundSelectionColor(inactiveBackgroundSelectionColor),
		style(style),
		resizer(std::move(resizer)),
		textInteraction(std::move(textInteraction)) {
	}
	
	Text* Text::Make::make(InitInfo initInfo) {
		return new Text{std::move(*this), initInfo};
	}
	
	Text::Text(Make&& make, InitInfo initInfo) :
		interactionManager(&initInfo.interactionManager),
		renderTarget(&initInfo.renderTarget),
		background(make.background->make(initInfo)),
		interact(false),
		oldInteract(false),
		size(make.size),
		textBlocks(
			mapMake(
				std::move(make.textBlocks),
				TextBockInitInfo{
					initInfo,
					renderTexture,
					drawManager,
					*interactionManager,
					TextBockInitInfo::TextVariables{
						make.textColor,
						make.textSelectionColor,
						make.backgroundSelectionColor,
						make.inactiveTextSelectionColor,
						make.inactiveBackgroundSelectionColor,
						make.font,
						make.style,
						make.size
					}
				}
			)
		),
		resizer(nullptr),
		textInteraction(nullptr) {
		textInteraction.set(make.textInteraction->make({initInfo, *this}));
		for(auto& textBlock: this->textBlocks) {
			textBlock->setKerning(textCharacters.empty() ? U'\0' : textCharacters[textCharacters.size() - 1]->getChar());
			std::vector<BaseCharacter*> characters = textBlock->getCharacters();
			textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
		}
		resizer = BoxPtr{make.resizer->make(ResizerInitInfo(textCharacters, lines))};
		
		initInfo.updateManager.add(*this);
		initInfo.drawManager.add(*this);
	}
	
	Text::Text(
		std::vector<BoxPtr<BaseTextBlock>>&& textBlocks,
		sf::Font*,
		BoxPtr<IUninteractive>&& background,
		int size,
		sf::Color,
		sf::Color,
		sf::Color,
		sf::Color,
		sf::Color,
		sf::Text::Style,
		BoxPtr<BaseResizer>&& resizer,
		BoxPtr<IBasicInteraction<Text&>>&& textInteraction
	) : interactionManager(nullptr),
		background(std::move(background)),
		size(size),
		textBlocks(std::move(textBlocks)),
		resizer(std::move(resizer)),
		textInteraction(std::move(textInteraction)) {
		for(auto& textBlock: this->textBlocks) {
			std::vector<BaseCharacter*> characters = textBlock->getCharacters();
			textCharacters.insert(textCharacters.end(), characters.begin(), characters.end());
		}
		this->resizer->init(ResizerInitInfo(textCharacters, lines));
	}
	
	void Text::init(InitInfo) {
/*
		this->interactionManager = &initInfo.interactionManager;
		this->renderTarget = &initInfo.renderTarget;
		initInfo.updateManager.add(*this);
		background->init(initInfo);
		initInfo.drawManager.add(*this);
		
		for(auto& textBlock: textBlocks) {
			textBlock->init({initInfo, renderTexture, drawManager, *interactionManager});
		}
		
		textInteraction->init({initInfo, *this});
*/
		throw std::runtime_error("Text::init() not correct");
	}
	
	void Text::setSelection(Text::Selection selection) {
		this->selection = selection;
	}
	
	void Text::setSelectionStart(orl::Option<std::vector<BaseCharacter*>::iterator> start) {
		selection.start = start;
	}
	
	void Text::setSelectionEnd(orl::Option<std::vector<BaseCharacter*>::iterator> end) {
		selection.end = end;
	}
	
	Text::Selection Text::getSelection() const {
		return selection;
	}
	
	std::vector<BaseCharacter*>::iterator Text::getSelectionStart() const {
		return selection.start.except();
	}
	
	std::vector<BaseCharacter*>::iterator Text::getSelectionEnd() const {
		return selection.end.except();
	}
	
	std::u32string Text::getSelectionText() {
		if(selection.start && selection.end) {
			std::u32string SelectionText{};
			std::vector<BaseCharacter*>::iterator localStart;
			std::vector<BaseCharacter*>::iterator localEnd;
			if(std::distance(selection.start.some(), selection.end.some()) < 0) {
				localStart = selection.end.some();
				localEnd = selection.start.some();
			} else {
				localStart = selection.start.some();
				localEnd = selection.end.some();
			}
			SelectionText.resize(std::distance(localStart, localEnd));
			
			for(std::size_t i = 0; i < SelectionText.length(); ++i) {
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
		
		if(distanceToA == distanceToB) {
			return distanceToA1 < distanceToB1;
		} else {
			return distanceToA < distanceToB;
		}
	}
	
	orl::Option<std::vector<BaseCharacter*>::iterator> Text::getCharacter(sf::Vector2f mousePosition) {
		orl::Option<std::vector<BaseCharacter*>::iterator> result{};
		
		for(auto iterator = textCharacters.begin(); iterator != textCharacters.end(); ++iterator) {
			if(result) {
				float DistanceYToIterator{getDistanceY(iterator, mousePosition.y)};
				float DistanceYToResult{getDistanceY(result.some(), mousePosition.y)};
				if(DistanceYToIterator <= DistanceYToResult) {
					if(DistanceYToIterator < DistanceYToResult) {
						result = iterator;
					}
					if(minDistanceX(iterator, result.some(), mousePosition.x)) {
						result = iterator;
					}
				}
			} else {
				result = iterator;
			}
		}
		
		if(mousePosition.x > (*result.except())->getPosition().x + (static_cast<float>((*result.except())->getSizeTexture().x) / 2.f)) {
			++result.some();
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
		
		for(auto& textBlock: textBlocks) {
			textBlock->update();
		}
	}
	
	bool Text::updateInteractions(sf::Vector2f mousePosition) {
		interact = true;
		
		for(auto& textBock: textBlocks) {
			
			if(textBock->in(mousePosition))
				if(textBock->updateInteractions(mousePosition))
					return true;
		}
		return background->updateInteractions(mousePosition);
	}
	
	void Text::draw() {
		bool rerender{false};
		for(auto& character: textCharacters) {
			if(character->getRerender()) {
				rerender = true;
				character->setRerender(false);
			}
		}
		
		if(rerender) {
			renderTexture.clear(sf::Color{0, 0, 0, 0});
			
			drawManager.draw();
			
			for(auto& character: textCharacters) {
				character->draw(true);
			}
			
			for(auto& character: textCharacters) {
				character->draw(false);
			}
			
			for(auto& line: lines) {
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
	
	Text* Text::copy() {
		return nullptr;
	}
	
	bool DecodePointer<Text>::decodePointer(const YAML::Node& node, Text*& text) {
		sf::Color textColor{convDef(node["text-color"], sf::Color::Black)};
		
		text = new Text{
			node["text-block"] ? std::vector{node["text-block"].as <BoxPtr<BaseTextBlock> > ()} : node["text-blocks"].as<std::vector<BoxPtr<BaseTextBlock>>>(),
			node["font"].as<sf::Font*>(),
			convDefBoxPtr<IUninteractive, FullColor>(node["background"], sf::Color::White),
			convDef(node["size"], 14),
			textColor,
			convDef(node["text-selection-color"], sf::Color::White),
			convDef(node["background-selection-color"], sf::Color::Blue),
			convDef(node["inactive-text-selection-color"], textColor),
			convDef(node["inactive-background-selection-color"],sf::Color{150, 150, 150}),
			convDef<sf::Text::Style>(node["style"], {}),
			convDefBoxPtr<BaseResizer, Resizer>(node["resizer"], 1.15f, BaseResizer::Align::Left),
			node["text-interaction"] ? node["text-interaction"].as < BoxPtr < IBasicInteraction<Text&>>>() : makeBoxPtr<BasicEmptyInteraction<Text&>>()};
		return true;
	}
	
	void Text::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		for(BaseCharacter*& character: textCharacters) {
			character->drawDebug(renderTarget, indentAddition, hue + hueOffset, hueOffset);
		}
		
		background->drawDebug(renderTarget, indent, indentAddition, hue + hueOffset, hueOffset);
	}
}