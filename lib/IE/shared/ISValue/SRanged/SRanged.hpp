#pragma once

#include "../../ISRanged/ISRanged.hpp"
#include "../SValue/SValue.hpp"

namespace ie {
	template<typename T_>
	class SRanged;
	
	namespace make_system {
		template<typename T_>
		struct SRanged : public SValue<T_>, public virtual ISRanged<T_> {
		public:
			SRanged(T_ data);
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
	}
}

template<typename T_>
struct ieml::Decode<char, ie::make_system::SRanged<T_> > {
	static orl::Option<ie::make_system::SRanged<T_> > decode(ieml::Node const& node);
};

namespace ie {
	template<typename T_>
	class SRanged : public SValue<T_>, public virtual ISRanged<T_> {
	public:
		using ReadFn = typename SValue<T_>::ReadFn;
		using Make = make_system::SRanged<T_>;
		
		SRanged(Make&& make, DynBuffer& dyn_buffer);
		
		SRanged(T_ data);
		
		void set(T_ value) override;
		
		T_ get_upper_bound() override;
		
		T_ get_lower_bound() override;
		
		void set_upper_bound(T_ upper_bound) override;
		
		void set_lower_bound(T_ lower_bound) override;
		
		void set_bounds(T_ lower_bound, T_ upper_bound) override;
	
	private:
		void reset();
	
	protected:
		T_ upper_bound_;
		T_ lower_bound_;
	};
	
	using SRFloat = SRanged<float>;
	using SRInt = SRanged<int>;
	using SRSize = SRanged<size_t>;
}

#include "SRanged.inl"