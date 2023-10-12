#include <codecvt>
#include "TextCopyAction.hpp"
#include "IE/component/IComponent/Text/Text.hpp"
#include "IE/Modules/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ie {
	TextCopyAction* TextCopyAction::Make::make(BasicActionInitInfo<Text&> initInfo) {
		return new TextCopyAction{std::move(*this), initInfo};
	}
	
	TextCopyAction::TextCopyAction(Make&&, BasicActionInitInfo<Text&> initInfo) : text(&initInfo.additional) {
	
	}
	
	TextCopyAction::TextCopyAction() : text(nullptr) {
	}
	
	void TextCopyAction::init(BasicActionInitInfo<Text&> initInfo) {
		text = &initInfo.additional;
	}
	
	void TextCopyAction::startPressed() {
		sf::Clipboard::setString(u32stringToUint32String(text->getSelectionText()));
	}
	
	void TextCopyAction::stopPressed() {
	}
	
	void TextCopyAction::whilePressed() {
	}
	
	void TextCopyAction::whileNotPressed() {
	}
	
	TextCopyAction* TextCopyAction::copy() {
		return new TextCopyAction{*this};
	}
	
	bool DecodePointer<TextCopyAction>::decodePointer(const YAML::Node&, TextCopyAction*& textCopyAction) {
		textCopyAction = new TextCopyAction{};
		return true;
	}
}