#pragma once

#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "../ISReadable.hpp"

namespace ie {
	namespace make_system {
		template<typename T_>
		struct SReadable : public virtual ISReadable<T_> {
		public:
			T_ data;
			
			SReadable(T_ data);
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
		
		template<typename T_>
		struct ToMutable<SReadable<T_> > : public SReadable<T_>, public virtual ISMutable<T_> {
		public:
			ToMutable(T_ data);
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
		
		template<typename T_>
		using SMutable = ToMutable<SReadable<T_> >;
	}
}

template<typename T_>
struct ieml::Decode<char, ie::make_system::SReadable<T_> > {
	static orl::Option<ie::make_system::SReadable<T_> > decode(ieml::Node const& node);
};

template<typename T_>
struct ieml::Decode<char, ie::make_system::SMutable<T_> > {
	static orl::Option<ie::make_system::SMutable<T_> > decode(ieml::Node const& node);
};

namespace ie {
	template<typename T_>
	class SReadable : public virtual ISReadable<T_> {
	public:
		using T = typename ISReadable<T_>::T;
		using ReadFn = typename SReadable<T_>::ReadFn;
		using Make = make_system::SReadable<T_>;
		
		SReadable(Make&& make, DynBuffer&);
		
		SReadable(T_ data);
		
		T_ get() const override;
		
	protected:
		ReadFn& add_read_fn(ReadFn&& read_fn) override;
		
		bool delete_read_fn(ReadFn& read_fn) override;
		
		void reset() override;
		
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
		
		ToMutable(Make&& make, DynBuffer&);
		
		ToMutable(T_ data);
		
		void set(T_ value) override;
	};
	
	template<typename T_>
	using SMutable = ToMutable<SReadable<T_> >;
	
	using SMBool = SMutable<bool>;
	using SMFloat = SMutable<float>;
	using SMInt = SMutable<int>;
	using SMSize = SMutable<size_t>;
	
	template<>
	struct Determine<SMBool::Make> {
		static bool determine(ieml::Node const& node);
	};
}

#include "SReadable.inl"
