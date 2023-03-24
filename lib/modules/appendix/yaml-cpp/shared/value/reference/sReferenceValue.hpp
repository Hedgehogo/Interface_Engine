#pragma once
#include "../iSValue.hpp"

namespace ui {
	template<typename T>
	class SReferenceValue : public virtual ISValue<T> {
	protected:
		T* valueReference;
		std::vector<typename ISValue<T>::SetterFunc> setters;
		
	public:
		explicit SReferenceValue(T& valueReference);
		
		void addSetter(const typename ISValue<T>::SetterFunc& setter) override;
		
		const T& getValue() const override;
		
		void setValue(const T& value) override;
		
		virtual void setReference(T& valueReference);
	};
}

#include "sReferenceValue.inl"
