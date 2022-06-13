#pragma once

#include "../iObject.h"

namespace ui {
	class IFlat : public IObject {
	public:
		IFlat* copy() override = 0;
	};
}