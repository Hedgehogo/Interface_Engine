#pragma once

#include "../value/coefficient/general/sCoefficientValue.hpp"
#include "../value/coefficient/reference/sReferenceCoefficientValue.hpp"

namespace ui {
	class ISList {
	public:
		ISList() = default;
		
		virtual PIShared getElementPtr(std::size_t index) const = 0;
		
		virtual void setElementPtr(std::size_t index, PIShared value) = 0;
	};
}
