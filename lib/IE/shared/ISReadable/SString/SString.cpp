#include "SString.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"

namespace ie::make_system {
	SString::SString(std::u32string data) : data(std::move(data)) {
	}
	
	auto SString::make(SInitInfo init_info) -> rttb::Dyn {
		return rttb::Dyn{ie::SString{std::move(*this), init_info}};
	}
	
	SMString::ToMutable(std::u32string data) : SString(std::move(data)) {
	}
	
	auto SMString::make(SInitInfo init_info) -> rttb::Dyn {
		return rttb::Dyn{ie::SMString{std::move(*this), init_info}};
	}
}

auto ieml::Decode<char, ie::make_system::SString>::decode(const ieml::Node& node) -> orl::Option<ie::make_system::SString> {
	auto& clear_node{node.get_clear()};
	if(clear_node.is_null()) {
		return {{}};
	}
	return {{ie::to_utf32(clear_node.as<ie::ParseString>().except().str)}};
}

auto ieml::Decode<char, ie::make_system::SMString>::decode(const ieml::Node& node) -> orl::Option<ie::make_system::SMString> {
	return ieml::Decode<char, ie::make_system::SString>::decode(node).map([](auto&& value) {
		return ie::make_system::SMString{std::move(value.data)};
	});
}

namespace ie {
	SString::SString(Make&& make, SInitInfo init_info) : data_(std::move(make.data)) {
	}
	
	SString::SString(std::u32string data) : data_(std::move(data)) {
	}
	
	auto SString::get() const -> std::u32string {
		return data_;
	}
	
	auto SString::add_read_fn(SString::ReadFn&& read_fn) -> ReadFn& {
		return read_fns_.emplace_back(std::move(read_fn));
	}
	
	auto SString::delete_read_fn(SString::ReadFn& read_fn) -> bool {
		auto result{std::find_if(read_fns_.cbegin(), read_fns_.cend(), [&](ReadFn const& item) {
			return &item == &read_fn;
		})};
		if(result != read_fns_.cend()) {
			read_fns_.erase(result);
			return true;
		}
		return false;
	}
	
	SMString::ToMutable(Make&& make, SInitInfo init_info) : SString(std::move(make.data)) {
	}

	SMString::ToMutable(std::u32string data) : SString(std::move(data)) {
	}
	
	auto ToMutable<SString>::set(std::u32string value) -> void {
		data_ = std::move(value);
		for(auto& read_fn : this->read_fns_) {
			read_fn(this->data_);
		}
	}

	auto Determine<SMString::Make>::determine(const ieml::Node& node) -> bool {
		return node.is_string();
	}
}
