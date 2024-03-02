#include "ILayoutTwoObjects.hpp"

namespace ie {
	auto ILayoutTwoObjects::get_array_size() const -> size_t {
		return 2;
	}
	
	auto ILayoutTwoObjects::get_object_at(size_t index) const -> IScalable const& {
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
	
	auto ILayoutTwoObjects::get_object_at(size_t index) -> IScalable& {
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