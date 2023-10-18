#include "ILayoutTwoObjects.hpp"

namespace ie {
	std::size_t ILayoutTwoObjects::get_array_size() const {
		return 2;
	}
	
	const IScalable& ILayoutTwoObjects::get_object_at(std::size_t index) const {
		if(index == 0) {
			return get_first_object();
		}
		if(index == 1) {
			return get_second_object();
		}
		throw std::out_of_range(
			std::string("ILayoutTwoObjects::get_object_at: __n (which is ") +
			std::to_string(index) + std::string(") >= _Nm (which is 2)")
		);
	}
	
	IScalable& ILayoutTwoObjects::get_object_at(std::size_t index) {
		if(index == 0) {
			return get_first_object();
		}
		if(index == 1) {
			return get_second_object();
		}
		throw std::out_of_range(
			std::string("ILayoutTwoObjects::get_object_at: __n (which is ") +
			std::to_string(index) + std::string(") >= _Nm (which is 2)")
		);
	}
}