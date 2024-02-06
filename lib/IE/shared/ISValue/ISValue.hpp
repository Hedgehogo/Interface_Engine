#pragma once

#include "IE/shared/DynBuffer/DynBuffer.hpp"
#include "../IGettable/IGettable.hpp"
#include "../ISettable/ISettable.hpp"

namespace ie {
	template<typename T_, typename>
	class SReader;
	
	template<typename T_>
	class ISValue;
	
	namespace make_system {
		template<typename T_>
		struct ISValue {
			virtual rttb::Dyn make(DynBuffer& dyn_buffer) = 0;
			
			virtual ~ISValue() = default;
		};
	}
	
	template<typename T_>
	class ISValue : public virtual IGettable<T_>, public virtual ISettable<T_> {
	public:
		using ReadFn = std::function<void(const T_&)>;
		using Make = make_system::ISValue<T_>;
		
		template<typename T, typename>
		friend class SReader;
	
	protected:
		virtual ReadFn& add_read_fn(ReadFn&& read_fn) = 0;
		
		virtual bool delete_read_fn(ReadFn& read_fn) = 0;
	};
	
	template<typename Value_>
	constexpr bool is_shared = std::is_base_of_v<ISValue<typename Value_::T>, Value_>;
	
	using ISBool = ISValue<bool>;
	using ISFloat = ISValue<float>;
	using ISInt = ISValue<int>;
	using ISSize = ISValue<size_t>;
}
