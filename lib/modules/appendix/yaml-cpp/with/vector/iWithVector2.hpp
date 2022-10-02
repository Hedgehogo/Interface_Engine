#pragma once
#include <SFML/Graphics.hpp>
#include "../value/iWithValue.hpp"
#include "../value/general/withValue.hpp"
#include "../value/general/sf_Vector2/withValue_sf_Vector2.hpp"
#include "../value/reference//withReferenceValue.hpp"
#include "../value/coefficient/general/withCoefficientValue.hpp"
#include "../value/coefficient/reference/withReferenceCoefficientValue.hpp"

namespace ui {
	class IWithVector2 : public IWith {
	public:
		IWithVector2() = default;
		
		virtual std::shared_ptr<IWith> getXPtr() const = 0;
		
		virtual void setXPtr(std::shared_ptr<IWith> value) = 0;
		
		virtual std::shared_ptr<IWith> getYPtr() const = 0;
		
		virtual void setYPtr(std::shared_ptr<IWith> value) = 0;
	};
}