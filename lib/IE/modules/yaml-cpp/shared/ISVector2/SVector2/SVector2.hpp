#pragma once

#include "../../ISValue/SRangeValue/SRangeValue.hpp"
#include "../ISVector2.hpp"

namespace ie {
	template<typename T>
	class SVector2 : public virtual ISVector2 {
	protected:
		void set();
	
	public:
		using V = to_auto<decltype(std::declval<T>().get_value())>;
		using SetterFunc = std::function<void(const sf::Vector2<V>&)>;
		
		SVector2(const sf::Vector2<V>& vector = {});
		
		SVector2(std::shared_ptr<T> x, std::shared_ptr<T> y);
		
		virtual void add_setter(const SetterFunc& setter);
		
		PIShared get_x_ptr() const override;
		
		void set_x_ptr(PIShared value) override;
		
		PIShared get_y_ptr() const override;
		
		void set_y_ptr(PIShared value) override;
		
		V get_x() const;
		
		void set_x(const V& value);
		
		V get_y() const;
		
		void set_y(const V& value);
		
		sf::Vector2<V> get_value() const;
		
		void set_value(const sf::Vector2<V>& vector);
	
	protected:
		std::shared_ptr<T> x_, y_;
		std::vector<SetterFunc> setters_;
	};
	
	template<typename T>
	struct DecodePointer<SVector2<T> > {
		static bool decode_pointer(const YAML::Node& node, SVector2<T>*& with_vector2);
	};
	
	template<typename T>
	using SVec2 = SVector2<T>;
	
	template<typename T>
	using PSVec2 = std::shared_ptr<SVec2<T> >;
	
	template<typename T>
	void set_range_upper(PSVec2<SRange<T> > value, sf::Vector2<T> upper);
	
	template<typename T>
	void set_range_lower(PSVec2<SRange<T> > value, sf::Vector2<T> lower);
	
	template<typename T>
	void set_range_bounds(PSVec2<SRange<T> > value, sf::Vector2<T> lower, sf::Vector2<T> upper);
	
	using SVec2f = SVec2<Sfloat>;
	using SVec2i = SVec2<Sint>;
	using SVec2u = SVec2<Ssize>;
	using SRVec2f = SVec2<SRfloat>;
	using SRVec2i = SVec2<SRint>;
	using SRVec2u = SVec2<SRsize>;
	using SCoefficientVec2 = SVec2<SCoefficientValue>;
	
	using PSVec2f = std::shared_ptr<SVec2f>;
	using PSVec2i = std::shared_ptr<SVec2i>;
	using PSVec2u = std::shared_ptr<SVec2u>;
	using PSRVec2f = std::shared_ptr<SRVec2f>;
	using PSRVec2i = std::shared_ptr<SRVec2i>;
	using PSRVec2u = std::shared_ptr<SRVec2u>;
	using PSCoefficientVec2 = std::shared_ptr<SCoefficientVec2>;
}

#include "SVector2.inl"
