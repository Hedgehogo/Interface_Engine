#pragma once

#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "../ISReadable.hpp"
#include "../../SInitInfo/SInitInfo.hpp"

namespace ie {
	namespace make_system {
		template<typename T_, bool Default_ = std::is_default_constructible_v<T_> >
		struct SReadable;
		
		template<typename T_>
		struct SReadable<T_, true> : public virtual ISReadable<T_> {
		public:
			T_ data;
			
			SReadable(T_ data = {});
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename T_>
		struct SReadable<T_, false> : public virtual ISReadable<T_> {
		public:
			T_ data;
			
			SReadable(T_ data);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename T_>
		struct ToMutable<SReadable<T_, true> > : public SReadable<T_>, public virtual ISMutable<T_> {
		public:
			ToMutable(T_ data = {});
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename T_>
		struct ToMutable<SReadable<T_, false> > : public SReadable<T_>, public virtual ISMutable<T_> {
		public:
			ToMutable(T_ data);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename T_, bool Default_ = std::is_default_constructible_v<T_> >
		using SMutable = ToMutable<SReadable<T_, Default_> >;
	}
}

template<typename T_>
struct ieml::Decode<char, ie::make_system::SReadable<T_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::SReadable<T_> >;
};

template<typename T_>
struct ieml::Decode<char, ie::make_system::SMutable<T_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::SMutable<T_> >;
};

namespace ie {
	template<typename T_>
	class SReadable : public virtual ISReadable<T_> {
	public:
		using T = typename ISReadable<T_>::T;
		using ReadFn = typename SReadable<T_>::ReadFn;
		using Make = make_system::SReadable<T_>;
		
		SReadable(Make&& make, SInitInfo init_info);
		
		SReadable(T_ data);
		
		auto get() const -> T_ override;
		
	protected:
		auto add_read_fn(ReadFn&& read_fn) -> ReadFn& override;
		
		auto delete_read_fn(ReadFn& read_fn) -> bool override;
		
		T_ data_;
		std::vector<ReadFn> read_fns_;
	};
	
	using SBool = SReadable<bool>;
	using SFloat = SReadable<float>;
	using SInt = SReadable<int>;
	using SSize = SReadable<size_t>;
	
	template<typename T_>
	class ToMutable<SReadable<T_> > : public SReadable<T_>, public virtual ISMutable<T_> {
	public:
		using T = typename SReadable<T_>::T;
		using ReadFn = typename ISMutable<T_>::ReadFn;
		using Make = make_system::SMutable<T_>;
		
		ToMutable(Make&& make, SInitInfo);
		
		ToMutable(T_ data);
		
		auto set(T_ value) -> void override;
	};
	
	template<typename T_>
	using SMutable = ToMutable<SReadable<T_> >;
	
	using SMBool = SMutable<bool>;
	using SMFloat = SMutable<float>;
	using SMInt = SMutable<int>;
	using SMSize = SMutable<size_t>;
	
	template<>
	struct Determine<SMBool::Make> {
		static auto determine(ieml::Node const& node) -> bool;
	};
}

#include "SReadable.inl"
