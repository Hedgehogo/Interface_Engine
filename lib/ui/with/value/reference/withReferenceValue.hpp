#pragma once
#include "../iWithValue.hpp"

namespace ui {
	template<typename T>
	class WithReferenceValue : public virtual IWithValue<T> {
	protected:
		T* valueReference;
		
	public:
		explicit WithReferenceValue(T& valueReference) : valueReference(&valueReference) {};
		
		const T& getValue() const override {
			return *valueReference;
		}
		
		void setValue(const T& value) override {
			*this->valueReference = value;
		}
		
		virtual void setReference(T& valueReference) {
			this->valueReference = &valueReference;
		}
	};
}
