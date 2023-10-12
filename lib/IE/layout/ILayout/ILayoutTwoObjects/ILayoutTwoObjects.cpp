#include "ILayoutTwoObjects.hpp"

namespace ie {
	std::size_t ILayoutTwoObjects::getArraySize() const {
		return 2;
	}
	
	const IScalable& ILayoutTwoObjects::getObjectAt(std::size_t index) const {
		if(index == 0) {
			return getFirstObject();
		}
		if(index == 1) {
			return getSecondObject();
		}
		throw std::out_of_range(
			std::string("ILayoutTwoObjects::getObjectAt: __n (which is ") +
			std::to_string(index) + std::string(") >= _Nm (which is 2)")
		);
	}
	
	IScalable& ILayoutTwoObjects::getObjectAt(std::size_t index) {
		if(index == 0) {
			return getFirstObject();
		}
		if(index == 1) {
			return getSecondObject();
		}
		throw std::out_of_range(
			std::string("ILayoutTwoObjects::getObjectAt: __n (which is ") +
			std::to_string(index) + std::string(") >= _Nm (which is 2)")
		);
	}
}