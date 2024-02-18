#pragma once

#include "IE/shared/DynBuffer/DynBuffer.hpp"
#include "../IGettable/IGettable.hpp"
#include "../ISettable/ISettable.hpp"

namespace ie {
	template<typename T_, typename>
	class SReader;
	
	template<typename T_>
	class ISReadable;
	
	namespace make_system {
		template<typename Value_>
		struct ToMutable;
		
		template<typename T_>
		struct ISReadable {
			virtual rttb::Dyn make(SInitInfo init_info) = 0;
			
			virtual ~ISReadable() = default;
		};
		
		template<typename T_>
		struct ToMutable<ISReadable<T_> > : public virtual ISReadable<T_> {
		};
		
		template<typename T_>
		using ISMutable = ToMutable<ISReadable<T_> >;
	}
	
	template<typename Value_>
	class ToMutable;
	
	template<typename T_>
	class ISReadable : public virtual IGettable<T_> {
	public:
		using T = T_;
		using ReadFn = std::function<void(const T_&)>;
		using Make = make_system::ISReadable<T_>;
		
		template<typename T, typename>
		friend class SReader;
	
	protected:
		virtual ReadFn& add_read_fn(ReadFn&& read_fn) = 0;
		
		virtual bool delete_read_fn(ReadFn& read_fn) = 0;
	};
	
	template<typename T_>
	constexpr bool is_readable = std::is_base_of_v<ISReadable<typename T_::T>, T_>;
	
	using ISBool = ISReadable<bool>;
	using ISFloat = ISReadable<float>;
	using ISInt = ISReadable<int>;
	using ISSize = ISReadable<size_t>;
	
	template<typename T_>
	class ToMutable<ISReadable<T_> > : public virtual ISReadable<T_>, public virtual ISettable<T_> {
	public:
		using ReadFn = std::function<void(const T_&)>;
		using Make = make_system::ISMutable<T_>;
	};
	
	template<typename T_>
	using ISMutable = ToMutable<ISReadable<T_> >;
	
	template<typename T_>
	constexpr bool is_mutable = std::is_base_of_v<ISMutable<typename T_::T>, T_>;
	
	using ISMBool = ISMutable<bool>;
	using ISMFloat = ISMutable<float>;
	using ISMInt = ISMutable<int>;
	using ISMSize = ISMutable<size_t>;
}
