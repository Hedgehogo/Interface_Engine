#pragma once
#include <SFML/Graphics.hpp>
#include "../value/iWithValue.hpp"
#include "../value/general/withValue.hpp"
#include "../value/general/sf_Vector2/withValue_sf_Vector2.hpp"
#include "../value/reference//withReferenceValue.hpp"
#include "../value/coefficient/general/withCoefficientValue.hpp"
#include "../value/coefficient/reference/withReferenceCoefficientValue.hpp"

namespace ui {
	class IWithList {
	public:
		IWithList() = default;
		
		virtual std::shared_ptr<IWith> getElementPtr(std::size_t index) const = 0;
		
		virtual void setElementPtr(std::size_t index, std::shared_ptr<IWith> value) = 0;
	};
}
