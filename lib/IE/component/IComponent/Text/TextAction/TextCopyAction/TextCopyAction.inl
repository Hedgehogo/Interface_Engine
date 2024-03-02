#include "IE/component/IComponent/Text/Text.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ie {
	namespace make_system{
		template<typename T>
		BasicTextCopyAction<T>::BasicTextCopyAction(bp::BoxPtr<T>&& clipboard) : clipboard(clipboard) {
		}
		
		template<typename T>
		auto BasicTextCopyAction<T>::make(BasicActionInitInfo<Text&> init_info) -> ie::BasicTextCopyAction<T>* {
			return new ie::BasicTextCopyAction{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicTextCopyAction<T>::BasicTextCopyAction(Make&& make, BasicActionInitInfo<Text&> init_info) :
		text_(&init_info.additional), clipboard_(make.clipboard) {
	}
	
	template<typename T>
	auto BasicTextCopyAction<T>::start_pressed() -> void {
	}
	
	template<typename T>
	auto BasicTextCopyAction<T>::stop_pressed() -> void {
		ProcessClipboard<T>::set_string(*clipboard_.get(), text_->get_selection_text());
	}
	
	template<typename T>
	auto BasicTextCopyAction<T>::while_pressed() -> void {
	}
	
	template<typename T>
	auto BasicTextCopyAction<T>::while_not_pressed() -> void {
	}
}

template<typename T>
auto ieml::Decode<char, ie::make_system::BasicTextCopyAction<T> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicTextCopyAction<T> > {
	auto const& clear_node{node.get_clear()};
	for(auto& map: clear_node.get_map_view().ok_or_none()) {
		return {{map.get_as<bp::BoxPtr<T> >("clipboard").except().ok_or({})}};
	}
	if (clear_node.is_null()){
		return ie::make_system::BasicTextCopyAction<T>{};
	}
	return {};
}
