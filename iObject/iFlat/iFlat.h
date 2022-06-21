#pragma once

#include "../iObject.h"

namespace ui {
	class IFlat : public virtual IObject {
	public:
		IFlat* copy() override = 0;
	};
}