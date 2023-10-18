#pragma once

#include "../ISValue/ISCoefficientValue/SCoefficientValue/SCoefficientValue.hpp"
#include "../ISValue/ISCoefficientValue/SReferenceCoefficientValue/SReferenceCoefficientValue.hpp"

namespace ie {
	class ISVector2 : public virtual IShared {
	public:
		ISVector2() = default;
		
		virtual PIShared get_x_ptr() const = 0;
		
		virtual void set_x_ptr(PIShared value) = 0;
		
		virtual PIShared get_y_ptr() const = 0;
		
		virtual void set_y_ptr(PIShared value) = 0;
	};
}