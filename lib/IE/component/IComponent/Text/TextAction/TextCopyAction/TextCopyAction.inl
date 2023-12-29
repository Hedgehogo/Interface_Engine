#include "IE/component/IComponent/Text/Text.hpp"
#include "IE/modules/yaml-cpp/file-buffer/FileBuffer.hpp"

namespace ie {
	void ProcessClipboard<sf::Clipboard>::set_string(sf::Clipboard&, std::u32string str) {
		sf::Clipboard::setString(u32string_to_uint32_string(std::move(str)));
	}
	
	std::u32string ProcessClipboard<sf::Clipboard>::get_string(sf::Clipboard&) {
		return uint32_to_u32string_string(sf::Clipboard::getString().toUtf32());
	}
	
	template<typename T>
	BasicTextCopyAction<T>::Make::Make(T&& clipboard) : clipboard(clipboard){
	}
	
	template<typename T>
	BasicTextCopyAction<T>* BasicTextCopyAction<T>::Make::make(BasicActionInitInfo<Text&> init_info) {
		return new BasicTextCopyAction{std::move(*this), init_info};
	}
	
	template<typename T>
	BasicTextCopyAction<T>::BasicTextCopyAction(Make&& make, BasicActionInitInfo<Text&> init_info) : text(&init_info.additional), clipboard(make.clipboard) {
	
	}
	
	template<typename T>
	BasicTextCopyAction<T>::BasicTextCopyAction(T&& clipboard) : text(nullptr), clipboard(clipboard) {
	}
	
	template<typename T>
	void BasicTextCopyAction<T>::init(BasicActionInitInfo<Text&> init_info) {
		text = &init_info.additional;
	}
	
	template<typename T>
	void BasicTextCopyAction<T>::start_pressed() {
	}
	
	template<typename T>
	void BasicTextCopyAction<T>::stop_pressed() {
		ProcessClipboard<T>::set_string(clipboard, text->get_selection_text());
	}
	
	template<typename T>
	void BasicTextCopyAction<T>::while_pressed() {
	}
	
	template<typename T>
	void BasicTextCopyAction<T>::while_not_pressed() {
	}
	
	template<typename T>
	BasicTextCopyAction<T>* BasicTextCopyAction<T>::copy() {
		return new BasicTextCopyAction{*this};
	}
	
	bool DecodePointer<TextCopyAction>::decode_pointer(const YAML::Node&, TextCopyAction*& text_copy_action) {
		text_copy_action = new TextCopyAction{};
		return true;
	}
}