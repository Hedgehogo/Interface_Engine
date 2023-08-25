#include <codecvt>
#include "TextCopyEvent.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/Text.hpp"
#include "modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
	TextCopyEvent::TextCopyEvent() : text(nullptr) {
	}
	
	void TextCopyEvent::init(TextInteractionInitInfo initInfo) {
		text = &initInfo.additional;
	}
	
	void TextCopyEvent::startPressed() {
		sf::Clipboard::setString(u32stringToUint32String(text->getSelectionText()));
	}
	
	void TextCopyEvent::stopPressed() {
	}
	
	void TextCopyEvent::whilePressed() {
	}
	
	void TextCopyEvent::whileNotPressed() {
	}
	
	TextCopyEvent* TextCopyEvent::copy() {
		return new TextCopyEvent{*this};
	}
	
	bool DecodePointer<TextCopyEvent>::decodePointer(const YAML::Node&, TextCopyEvent*& textCopyEvent) {
		textCopyEvent = new TextCopyEvent{};
		return true;
	}
}