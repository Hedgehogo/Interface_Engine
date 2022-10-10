#pragma once
#include "../iSValue.hpp"

namespace ui {
	template<typename T>
	class SReferenceValue : public virtual ISValue<T> {
	protected:
		T* valueReference;
		
	public:
		explicit SReferenceValue(T& valueReference);;
		
		const T& getValue() const override;
		
		void setValue(const T& value) override;
		
		virtual void setReference(T& valueReference);
	};
}

#include "sReferenceValue.inl"
