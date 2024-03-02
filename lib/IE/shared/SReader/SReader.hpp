#pragma once

#include <functional>
#include "IE/shared/ISReadable/ISReadable.hpp"

namespace ie {
	template<typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
	class SReader {
	public:
		using T = typename Value_::T;
		using ReadFn = typename ISReadable<typename Value_::T>::ReadFn;
		
		SReader(Value_& readable, ReadFn&& read_fn);
		
		SReader(SReader const& other);
		
		SReader(SReader&& other);
		
		auto get() const -> Value_&;
		
		~SReader();
	
	private:
		Value_* readable_;
		ReadFn* read_fn_;
	};
}

#include "SReader.inl"
