#pragma once

#include "../ISRanged.hpp"
#include "../../SReadable/SReadable.hpp"

namespace ie {
	template<typename T_>
	class SRanged;
	
	namespace make_system {
		template<typename T_>
		struct SRanged : public SReadable<T_>, public virtual ISRanged<T_> {
		public:
			SRanged(T_ data);
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
		
		template<typename T_>
		struct ToMutable<SRanged<T_> > : public SRanged<T_>, public virtual ISMRanged<T_> {
		public:
			ToMutable(T_ data);
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
		
		template<typename T_>
		using SMRanged = ToMutable<SRanged<T_> >;
	}
}

template<typename T_>
struct ieml::Decode<char, ie::make_system::SRanged<T_> > {
	static orl::Option<ie::make_system::SRanged<T_> > decode(ieml::Node const& node);
};

template<typename T_>
struct ieml::Decode<char, ie::make_system::SMRanged<T_> > {
	static orl::Option<ie::make_system::SMRanged<T_> > decode(ieml::Node const& node);
};

namespace ie {
	template<typename T_>
	class SRanged : public SReadable<T_>, public virtual ISRanged<T_> {
	public:
		using T = typename SReadable<T_>::T;
		using ReadFn = typename SReadable<T_>::ReadFn;
		using Make = make_system::SRanged<T_>;
		
		SRanged(Make&& make, DynBuffer& dyn_buffer);
		
		SRanged(T_ data);
		
		T_ get_upper_bound() override;
		
		T_ get_lower_bound() override;
		
		void set_upper_bound(T_ upper_bound) override;
		
		void set_lower_bound(T_ lower_bound) override;
		
		void set_bounds(T_ lower_bound, T_ upper_bound) override;
	
	protected:
		void reset();
		
		void set(T_ value);
		
		T_ upper_bound_;
		T_ lower_bound_;
	};
	
	using SRFloat = SRanged<float>;
	using SRInt = SRanged<int>;
	using SRSize = SRanged<size_t>;
	
	template<typename T_>
	class ToMutable<SRanged<T_> > : public SRanged<T_>, public virtual ISMRanged<T_> {
	public:
		using T = typename SRanged<T_>::T;
		using ReadFn = typename SRanged<T_>::ReadFn;
		using Make = make_system::SMRanged<T_>;
		
		ToMutable(Make&& make, DynBuffer& dyn_buffer);
		
		ToMutable(T_ data);
		
		void set(T_ value) override;
	};
	
	template<typename T_>
	using SMRanged = ToMutable<SRanged<T_> >;
	
	using SMRFloat = SMRanged<float>;
	using SMRInt = SMRanged<int>;
	using SMRSize = SMRanged<size_t>;
	
	template<typename T_>
	struct Determine<make_system::SMRanged<T_> > {
		static bool determine(ieml::Node const& node);
	};
}

#include "SRanged.inl"
