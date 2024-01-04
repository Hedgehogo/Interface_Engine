#include <codecvt>
#include "TextCopyAction.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"
#include "IE/component/IComponent/Text/Text.hpp"

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
		sf::Clipboard::setString(to_utf32(text->get_selection_text()));
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
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<TextCopyAction>::decode_pointer(const YAML::Node&, TextCopyAction*& text_copy_action) {
		text_copy_action = new TextCopyAction{};
		return true;
	}
	*/
}