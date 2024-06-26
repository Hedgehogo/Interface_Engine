#pragma once

#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "../ISVec2.hpp"
#include "../../ISRanged/ISRanged.hpp"
#include "../../../SReader/SReader.hpp"

namespace ie {
	namespace make_system {
		template<typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
		struct BasicSVec2 : public virtual IBasicSVec2<Value_> {
			MakeDyn<Value_> x;
			MakeDyn<Value_> y;
			
			BasicSVec2(MakeDyn<Value_> x, MakeDyn<Value_> y);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename Value_>
		struct ToMutable<BasicSVec2<Value_> > : public BasicSVec2<ie::ToMutable<Value_> >, public virtual IBasicSMVec2<Value_> {
			ToMutable(MakeDyn<ie::ToMutable<Value_> > x, MakeDyn<ie::ToMutable<Value_> > y);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
		
		template<typename Value_>
		using BasicSMVec2 = ToMutable<BasicSVec2<Value_> >;
	}
}

template<typename Value_>
struct ieml::Decode<char, ie::make_system::BasicSVec2<Value_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicSVec2<Value_> >;
};

template<typename Value_>
struct ieml::Decode<char, ie::make_system::BasicSMVec2<Value_> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicSMVec2<Value_> >;
};

namespace ie {
	template<typename Value_, typename = std::enable_if_t<is_readable<Value_> > >
	class BasicSVec2 : public virtual IBasicSVec2<Value_> {
	public:
		using T = typename IBasicSVec2<Value_>::T;
		using ReadFn = typename IBasicSVec2<Value_>::ReadFn;
		using Make = make_system::BasicSVec2<Value_>;
		
		BasicSVec2(Make&& make, SInitInfo init_info);
		
		BasicSVec2(Value_& x, Value_& y);
		
		auto get_x() const -> Value_& override;
		
		auto get_y() const -> Value_& override;
		
		auto get() const -> T override;
		
	protected:
		auto add_read_fn(ReadFn&& read_fn) -> ReadFn& override;
		
		auto delete_read_fn(ReadFn& read_fn) -> bool override;
	
		auto reset() -> void;
		
		bool reset_;
		SReader<Value_> x_;
		SReader<Value_> y_;
		std::vector<ReadFn> read_fns_;
	};
	
	template<typename T>
	using SVec2 = BasicSVec2<ISReadable<T> >;
	
	using SVec2B = SVec2<bool>;
	using SVec2F = SVec2<float>;
	using SVec2I = SVec2<int>;
	using SVec2S = SVec2<size_t>;
	
	template<typename T>
	using SRVec2 = BasicSVec2<ISRanged<T> >;
	
	using SRVec2F = SRVec2<float>;
	using SRVec2I = SRVec2<int>;
	using SRVec2S = SRVec2<size_t>;
	
	template<typename Value_>
	class ToMutable<BasicSVec2<Value_> > : public BasicSVec2<ToMutable<Value_> >, public virtual IBasicSMVec2<Value_> {
	public:
		using T = typename IBasicSMVec2<Value_>::T;
		using ReadFn = typename IBasicSMVec2<Value_>::ReadFn;
		using Make = make_system::BasicSMVec2<Value_>;
		
		ToMutable(Make&& make, SInitInfo init_info);
		
		ToMutable(ToMutable<Value_>& x, ToMutable<Value_>& y);
		
		auto get_x() const -> ToMutable<Value_>& override;
		
		auto get_y() const -> ToMutable<Value_>& override;
		
		auto get() const -> T override;
		
		auto set(T value) -> void override;
	};
	
	template<typename Value_>
	using BasicSMVec2 = ToMutable<BasicSVec2<Value_> >;
	
	template<typename T>
	using SMVec2 = BasicSMVec2<ISReadable<T> >;
	
	using SMVec2B = SMVec2<bool>;
	using SMVec2F = SMVec2<float>;
	using SMVec2I = SMVec2<int>;
	using SMVec2S = SMVec2<size_t>;
	
	template<typename T>
	using SMRVec2 = BasicSMVec2<ISRanged<T> >;
	
	using SMRVec2F = SMRVec2<float>;
	using SMRVec2I = SMRVec2<int>;
	using SMRVec2S = SMRVec2<size_t>;
	
	template<typename T_>
	struct Determine<make_system::BasicSMVec2<ISRanged<T_> > > {
		static auto determine(ieml::Node const& node) -> bool;
	};
}

#include "SVec2.inl"