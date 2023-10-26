//included into with_vector2.hpp
#include <utility>

namespace ie {
	template<typename T>
	SVector2<T>::SVector2(const sf::Vector2<typename SVector2<T>::V>& vector) :
		x_(std::make_shared<T>(vector.x)), y_(std::make_shared<T>(vector.y)), setters_() {
		x_->add_setter([this](auto) {
			set();
		});
		y_->add_setter([this](auto) {
			set();
		});
	}
	
	template<typename T>
	SVector2<T>::SVector2(std::shared_ptr<T> x, std::shared_ptr<T> y) :
		x_(x), y_(y), setters_() {
			x->add_setter([this](auto) {
				set();
			});
			y->add_setter([this](auto) {
				set();
			});
	}
	
	template<typename T>
	void SVector2<T>::set() {
		for(const auto& setter: setters_)
			setter(get_value());
	}
	
	template<typename T>
	void SVector2<T>::add_setter(const typename SVector2<T>::SetterFunc& setter) {
		setters_.push_back(setter);
	}
	
	template<typename T>
	PIShared SVector2<T>::get_x_ptr() const {
		return std::dynamic_pointer_cast<IShared>(x_);
	}
	
	template<typename T>
	void SVector2<T>::set_x_ptr(PIShared value) {
		x_ = std::dynamic_pointer_cast<T>(value);
		set();
	}
	
	template<typename T>
	PIShared SVector2<T>::get_y_ptr() const {
		return std::dynamic_pointer_cast<IShared>(y_);
	}
	
	template<typename T>
	void SVector2<T>::set_y_ptr(PIShared value) {
		y_ = std::dynamic_pointer_cast<T>(value);
		set();
	}
	
	template<typename T>
	typename SVector2<T>::V SVector2<T>::get_x() const {
		return x_->get_value();
	}
	
	template<typename T>
	void SVector2<T>::set_x(const typename SVector2<T>::V& value) {
		x_->set_value(value);
		set();
	}
	
	template<typename T>
	typename SVector2<T>::V SVector2<T>::get_y() const {
		return y_->get_value();
	}
	
	template<typename T>
	void SVector2<T>::set_y(const typename SVector2<T>::V& value) {
		y_->set_value(value);
		set();
	}
	
	template<typename T>
	sf::Vector2<typename SVector2<T>::V> SVector2<T>::get_value() const {
		return {get_x(), get_y()};
	}
	
	template<typename T>
	void SVector2<T>::set_value(const sf::Vector2<typename SVector2<T>::V>& vector) {
		set_x(vector.x);
		set_y(vector.y);
		set();
	}
	
	template<typename T>
	void set_range_upper(PSVec2<SRange<T> > value, sf::Vector2<T> upper) {
		std::dynamic_pointer_cast<SRange<T> >(value->get_x_ptr())->set_upper(upper.x);
		std::dynamic_pointer_cast<SRange<T> >(value->get_y_ptr())->set_upper(upper.y);
	}
	
	template<typename T>
	void set_range_lower(PSVec2<SRange<T>> value, sf::Vector2<T> lower) {
		std::dynamic_pointer_cast<SRange<T> >(value->get_x_ptr())->set_lower(lower.x);
		std::dynamic_pointer_cast<SRange<T> >(value->get_y_ptr())->set_lower(lower.y);
	}
	
	template<typename T>
	void set_range_bounds(PSVec2<SRange<T> > value, sf::Vector2<T> lower, sf::Vector2<T> upper) {
		std::dynamic_pointer_cast<SRange<T> >(value->get_x_ptr())->set_bounds(lower.x, upper.x);
		std::dynamic_pointer_cast<SRange<T> >(value->get_y_ptr())->set_bounds(lower.y, upper.y);
	}
	
	template<typename T>
	bool DecodePointer<SVector2<T> >::decode_pointer(const YAML::Node& node, SVector2<T>*& with_vector2) {
		if(node["x"] && node["y"]) {
			with_vector2 = new SVector2<T>(get_s_value<T>(node["x"]), get_s_value<T>(node["y"]));
		} else {
			sf::Vector2<typename SVector2<T>::V> vector;
			
			if(node["vector"])
				node["vector"] >> vector;
			
			with_vector2 = new SVector2<T>(vector);
		}
		return true;
	}
}