#pragma once

#include <SFML/System.hpp>
#include "../ISReadable.hpp"
#include "../ISRanged/ISRanged.hpp"

namespace ie {
	namespace make_system {
		template<typename Value_>
		struct IBasicSVec2 : public virtual ISReadable<sf::Vector2<typename Value_::T> > {
		};
		
		template<typename Value_>
		struct ToMutable<IBasicSVec2<Value_> > :
			public virtual IBasicSVec2<Value_>,
			public virtual IBasicSVec2<ie::ToMutable<Value_> >,
			public virtual ISMutable<sf::Vector2<typename Value_::T> > {
		};
		
		template<typename T_>
		using IBasicSMVec2 = ToMutable<IBasicSVec2<T_> >;
	}
	
	template<typename Value_>
	class IBasicSVec2 : public virtual ISReadable<sf::Vector2<typename Value_::T> > {
	public:
		using T = sf::Vector2<typename Value_::T>;
		using ReadFn = std::function<void(const T&)>;
		using Make = make_system::IBasicSVec2<Value_>;
		
		virtual Value_& get_x() const = 0;
		
		virtual Value_& get_y() const = 0;
	};
	
	template<typename T_>
	using ISVec2 = IBasicSVec2<ISReadable<T_> >;
	
	using ISVec2B = ISVec2<bool>;
	using ISVec2F = ISVec2<float>;
	using ISVec2I = ISVec2<int>;
	using ISVec2S = ISVec2<size_t>;
	
	template<typename T>
	using ISRVec2 = IBasicSVec2<ISRanged<T> >;
	
	using ISRVec2F = ISRVec2<float>;
	using ISRVec2I = ISRVec2<int>;
	using ISRVec2S = ISRVec2<size_t>;
	
	template<typename Value_>
	class ToMutable<IBasicSVec2<Value_> > :
		public virtual IBasicSVec2<Value_>,
		public virtual IBasicSVec2<ToMutable<Value_> >,
		public virtual ISMutable<sf::Vector2<typename Value_::T> > {
	public:
		using T = typename IBasicSVec2<Value_>::T;
		using ReadFn = typename IBasicSVec2<Value_>::ReadFn;
		using Make = make_system::IBasicSMVec2<Value_>;
		
		ToMutable<Value_>& get_x() const override = 0;
		
		ToMutable<Value_>& get_y() const override = 0;
		
		T get() const override = 0;
	};
	
	template<typename T_>
	using IBasicSMVec2 = ToMutable<IBasicSVec2<T_> >;
	
	template<typename T_>
	using ISMVec2 = IBasicSMVec2<ISReadable<T_> >;
	
	using ISMVec2B = ISMVec2<bool>;
	using ISMVec2F = ISMVec2<float>;
	using ISMVec2I = ISMVec2<int>;
	using ISMVec2S = ISMVec2<size_t>;
	
	template<typename T>
	using ISMRVec2 = IBasicSMVec2<ISRanged<T> >;
	
	using ISMRVec2F = ISMRVec2<float>;
	using ISMRVec2I = ISMRVec2<int>;
	using ISMRVec2S = ISMRVec2<size_t>;
}
