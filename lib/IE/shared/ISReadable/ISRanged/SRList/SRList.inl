//included into SRList.hpp

namespace ie {
	namespace make_system {
		template<typename T_>
		SRList<T_>::SRList(std::vector<MakeDyn<ie::ISRanged<T_> > > values) : values(std::move(values)) {
		}
		
		template<typename T_>
		auto SRList<T_>::make(SInitInfo init_info) -> rttb::Dyn {
			return rttb::Dyn{new ie::SRList<T_>{std::move(*this), init_info}};
		}
	}
	
	template<typename T_>
	SRList<T_>::SRList(
		Make&& make,
		SInitInfo init_info
	) :
		SRanged<T_>({}, init_info),
		values_([this, &values = make.values, &init_info]{
			auto result{std::vector<SReader<ISRanged<T_> > >{}};
			result.reserve(values.size());
			for (auto& value : values) {
				result.emplace_back(
					DynBuffer::get(std::move(value), init_info),
					[this](auto const& value){
						this->set(value);
					}
				);
			}
			return result;
		}()){
	}
	
	template<typename T_>
	auto SRList<T_>::set_lower_bound(T_ lower_bound) -> void {
		SRanged<T_>::set_lower_bound(lower_bound);
		for(auto& value : values_) {
			value.get().set_lower_bound(this->lower_bound_);
		}
	}
	
	template<typename T_>
	auto SRList<T_>::set_upper_bound(T_ upper_bound) -> void {
		SRanged<T_>::set_upper_bound(upper_bound);
		for(auto& value : values_) {
			value.get().set_upper_bound(this->upper_bound_);
		}
	}
	
	template<typename T_>
	auto SRList<T_>::set_bounds(T_ lower_bound, T_ upper_bound) -> void {
		SRanged<T_>::set_bounds(lower_bound, upper_bound);
		for(auto& value : values_) {
			value.get().set_bounds(this->lower_bound_, this->upper_bound_);
		}
	}
}

template<typename T_>
orl::Option<ie::make_system::SRList<T_> > ieml::Decode<char, ie::make_system::SRList<T_> >::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::make_system::SRList<T_> {
		map.at("values").except().as<std::vector<ie::MakeDyn<ie::ISRanged<T_> > > >().except()
	};
}
