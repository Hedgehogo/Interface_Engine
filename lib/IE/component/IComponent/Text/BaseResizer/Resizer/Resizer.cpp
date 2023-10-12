#include "Resizer.hpp"

namespace ie {
	Resizer::Make::Make(float lineSpacing, BaseResizer::Align align, BaseResizer::Algorithm algorithm) : lineSpacing(lineSpacing), align(align), algorithm(algorithm) {
	}
	
	Resizer* Resizer::Make::make(ResizerInitInfo initInfo) {
		return new Resizer{std::move(*this), initInfo};
	}
	
	Resizer::Resizer(Make&& make, ResizerInitInfo initInfo) : BaseResizer{make.lineSpacing, make.align, make.algorithm, initInfo} {
	}
	
	Resizer::Resizer(float lineSpacing, Align align, Algorithm algorithm) : BaseResizer{lineSpacing, align, algorithm} {
	}
	
	void Resizer::move(sf::Vector2f position) {
		startRender += position;
		endRender += position;
		
		for(auto& character: *characters) {
			character->move(position);
		}
		
		for(auto& line: *lines) {
			line->move(position);
		}
	}
	
	void Resizer::setPosition(sf::Vector2f position) {
		sf::Vector2f offset{position - startRender};
		for(auto& character: *characters) {
			character->move({offset});
		}
		
		for(auto& line: *lines) {
			line->move(offset);
		}
		
		endRender += offset;
		startRender = position;
	}
	
	void Resizer::printCharacter(std::vector<BaseCharacter*>::iterator character, float kerning) {
		(*character)->setPosition(nextPosition);
		nextPosition.x += (*character)->getAdvance() + kerning;
	}
	
	float Resizer::equalize(std::vector<BaseCharacter*>::iterator endCharacter) {
		float lineSize{0};
		float characterSize;
		for(auto character = afterEnter; character != endCharacter; ++character) {
			characterSize = (*character)->getHeight();
			if(lineSize < characterSize)
				lineSize = characterSize;
		}
		
		sf::Vector2f offset{endRender.x - ((*(endCharacter - 1))->getPosition().x), lineSize};
		
		switch(align) {
			case Align::Left:
				offset.x = 0;
				break;
			case Align::Center:
				offset.x /= 2;
				break;
			default:
				break;
		}
		
		for(auto character = afterEnter; character != endCharacter; ++character) {
			(*character)->move(offset);
		}
		
		const std::vector<BoxPtr<BaseLine>>* oldLine = nullptr;
		float startLine = 0;
		
		for(auto character = afterEnter; character != endCharacter; ++character) {
			auto& characterLine = (*character)->getLine();
			if(oldLine != &characterLine) {
				sf::Vector2f characterPos = (*character)->getPosition();
				if(oldLine) {
					for(auto & line: *oldLine) {
						BaseLine* copyLine = line->copy();
						copyLine->resize(startLine, characterPos.x, characterPos.y);
						this->lines->emplace_back(copyLine);
					}
				}
				
				oldLine = &characterLine;
				startLine = characterPos.x;
			}
		}
		
		if(oldLine) {
			BaseCharacter* character = *(endCharacter - ((endCharacter != characters->begin() + 1 && (*(endCharacter - 1))->isSpecial() != BaseCharacter::Special::No) ? 2 : 1));
			sf::Vector2f lineEnd = character->getPosition();
			lineEnd.x += character->getAdvance();
			
			for(auto& line: *oldLine) {
				BaseLine* copyLine = line->copy();
				copyLine->resize(startLine, lineEnd.x, lineEnd.y);
				this->lines->emplace_back(copyLine);
			}
		}
		return lineSize;
	}
	
	void Resizer::porting(std::vector<BaseCharacter*>::iterator endCharacter) {
		float lineSize = equalize(endCharacter);
		nextPosition.y += lineSize * lineSpacing;
		nextPosition.x = startRender.x;
		
		afterEnter = endCharacter;
	}
	
	void Resizer::autoPorting(std::vector<BaseCharacter*>::iterator endCharacter) {
		float lineSize = equalize(afterSpace);
		nextPosition.y += lineSize * lineSpacing;
		nextPosition.x = startRender.x;
		
		float kerning{0};
		for(auto character = afterSpace; character != endCharacter; ++character) {
			kerning = (character + 1 != characters->end()) ? ((*character)->getKerning((*(character + 1))->getChar())) : 0;
			
			printCharacter(character, kerning);
		}
		
		afterEnter = afterSpace;
		afterSpace = endCharacter;
	}
	
	void Resizer::deleteOldCash(sf::Vector2f size, sf::Vector2f position) {
		lines->clear();
		
		startRender = position;
		endRender = position + size;
		this->nextPosition = startRender;
		
		afterEnter = characters->begin();
		afterSpace = characters->begin();
	}
	
	void Resizer::characterResize(float kerning) {
		if(algorithm == BaseResizer::Algorithm::Console)
			return spaceResize(kerning);
		
		printCharacter(currentCharacter, kerning);
	}
	
	void Resizer::spaceResize(float kerning) {
		if(algorithm == BaseResizer::Algorithm::Absolute)
			return characterResize(kerning);
		
		if(this->nextPosition.x + (algorithm == BaseResizer::Algorithm::Console ? (*currentCharacter)->getAdvance() : 0) <= endRender.x) {
			printCharacter(currentCharacter, kerning);
			afterSpace = currentCharacter + 1;
		} else {
			autoPorting(currentCharacter + 1);
		}
	}
	
	void Resizer::enterResize() {
		(*currentCharacter)->setPosition(nextPosition);
		if(this->nextPosition.x > endRender.x)
			autoPorting(currentCharacter + 1);
		porting(currentCharacter + 1);
	}
	
	void Resizer::fullObjectResize() {
		if(nextPosition.x != startRender.x) {
			(*currentCharacter)->setPosition(nextPosition);
			if(this->nextPosition.x > endRender.x)
				autoPorting(currentCharacter);
			porting(currentCharacter);
		}
		(*currentCharacter)->resize(nextPosition, endRender.x);
		nextPosition.y += lineSpacing * (*currentCharacter)->getHeight();
	}
	
	void Resizer::endLineEqualize() {
		if(endRender.x < this->nextPosition.x) {
			autoPorting(characters->end());
		}
		equalize(characters->end());
	}
	
	void Resizer::resize(sf::Vector2f size, sf::Vector2f position) {
		if(characters->empty()) {
			startRender = position;
			endRender = position + size;
			return;
		}
		if(size.x == endRender.x - startRender.x) {
			setPosition(position);
			return;
		}
		
		deleteOldCash(size, position);
		
		float kerning{0};
		
		for(currentCharacter = characters->begin(); currentCharacter != characters->end(); ++currentCharacter) {
			kerning = (currentCharacter + 1 != characters->end()) ? (*currentCharacter)->getKerning((*(currentCharacter + 1))->getChar()) : 0;
			
			switch((*currentCharacter)->isSpecial()) {
				case BaseCharacter::Special::No:
					characterResize(kerning);
					break;
				case BaseCharacter::Special::Space:
					spaceResize(kerning);
					break;
				case BaseCharacter::Special::Enter:
					enterResize();
					break;
				case BaseCharacter::Special::FullLine:
					fullObjectResize();
					break;
			}
		}
		
		endLineEqualize();
	}
	
	sf::Vector2f Resizer::getPosition() {
		return startRender;
	}
	
	sf::Vector2f Resizer::getSize() {
		if(characters->empty())
			return {0, 0};
		std::vector<BaseCharacter*>::iterator maxX{
			std::max_element(characters->begin(), characters->end(), [](BaseCharacter* elem, BaseCharacter* elem2) {
				return elem->getPosition().x < elem2->getPosition().x;
			})
		};
		
		std::vector<BaseCharacter*>::iterator maxY{
			std::max_element(characters->begin(), characters->end(), [](BaseCharacter* elem, BaseCharacter* elem2) {
				return elem->getPosition().y < elem2->getPosition().y;
			})
		};
		return sf::Vector2f{(*maxX)->getPosition().x, (*maxY)->getPosition().y} - getPosition();
	}
	
	sf::Vector2f Resizer::getMinSizeBase() {
		sf::Vector2f minSize = {0, 0};
		float wordSizeX = 0;
		
		for(auto& character: *characters) {
			if(character->isSpecial() == BaseCharacter::Special::No) {
				wordSizeX += character->getMinAdvance();
			} else {
				if(minSize.x < wordSizeX)
					minSize.x = wordSizeX;
				wordSizeX = 0;
			}
		}
		if(minSize.x < wordSizeX)
			minSize.x = wordSizeX;
		
		return minSize;
	}
	
	sf::Vector2f Resizer::getMinSizeConsole() {
		sf::Vector2f minSize = {0, 0};
		
		float advance = 0;
		for(auto& character: *characters) {
			advance = character->getMinAdvance();
			if(advance > minSize.x)
				minSize.x = advance;
		}
		return minSize;
	}
	
	sf::Vector2f Resizer::getMinSizeAbsolute() {
		sf::Vector2f minSize = {0, 0};
		float wordSizeX = 0;
		
		for(auto& character: *characters) {
			if(character->isSpecial() != BaseCharacter::Special::Enter) {
				wordSizeX += character->getMinAdvance();
			} else {
				if(minSize.x < wordSizeX)
					minSize.x = wordSizeX;
				wordSizeX = 0;
			}
		}
		if(minSize.x < wordSizeX)
			minSize.x = wordSizeX;
		
		return minSize;
	}
	
	sf::Vector2f Resizer::getNormalSize() {
		return getMinSize();
	}
	
	Resizer* Resizer::copy() {
		return new Resizer(lineSpacing, align);
	}
	
	bool DecodePointer<Resizer>::decodePointer(const YAML::Node& node, Resizer*& resizer) {
		resizer = new Resizer{
			convDef(node["line-spacing"], 1.15f),
			convDef(node["align"], BaseResizer::Align::Left),
			convDef(node["algorithm"], BaseResizer::Algorithm::Base)
		};
		return true;
	}
}