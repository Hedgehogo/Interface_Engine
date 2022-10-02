#pragma once
#include "../iWithValue.hpp"

namespace ui {
	template<typename T>
	class WithReferenceValue : public virtual IWithValue<T> {
	protected:
		T* valueReference;
		
	public:
		explicit WithReferenceValue(T& valueReference);;
		
		const T& getValue() const override;
		
		void setValue(const T& value) override;
		
		virtual void setReference(T& valueReference);
	};
}

#include "withReferenceValue.inl"
