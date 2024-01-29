#include "IE/component/IComponent/Text/Text.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ie {
	template<typename T>
	BasicTextCopyAction<T>::Make::Make(T&& clipboard) : clipboard(clipboard) {
	}
	
	template<typename T>
	BasicTextCopyAction<T>* BasicTextCopyAction<T>::Make::make(BasicActionInitInfo<Text&> init_info) {
		return new BasicTextCopyAction{std::move(*this), init_info};
	}
	
	template<typename T>
	BasicTextCopyAction<T>::BasicTextCopyAction(Make&& make, BasicActionInitInfo<Text&> init_info) :
		text(&init_info.additional), clipboard(make.clipboard) {
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
		ProcessClipboard<T>::set_string(clipboard, to_utf32(text->get_selection_text()));
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
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<TextCopyAction>::decode_pointer(const YAML::Node&, TextCopyAction*& text_copy_action) {
		text_copy_action = new TextCopyAction{};
		return true;
	}
	*/
}