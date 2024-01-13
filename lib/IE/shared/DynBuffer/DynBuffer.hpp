#pragma once

#include <IE/ieml/ieml-rttb/ieml-rttb.hpp>
#include <box-ptr/BoxPtr.hpp>

namespace ie {
	namespace fs = std::filesystem;
	
	template<typename Type_>
	class MakeDyn;
	
	class DynBuffer {
	public:
		DynBuffer() = default;
		
		DynBuffer(DynBuffer&& other) = default;
		
		template<typename T>
		bool add(MakeDyn<T> make_dyn);
		
		template<typename T>
		T& get(MakeDyn<T> make_dyn);
	
	private:
		absl::flat_hash_map<size_t, rttb::Dyn> indexed_;
		std::vector<rttb::Dyn> non_indexed_;
	};
	
	template<typename Type_>
	class MakeDyn {
	public:
		using MakeType = typename Type_::Make;
		
		MakeDyn(Type_& ref);
		
		MakeDyn(bp::BoxPtr<MakeType> make);
		
		Type_& make(DynBuffer& dyn_buffer);
		
		static orl::Option<MakeDyn<Type_> > decode(ieml::Node const& node);
		
		friend DynBuffer;
	
	private:
		MakeDyn(size_t id, bp::BoxPtr<MakeType> make);
		
		struct Pair {
			size_t id_;
			bp::BoxPtr<MakeType> make_;
		};
		
		std::variant<Pair, std::reference_wrapper<Type_> > data_;
	};
}

#include "DynBuffer.inl"
