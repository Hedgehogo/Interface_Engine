#include "IE/component/IComponent/Text/Text.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ie {
	namespace make_system{
		template<typename T>
		BasicTextCopyAction<T>::BasicTextCopyAction(bp::BoxPtr<T>&& clipboard) : clipboard(clipboard) {
		}
		
		template<typename T>
		ie::BasicTextCopyAction<T>* BasicTextCopyAction<T>::make(BasicActionInitInfo<Text&> init_info) {
			return new ie::BasicTextCopyAction{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicTextCopyAction<T>::BasicTextCopyAction(Make&& make, BasicActionInitInfo<Text&> init_info) :
		text(&init_info.additional), clipboard(make.clipboard) {
	}
	
	template<typename T>
	void BasicTextCopyAction<T>::start_pressed() {
	}
	
	template<typename T>
	void BasicTextCopyAction<T>::stop_pressed() {
		ProcessClipboard<T>::set_string(*clipboard.get(), text->get_selection_text());
	}
	
	template<typename T>
	void BasicTextCopyAction<T>::while_pressed() {
	}
	
	template<typename T>
	void BasicTextCopyAction<T>::while_not_pressed() {
	}
}

template<typename T>
orl::Option<ie::make_system::BasicTextCopyAction<T>> ieml::Decode<char, ie::make_system::BasicTextCopyAction<T>>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicTextCopyAction<T>{
		map.get_as<bp::BoxPtr<T>>("clipboard").ok_or({}),
	};
}
