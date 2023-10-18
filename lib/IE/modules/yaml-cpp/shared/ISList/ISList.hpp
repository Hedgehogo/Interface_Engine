#pragma once

#include "../ISValue/ISCoefficientValue/SCoefficientValue/SCoefficientValue.hpp"
#include "../ISValue/ISCoefficientValue/SReferenceCoefficientValue/SReferenceCoefficientValue.hpp"

namespace ie {
	class ISList {
	public:
		ISList() = default;
		
		virtual PIShared get_element_ptr(std::size_t index) const = 0;
		
		virtual void set_element_ptr(std::size_t index, PIShared value) = 0;
	};
}
