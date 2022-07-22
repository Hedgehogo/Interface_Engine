#pragma once
#include "../location/location.h"

namespace ui {
	enum class Location2 {
		  upLeft,     up,   upRight,
		    left, center,     right,
		downLeft,   down, downRight
	};
	
	Location getVerticalLocation(Location2 location2);
	Location getHorizontalLocation(Location2 location2);
}
