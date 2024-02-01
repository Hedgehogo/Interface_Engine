//included into SVec2.hpp

namespace ie::make_system {
	template<typename Value_, typename _>
	BasicSVec2<Value_, _>::BasicSVec2(MakeDyn<Value_> x, MakeDyn<Value_> y) : x_(std::move(x)), y_(std::move(y)) {
	}
	
	template<typename Value_, typename _>
	rttb::Dyn BasicSVec2<Value_, _>::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::BasicSVec2<Value_>{std::move(*this), dyn_buffer}};
	}
}

template<typename Value_>
orl::Option<ie::make_system::BasicSVec2<Value_> >
ieml::Decode<char, ie::make_system::BasicSVec2<Value_> >::decode(const ieml::Node& node) {
	if(auto list{node.get_list_view()}) {
		return ie::make_system::BasicSVec2<Value_>{
			list.ok().at(0).except().as<ie::MakeDyn<Value_> >().move_except(),
			list.ok().at(1).except().as<ie::MakeDyn<Value_> >().move_except(),
		};
	}
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicSVec2<Value_>{
		map.at("x").except().as<ie::MakeDyn<Value_> >().move_except(),
		map.at("y").except().as<ie::MakeDyn<Value_> >().move_except(),
	};
}

namespace ie {
	template<typename Value_, typename _>
	BasicSVec2<Value_, _>::BasicSVec2(Make&& make, DynBuffer& dyn_buffer) :
		BasicSVec2(
			dyn_buffer.get(std::move(make.x_)),
			dyn_buffer.get(std::move(make.y_))
		) {
	}
	
	template<typename Value_, typename _>
	BasicSVec2<Value_, _>::BasicSVec2(Value_& x, Value_& y) :
		reset_(true),
		x_(x, [this](typename Value_::T const&) {
			reset_ = false;
			this->reset();
			reset_ = true;
		}),
		y_(y, [this](typename Value_::T const&) {
			reset_ = false;
			this->reset();
			reset_ = true;
		}) {
	}
	
	template<typename Value_, typename _>
	Value_& BasicSVec2<Value_, _>::get_x() const {
		return x_.get();
	}
	
	template<typename Value_, typename _>
	Value_& BasicSVec2<Value_, _>::get_y() const {
		return y_.get();
	}
	
	template<typename Value_, typename _>
	auto BasicSVec2<Value_, _>::get() const -> T {
		return {x_.get().get(), y_.get().get()};
	}
	
	template<typename Value_, typename _>
	void BasicSVec2<Value_, _>::set(T value) {
		reset_ = false;
		x_.get().set(value.x);
		y_.get().set(value.y);
		reset_ = true;
		reset();
	}
	
	template<typename Value_, typename _>
	auto BasicSVec2<Value_, _>::add_read_fn(ReadFn&& read_fn) -> ReadFn& {
		return read_fns_.emplace_back(std::move(read_fn));
	}
	
	template<typename Value_, typename _>
	bool BasicSVec2<Value_, _>::delete_read_fn(ReadFn& read_fn) {
		auto result{std::find_if(read_fns_.cbegin(), read_fns_.cend(), [&](ReadFn const& item) {
			return &item == &read_fn;
		})};
		if(result != read_fns_.cend()) {
			read_fns_.erase(result);
			return true;
		}
		return false;
	}
	
	template<typename Value_, typename _>
	void BasicSVec2<Value_, _>::reset() {
		if(reset_) {
			reset_ = false;
			auto value{get()};
			for(auto& read_fn: read_fns_) {
				read_fn(value);
			}
			reset_ = true;
		}
	}
	
	template<typename T_>
	bool Determine<make_system::BasicSVec2<ISRanged<T_> > >::determine(ieml::Node const& node) {
		return node.is_list() || node.is_map();
	}
}
