#pragma once

#include <IE/ieml/ieml-rttb/ieml-rttb.hpp>
#include <box-ptr/BoxPtr.hpp>
#include "../SInitInfo/SInitInfo.hpp"

namespace ie {
	namespace fs = std::filesystem;
	
	template<typename Type_>
	class MakeDyn;
	
	class DynBuffer {
	public:
		DynBuffer() = default;
		
		DynBuffer(DynBuffer&& other) = default;
		
		template<typename T>
		static auto add(MakeDyn<T> make_dyn, SInitInfo init_info) -> bool;
		
		template<typename T>
		static auto get(MakeDyn<T> make_dyn, SInitInfo init_info) -> T&;
	
	private:
		absl::flat_hash_map<size_t, rttb::Dyn> indexed_;
		std::vector<rttb::Dyn> non_indexed_;
	};
	
	template<typename Type_>
	class MakeDyn {
	public:
		using MakeType = typename Type_::Make;
		
		MakeDyn(bp::BoxPtr<MakeType> make);
		
		MakeDyn(Type_& ref);
		
		auto make(SInitInfo init_info) -> Type_&;
		
		static auto decode(ieml::Node const& node) -> orl::Option<MakeDyn<Type_> >;
		
		friend DynBuffer;
	
	private:
		MakeDyn(size_t id, bp::BoxPtr<MakeType> make);
		
		struct Pair {
			size_t id_;
			bp::BoxPtr<MakeType> make_;
			
			Pair(size_t id_, bp::BoxPtr<MakeType> make_);
			
			Pair(Pair const&) = delete;
			
			Pair(Pair&&) = default;
		};
		
		std::variant<Pair, std::reference_wrapper<Type_> > data_;
	};
}

template<typename Type_>
struct tnl::TypeName<ie::MakeDyn<Type_> > {
	static auto type_name() -> StringView;
};

template<typename Type_>
struct ieml::Decode<char, ie::MakeDyn<Type_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::MakeDyn<Type_> >;
};

#include "DynBuffer.inl"
