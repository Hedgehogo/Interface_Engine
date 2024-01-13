#pragma once

#include "../ISValue.hpp"

namespace ie {
	template<typename T_>
	class SValue;
	
	namespace make_system {
		template<typename T_>
		struct SValue : public virtual ISValue<T_> {
		public:
			T_ data;
		
			SValue(T_ data);
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
	}
}

template<typename T_>
struct ieml::Decode<char, ie::make_system::SValue<T_> > {
	static orl::Option<ie::make_system::SValue<T_> > decode(ieml::Node const& node);
};

namespace ie {
	template<typename T_>
	class SValue : public virtual ISValue<T_> {
	public:
		using ReadFn = typename ISValue<T_>::ReadFn;
		using Make = make_system::SValue<T_>;
		
		SValue(Make&& make, DynBuffer&);
		
		SValue(T_ data);
		
		T_ get() const override;
		
		void set(T_ value) override;
	
	protected:
		ReadFn& add_read_fn(ReadFn&& read_fn) override;
		
		bool delete_read_fn(ReadFn& read_fn) override;
		
		T_ data_;
		std::vector<ReadFn> read_fns_;
	};
	
	using SBool = SValue<bool>;
	using SFloat = SValue<float>;
	using SInt = SValue<int>;
	using SSize = SValue<size_t>;
}

#include "SValue.inl"
