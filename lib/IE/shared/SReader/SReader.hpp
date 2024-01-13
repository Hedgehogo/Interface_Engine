#pragma once

#include <functional>
#include "../ISValue/ISValue.hpp"
#include "../ISRanged/ISRanged.hpp"

namespace ie {
	template<typename Value_, typename = std::enable_if_t<is_shared<Value_> > >
	class SReader {
	public:
		using T = typename Value_::T;
		using ReadFn = typename ISValue<typename Value_::T>::ReadFn;
		
		SReader(Value_& readable, ReadFn&& read_fn);
		
		SReader(SReader const& other);
		
		SReader(SReader&& other);
		
		Value_& get() const;
		
		~SReader();
	
	private:
		Value_* readable_;
		ReadFn* read_fn_;
	};
}

#include "SReader.inl"
