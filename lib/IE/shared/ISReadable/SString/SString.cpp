#include "SString.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ie::make_system {
	SString::SString(std::u32string data) : data(std::move(data)) {
	}
	
	rttb::Dyn SString::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SString{std::move(*this), dyn_buffer}};
	}
	
	SMString::ToMutable(std::u32string data) : SString(std::move(data)) {
	}
	
	rttb::Dyn SMString::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SMString{std::move(*this), dyn_buffer}};
	}
}

orl::Option<ie::make_system::SString> ieml::Decode<char, ie::make_system::SString>::decode(const ieml::Node& node) {
	auto& clear_node{node.get_clear()};
	if(clear_node.is_null()) {
		return {{}};
	}
	return {{ie::to_utf32(clear_node.as<ie::LoadString>().except().str)}};
}

orl::Option<ie::make_system::SMString> ieml::Decode<char, ie::make_system::SMString>::decode(const ieml::Node& node) {
	return ieml::Decode<char, ie::make_system::SString>::decode(node).map([](auto&& value) {
		return ie::make_system::SMString{std::move(value.data)};
	});
}

namespace ie {
	SString::SString(Make&& make, ie::DynBuffer&) : data_(std::move(make.data)) {
	}
	
	SString::SString(std::u32string data) : data_(std::move(data)) {
	}
	
	std::u32string SString::get() const {
		return data_;
	}
	
	auto SString::add_read_fn(SString::ReadFn&& read_fn) -> ReadFn& {
		return read_fns_.emplace_back(std::move(read_fn));
	}
	
	bool SString::delete_read_fn(SString::ReadFn& read_fn) {
		auto result{std::find_if(read_fns_.cbegin(), read_fns_.cend(), [&](ReadFn const& item) {
			return &item == &read_fn;
		})};
		if(result != read_fns_.cend()) {
			read_fns_.erase(result);
			return true;
		}
		return false;
	}
	
	SMString::ToMutable(Make&& make, DynBuffer&) : SString(std::move(make.data)) {
	}

	SMString::ToMutable(std::u32string data) : SString(std::move(data)) {
	}
	
	void ToMutable<SString>::set(std::u32string value) {
		data_ = std::move(value);
	}

	bool Determine<SMString::Make>::determine(const ieml::Node& node) {
		return node.is_string();
	}
}
