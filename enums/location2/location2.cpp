#include "location2.h"

namespace ui {
	Location getVerticalLocation(Location2 location2) {
		switch(location2) {
			case Location2::upLeft:
			case Location2::up:
			case Location2::upRight:
				return Location::origin;
				break;
			case Location2::left:
			case Location2::center:
			case Location2::right:
				return Location::center;
				break;
			case Location2::downLeft:
			case Location2::down:
			case Location2::downRight:
				return Location::end;
				break;
		}
        return Location::center;
	}
	
	Location getHorizontalLocation(Location2 location2) {
		switch(location2) {
			case Location2::upLeft:
			case Location2::left:
			case Location2::downLeft:
				return Location::origin;
				break;
			case Location2::up:
			case Location2::center:
			case Location2::down:
				return Location::center;
				break;
			case Location2::upRight:
			case Location2::right:
			case Location2::downRight:
				return Location::end;
				break;
		}
        return Location::center;
	}
}