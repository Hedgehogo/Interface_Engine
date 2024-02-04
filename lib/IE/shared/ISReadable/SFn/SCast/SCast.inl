//included into SCast.hpp

namespace ie::detail {
	template<typename From_, typename To_>
	typename To_::T SCast<From_, To_>::fn(From_& value) {
		return static_cast<typename To_::T>(value.get());
	}
}
