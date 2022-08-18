#pragma once
#include "../iWithValue.hpp"

namespace ui {
	template<typename T>
	class WithValue : public virtual IWithValue<T> {
	protected:
		T value;
		
	public:
		explicit WithValue(T value = T{}) : value(value) {}
		
		const T& getValue() const override {
			return value;
		}
		
		void setValue(const T& value) override {
			this->value = value;
		}
	};
}
