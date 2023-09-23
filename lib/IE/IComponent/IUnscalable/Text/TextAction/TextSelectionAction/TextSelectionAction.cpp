#include "TextSelectionAction.hpp"

#include "IE/IComponent/IUnscalable/Text/Text.hpp"

#include <cmath>

namespace ie {
	TextSelectionAction* TextSelectionAction::Make::make(BasicActionInitInfo<Text&> initInfo) {
		return new TextSelectionAction{std::move(*this), initInfo};
	}
	
	TextSelectionAction::TextSelectionAction(TextSelectionAction::Make&& make, BasicActionInitInfo<Text&> initInfo) : text(&initInfo.additional), start(), end() {
	}
	
	TextSelectionAction::TextSelectionAction() : text(nullptr), start(), end() {
	}
	
	void TextSelectionAction::init(BasicActionInitInfo<Text&> initInfo) {
		text = &initInfo.additional;
	}
	
	void TextSelectionAction::startPressed() {
		text->setSelectionStart(start = text->getCharacter(sf::Vector2f{mousePosition}));
	}
	
	void TextSelectionAction::stopPressed() {
	}
	
	void TextSelectionAction::whilePressed() {
		text->setSelectionEnd(end = text->getCharacter(sf::Vector2f{mousePosition}));
		if(start != nullBaseCharacterIterator && end != nullBaseCharacterIterator) {
			auto localStart = start, localEnd = end;
			
			if(start > end)
				std::swap(localStart, localEnd);
			
			for(auto iterator = localStart; iterator != localEnd; ++iterator) {
				(*iterator)->setSelection(true);
				(*iterator)->setActive(true);
			}
		}
	}
	
	void TextSelectionAction::whileNotPressed() {
	}
	
	std::vector<BaseCharacter*>::iterator TextSelectionAction::getStart() {
		return start;
	}
	
	std::vector<BaseCharacter*>::iterator TextSelectionAction::getEnd() {
		return end;
	}
	
	void TextSelectionAction::update(sf::Vector2i mousePosition, bool press) {
		if(press && start != nullBaseCharacterIterator && end != nullBaseCharacterIterator) {
			auto localStart = start, localEnd = end;
			
			if(start > end)
				std::swap(localStart, localEnd);
			
			for(auto iterator = localStart; iterator != localEnd; ++iterator) {
				(*iterator)->setSelection(false);
			}
		}
		BasicBaseKeyAction<Text&>::update(mousePosition, press);
	}
	
	TextSelectionAction* TextSelectionAction::copy() {
		return new TextSelectionAction{*this};
	}
	
	bool DecodePointer<TextSelectionAction>::decodePointer(const YAML::Node&, TextSelectionAction*& textSelectionAction) {
		textSelectionAction = new TextSelectionAction{};
		return true;
	}
}