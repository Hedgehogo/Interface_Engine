#pragma once

#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "../../SReader/SReader.hpp"
#include "../../ISVec2/ISVec2.hpp"
#include "../../ISRanged/ISRanged.hpp"

namespace ie {
	template<typename Value_, typename>
	class BasicSVec2;
	
	namespace make_system {
		template<typename Value_, typename = std::enable_if_t<is_shared<Value_> > >
		struct BasicSVec2 : public virtual ISVec2<typename Value_::T> {
		public:
			MakeDyn<Value_> x_;
			MakeDyn<Value_> y_;
			
			BasicSVec2(MakeDyn<Value_> x, MakeDyn<Value_> y);
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
	}
}

template<typename Value_>
struct ieml::Decode<char, ie::make_system::BasicSVec2<Value_> > {
	static orl::Option<ie::make_system::BasicSVec2<Value_> > decode(ieml::Node const& node);
};

namespace ie {
	template<typename Value_, typename = std::enable_if_t<is_shared<Value_> > >
	class BasicSVec2 : public virtual ISVec2<typename Value_::T> {
	public:
		using T = sf::Vector2<typename Value_::T>;
		using ReadFn = typename ISVec2<T>::ReadFn;
		using Make = make_system::BasicSVec2<Value_>;
		
		BasicSVec2(Make&& make, DynBuffer& dyn_buffer);
		
		BasicSVec2(Value_& x, Value_& y);
		
		Value_& get_x() const;
		
		Value_& get_y() const;
		
		T get() const override;
		
		void set(T value) override;
	
	protected:
		ReadFn& add_read_fn(ReadFn&& read_fn) override;
		
		bool delete_read_fn(ReadFn& read_fn) override;
	
	private:
		void reset();
	
	protected:
		bool reset_;
		SReader<Value_> x_;
		SReader<Value_> y_;
		std::vector<ReadFn> read_fns_;
	};
	
	template<typename T>
	using SVec2 = BasicSVec2<ISValue<T> >;
	
	using SVec2B = SVec2<bool>;
	using SVec2F = SVec2<float>;
	using SVec2I = SVec2<int>;
	using SVec2S = SVec2<size_t>;
	
	template<typename T>
	using SRVec2 = BasicSVec2<ISRanged<T> >;
	
	using SRVec2F = SRVec2<float>;
	using SRVec2I = SRVec2<int>;
	using SRVec2S = SRVec2<size_t>;
	
	template<typename T_>
	struct Determine<make_system::BasicSVec2<ISRanged<T_> > > {
		static bool determine(ieml::Node const& node);
	};
}

#include "SVec2.inl"