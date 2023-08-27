#pragma once

#include "../value/coefficient/general/sCoefficientValue.hpp"
#include "../value/coefficient/reference/sReferenceCoefficientValue.hpp"

namespace ie {
	class ISVector2 : public IShared {
	public:
		ISVector2() = default;
		
		virtual PIShared getXPtr() const = 0;
		
		virtual void setXPtr(PIShared value) = 0;
		
		virtual PIShared getYPtr() const = 0;
		
		virtual void setYPtr(PIShared value) = 0;
	};
}