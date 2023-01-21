#include "resizer.hpp"

namespace ui {
    Resizer::Resizer(float lineSpacing, Align align, Algorithm algorithm) : BaseResizer{lineSpacing, align, algorithm}{}

    void Resizer::move(sf::Vector2f position) {
        startRender += position;
        endRender += position;

        for (BaseCharacter*& character : *characters) {
            character->move(position);
        }

        for (BaseLine*& line : *lines) {
            line->move(position);
        }
    }

    void Resizer::setPosition(sf::Vector2f position) {
        sf::Vector2f offset{position - startRender};
        for (BaseCharacter*& character : *characters) {
            character->move({offset});
        }

        for (BaseLine*& line : *lines) {
            line->move(offset);
        }

        endRender += offset;
        startRender = position;
    }

    void Resizer::printCharacter(BaseCharacter *character, float kerning) {
        character->setPosition(nextPosition);
        nextPosition.x += character->getAdvance() + kerning;
        distanceEnter++;
    }

    float Resizer::equalize(uint i) {
        if (i > 0){
            float lineSize = 0;
            for (int j = i - distanceEnter; j < i; ++j) {
                float characterSize = (*characters)[j]->getHeight();
                if (lineSize < characterSize)
                    lineSize = characterSize;
            }
            sf::Vector2f offset{endRender.x - ((*characters)[i - 1]->getPosition().x), lineSize};
/*
            if ((*characters)[i - 1]->isSpecial() != BaseCharacter::Special::space)
                offset.x -= (*characters)[i - 1]->getAdvance();
*/

            switch (align) {
                case Align::left:
                    offset.x = 0;
                    break;
                case Align::center:
                    offset.x /= 2;
                    break;
            }

            for (uint j = i - distanceEnter; j < i; ++j) {
                (*characters)[j]->move(offset);
            }

            std::vector<BaseLine *> *oldLine = nullptr;
            float startLine = 0;
            for (uint j = i - distanceEnter; j < i; ++j) {
                BaseCharacter* character = (*characters)[j];
                std::vector<BaseLine *> &characterLine = character->getLine();
                sf::Vector2f characterPos = character->getPosition();
                if (oldLine != &characterLine) {
                    if (oldLine) {
                        for (BaseLine *&line: *oldLine) {
                            BaseLine *copyLine = line->copy();
                            copyLine->resize(startLine, characterPos.x, characterPos.y);
                            this->lines->push_back(copyLine);
                        }
                    }

                    oldLine = &characterLine;
                    startLine = characterPos.x;
                }
            }

            if (oldLine) {
                BaseCharacter* character = (*characters)[i - ((characters->size() == i || (*characters)[i]->isEnter() || i == 1) ? 1 : 2)];
                sf::Vector2f characterPos = character->getPosition();
                characterPos.x += character->getAdvance();

                for (BaseLine *&line: *oldLine) {
                    BaseLine *copyLine = line->copy();
                    copyLine->resize(startLine, characterPos.x, characterPos.y);
                    this->lines->push_back(copyLine);
                }
            }
            return lineSize;
        }
        return 0;
    }

    void Resizer::porting(int i) {
        float lineSize = equalize(i);
        nextPosition.y += lineSize * lineSpacing;
        nextPosition.x = startRender.x;

        distanceEnter = 0;
    }

    void Resizer::autoPorting(int i) {

        distanceEnter -= distanceSpace;
        porting(i - distanceSpace);

        for (uint j = i - distanceSpace; j < i; ++j) {
            float kerning;
            if (j < i - 1)
                kerning = (*characters)[j]->getKerning((*characters)[j + 1]->getChar());
            printCharacter((*characters)[j], kerning);
        }

        distanceEnter = distanceSpace;
        distanceSpace = 0;
    }

	void Resizer::deleteOldCash(sf::Vector2f size, sf::Vector2f position) {
		for (BaseLine*& line : *lines) {
			delete line;
		}
		lines->clear();

		startRender = position;
		endRender = position + size;
		this->nextPosition = startRender;
	}

	void Resizer::characterResize(BaseCharacter *character, float kerning) {
		printCharacter(character, kerning);
		distanceSpace++;
	}

	void Resizer::spaceResize(BaseCharacter *character, float kerning, int i) {
		if (this->nextPosition.x + (algorithm == BaseResizer::Algorithm::console ? character->getAdvance() : 0) <= endRender.x){
			printCharacter(character, kerning);
			distanceSpace = 0;
		} else{
			autoPorting(i);
			printCharacter(character, kerning);
		}
	}

	void Resizer::enterResize(int i) {
		if (this->nextPosition.x > endRender.x)
			autoPorting(i);
		porting(i);
	}

	void Resizer::fullObjectResize(BaseCharacter *character, int i) {
		enterResize(i);
		character->resize(nextPosition, endRender.x);
		nextPosition.y += lineSpacing + character->getHeight();
	}

	void Resizer::deleteCash() {
		distanceEnter = 0;
		distanceSpace = 0;
	}

	void Resizer::endLineEqualize() {
		if (endRender.x < this->nextPosition.x){
			autoPorting(characters->size());
		}
		equalize((*characters).size());
	}

    void Resizer::resize(sf::Vector2f size, sf::Vector2f position) {
	    if(size.x == endRender.x - startRender.x){
		    setPosition(position);
		    return;
	    }

		deleteOldCash(size, position);

        for (int i = 0; i < (*characters).size(); i++) {
            BaseCharacter* character = (*characters)[i];

            float kerning{(i != (*characters).size() - 1) ? character->getKerning((*characters)[i + 1]->getChar()) : 0};

            switch (character->isSpecial()) {
                case BaseCharacter::Special::no:
					if (algorithm == BaseResizer::Algorithm::console)
						spaceResize(character, kerning, i);
					else
	                    characterResize(character, kerning);
                    break;
                case BaseCharacter::Special::space:
	                if (algorithm == BaseResizer::Algorithm::absolute)
		                characterResize(character, kerning);
	                else
		                spaceResize(character, kerning, i);
                    break;
                case BaseCharacter::Special::enter:
	                enterResize(i);
                    break;
	            case BaseCharacter::Special::fullLine:
		            fullObjectResize(character, i);
		            break;
            }
        }

	    endLineEqualize();

        deleteCash();
    }

	sf::Vector2f Resizer::getPosition() {
		return startRender;
	}

	sf::Vector2f Resizer::getSize() {
		std::vector<BaseCharacter *>::iterator maxX{
			std::max_element(characters->begin(), characters->end(), [](BaseCharacter* elem,  BaseCharacter* elem2){return elem->getPosition().x < elem2->getPosition().x;})
		};

		std::vector<BaseCharacter *>::iterator maxY{
			std::max_element(characters->begin(), characters->end(), [](BaseCharacter* elem,  BaseCharacter* elem2){return elem->getPosition().y < elem2->getPosition().y;})
		};

		return sf::Vector2f{(*maxX)->getPosition().x, (*maxY)->getPosition().y + (*maxY)->getHeight()} - getPosition();
	}

    sf::Vector2f Resizer::getMinSize() {
	    sf::Vector2f minSize = {0, 0};

	    if (algorithm == BaseResizer::Algorithm::console){
			float advance = 0;
		    for (BaseCharacter *character : *characters) {
				advance = character->getAdvance();
				if (advance > minSize.x) minSize.x = advance;
			}
		    return minSize;
		}

        float wordSizeX = 0;

        for (BaseCharacter *character : *characters) {
            if ((algorithm == BaseResizer::Algorithm::base     && (character->isSpecial() == BaseCharacter::Special::no)) ||
	            (algorithm == BaseResizer::Algorithm::absolute && (character->isSpecial() != BaseCharacter::Special::enter))){
                wordSizeX += character->getAdvance();
            }else{
                if (minSize.x < wordSizeX)
                    minSize.x = wordSizeX;
                wordSizeX = 0;
            }
        }
        if (minSize.x < wordSizeX)
            minSize.x = wordSizeX;

        return minSize;
    }

    sf::Vector2f Resizer::getNormalSize() {
        return getMinSize();
    }

    Resizer *Resizer::copy() {
        return new Resizer(lineSpacing, align);
    }

	bool convertPointer(const YAML::Node &node, Resizer *&resizer) {
        resizer = new Resizer{
			convDef(node["line-spacing"], 1.15f),
			convDef(node["align"], BaseResizer::Align::left),
			convDef(node["algorithm"], BaseResizer::Algorithm::base)
		};
		return true;
    }
}