//included into SVec2.hpp

namespace ie::make_system {
	template<typename Value_, typename _>
	BasicSVec2<Value_, _>::BasicSVec2(MakeDyn<Value_> x, MakeDyn<Value_> y) : x(std::move(x)), y(std::move(y)) {
	}
	
	template<typename Value_, typename _>
	rttb::Dyn BasicSVec2<Value_, _>::make(SInitInfo init_info) {
		return rttb::Dyn{ie::BasicSVec2<Value_>{std::move(*this), SInitInfo{init_info}}};
	}
	
	template<typename Value_>
	BasicSMVec2<Value_>::ToMutable(MakeDyn<ie::ToMutable<Value_> > x, MakeDyn<ie::ToMutable<Value_> > y) :
		BasicSVec2<ie::ToMutable<Value_> >(std::move(x), std::move(y)) {
	}
	
	template<typename Value_>
	rttb::Dyn BasicSMVec2<Value_>::make(SInitInfo init_info) {
		return rttb::Dyn{ie::BasicSMVec2<Value_>{std::move(*this), SInitInfo{init_info}}};
	}
}

template<typename Value_>
orl::Option<ie::make_system::BasicSVec2<Value_> >
ieml::Decode<char, ie::make_system::BasicSVec2<Value_> >::decode(const ieml::Node& node) {
	for(auto list: node.get_list_view().ok_or_none()) {
		return ie::make_system::BasicSVec2<Value_>{
			list.at(0).except().as<ie::MakeDyn<Value_> >().except(),
			list.at(1).except().as<ie::MakeDyn<Value_> >().except(),
		};
	}
	auto map{node.get_map_view().except()};
	return ie::make_system::BasicSVec2<Value_>{
		map.at("x").except().as<ie::MakeDyn<Value_> >().except(),
		map.at("y").except().as<ie::MakeDyn<Value_> >().except(),
	};
}

template<typename Value_>
orl::Option<ie::make_system::BasicSMVec2<Value_> >
ieml::Decode<char, ie::make_system::BasicSMVec2<Value_> >::decode(const ieml::Node& node) {
	return ieml::Decode<char, ie::make_system::BasicSVec2<ie::ToMutable<Value_> > >::decode(node).map(
		[](auto&& value) -> ie::make_system::BasicSMVec2<Value_> {
			return {std::move(value.x), std::move(value.y)};
		}
	);
}

namespace ie {
	template<typename Value_, typename _>
	BasicSVec2<Value_, _>::BasicSVec2(Make&& make, SInitInfo init_info) :
		BasicSVec2<Value_>(
			DynBuffer::get(std::move(make.x), SInitInfo{init_info}),
			DynBuffer::get(std::move(make.y), SInitInfo{init_info})
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
	
	template<typename Value_>
	BasicSMVec2<Value_>::ToMutable(Make&& make, SInitInfo init_info) :
		BasicSVec2<ToMutable<Value_> >({std::move(make.x), std::move(make.y)}, SInitInfo{init_info}) {
	}
	
	template<typename Value_>
	BasicSMVec2<Value_>::ToMutable(ToMutable<Value_>& x, ToMutable<Value_>& y) :
		BasicSVec2<ToMutable<Value_> >(x, y) {
	}
	
	template<typename Value_>
	ToMutable<Value_>& BasicSMVec2<Value_>::get_x() const {
		return this->x_.get();
	}
	
	template<typename Value_>
	ToMutable<Value_>& BasicSMVec2<Value_>::get_y() const {
		return this->y_.get();
	}

	template<typename Value_>
	auto BasicSMVec2<Value_>::get() const -> T {
		return BasicSVec2<ToMutable<Value_> >::get();
	}
	
	template<typename Value_>
	void BasicSMVec2<Value_>::set(T value) {
		this->reset_ = false;
		this->x_.get().set(value.x);
		this->y_.get().set(value.y);
		this->reset_ = true;
		this->reset();
	}
	
	template<typename T_>
	bool Determine<make_system::BasicSMVec2<ISRanged<T_> > >::determine(ieml::Node const& node) {
		return node.is_list() || node.is_map();
	}
}
