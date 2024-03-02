#pragma once

#include "../ISRanged.hpp"
#include "../../SReadable/SReadable.hpp"

namespace ie {
	namespace make_system {
		template<typename T_, bool Default_ = std::is_default_constructible_v<T_> >
		struct SRanged;
		
		template<typename T_>
		struct SRanged<T_, true> : public SReadable<T_>, public virtual ISRanged<T_> {
		public:
			SRanged(T_ data = {});
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename T_>
		struct SRanged<T_, false> : public SReadable<T_>, public virtual ISRanged<T_> {
		public:
			SRanged(T_ data);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename T_>
		struct ToMutable<SRanged<T_, true> > : public SRanged<T_>, public virtual ISMRanged<T_> {
		public:
			ToMutable(T_ data = {});
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename T_>
		struct ToMutable<SRanged<T_, false> > : public SRanged<T_>, public virtual ISMRanged<T_> {
		public:
			ToMutable(T_ data);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename T_, bool Default_ = std::is_default_constructible_v<T_> >
		using SMRanged = ToMutable<SRanged<T_, Default_> >;
	}
}

template<typename T_>
struct ieml::Decode<char, ie::make_system::SRanged<T_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::SRanged<T_> >;
};

template<typename T_>
struct ieml::Decode<char, ie::make_system::SMRanged<T_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::SMRanged<T_> >;
};

namespace ie {
	template<typename T_>
	class SRanged : public SReadable<T_>, public virtual ISRanged<T_> {
	public:
		using T = typename SReadable<T_>::T;
		using ReadFn = typename SReadable<T_>::ReadFn;
		using Make = make_system::SRanged<T_>;
		
		SRanged(Make&& make, SInitInfo init_info);
		
		SRanged(T_ data, T_ upper_bound_, T_ lower_bound_);
		
		SRanged(T_ data);
		
		auto get_upper_bound() const -> T_ override;
		
		auto get_lower_bound() const -> T_ override;
		
		auto set_upper_bound(T_ upper_bound) -> void override;
		
		auto set_lower_bound(T_ lower_bound) -> void override;
		
		auto set_bounds(T_ lower_bound, T_ upper_bound) -> void override;
	
	protected:
		auto reset() -> void;
		
		auto set(T_ value) -> void;
		
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
		
		ToMutable(Make&& make, SInitInfo init_info);
		
		ToMutable(T_ data);
		
		auto set(T_ value) -> void override;
	};
	
	template<typename T_>
	using SMRanged = ToMutable<SRanged<T_> >;
	
	using SMRFloat = SMRanged<float>;
	using SMRInt = SMRanged<int>;
	using SMRSize = SMRanged<size_t>;
	
	template<typename T_>
	struct Determine<make_system::SMRanged<T_> > {
		static auto determine(ieml::Node const& node) -> bool;
	};
}

#include "SRanged.inl"
