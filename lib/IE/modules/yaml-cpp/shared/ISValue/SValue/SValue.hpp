#pragma once

#include "../ISValue.hpp"

namespace ie {
	template<typename T>
	class SValue : public virtual ISValue<T> {
	public:
		explicit SValue(T value = T{});
		
		void add_setter(const typename ISValue<T>::SetterFunc& setter) override;
		
		const T& get_value() const override;
		
		void set_value(const T& value) override;
	
	protected:
		T value;
		std::vector<typename ISValue<T>::SetterFunc> setters;
	};
	
	template<typename T>
	struct DecodePointer<SValue<T> > {
		static bool decode_pointer(const YAML::Node& node, SValue<T>*& sValue);
	};
	
	typedef SValue<bool> Sbool;
	typedef SValue<float> Sfloat;
	typedef SValue<int> Sint;
	typedef SValue<unsigned> Suint;
	
	template<typename T>
	using PSValue = std::shared_ptr<SValue<T>>;
	
	typedef std::shared_ptr<Sbool> PSbool;
	typedef std::shared_ptr<Sfloat> PSfloat;
	typedef std::shared_ptr<Sint> PSint;
	typedef std::shared_ptr<Suint> PSuint;
}

#include "SValue.inl"