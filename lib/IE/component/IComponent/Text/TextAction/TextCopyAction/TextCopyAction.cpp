#include <codecvt>
#include "TextCopyAction.hpp"
#include "IE/component/IComponent/Text/Text.hpp"
#include "IE/modules/yaml-cpp/file-buffer/FileBuffer.hpp"

namespace ie {
	TextCopyAction* TextCopyAction::Make::make(BasicActionInitInfo<Text&> init_info) {
		return new TextCopyAction{std::move(*this), init_info};
	}
	
	TextCopyAction::TextCopyAction(Make&&, BasicActionInitInfo<Text&> init_info) : text(&init_info.additional) {
	
	}
	
	TextCopyAction::TextCopyAction() : text(nullptr) {
	}
	
	void TextCopyAction::init(BasicActionInitInfo<Text&> init_info) {
		text = &init_info.additional;
	}
	
	void TextCopyAction::start_pressed() {
		sf::Clipboard::setString(u32string_to_uint32_string(text->get_selection_text()));
	}
	
	void TextCopyAction::stop_pressed() {
	}
	
	void TextCopyAction::while_pressed() {
	}
	
	void TextCopyAction::while_not_pressed() {
	}
	
	TextCopyAction* TextCopyAction::copy() {
		return new TextCopyAction{*this};
	}
	
	bool DecodePointer<TextCopyAction>::decode_pointer(const YAML::Node&, TextCopyAction*& text_copy_action) {
		text_copy_action = new TextCopyAction{};
		return true;
	}
}