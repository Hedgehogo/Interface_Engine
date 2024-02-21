#pragma once

#include <box-ptr/BoxPtr.hpp>
#include <IEML/node.hpp>
#include "IE/ieml/ieml-rttb/ieml-rttb.hpp"
#include "LoadString/LoadString.hpp"

namespace ieml {
	template<typename T>
	struct Decode<char, bp::BoxPtr<T> > {
		static orl::Option<bp::BoxPtr<T> > decode(ieml::Node const& node);
	};
	
	template<typename T>
	struct Decode<char, orl::Option<T> > {
		static orl::Option<orl::Option<T> > decode(ieml::Node const& node);
	};
	
	template<typename T>
	struct Decode<char, std::vector<T> > {
		static orl::Option<std::vector<T> > decode(ieml::Node const& node);
	};
	
	template<typename T>
	struct Decode<char, absl::flat_hash_map<std::string, T> > {
		static orl::Option<absl::flat_hash_map<std::string, T> > decode(ieml::Node const& node);
	};
	
	template<>
	struct Decode<char, ie::LoadString> {
		static orl::Option<ie::LoadString> decode(ieml::Node const& node);
	};
}

#include "ieml-basic.inl"
