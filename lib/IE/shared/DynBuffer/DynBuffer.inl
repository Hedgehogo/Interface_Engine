//included into SharedBuffer.hpp

namespace ie {
	template<typename T>
	bool DynBuffer::add(MakeDyn<T> make_dyn, SInitInfo init_info) {
		if(auto pair{std::get_if<0>(&make_dyn.data_)}) {
			return init_info.dyn_buffer.indexed_.emplace(pair->id_, pair->make_.make(init_info)).second;
		}
	}
	
	template<typename T>
	T& DynBuffer::get(MakeDyn<T> make_dyn, SInitInfo init_info) {
		if(auto pair{std::get_if<0>(&make_dyn.data_)}) {
			auto& builder{rttb::Builder<ieml::Node const&, T>::builder()};
			if(pair->id_ != 0) {
				if(auto add_result{init_info.dyn_buffer.indexed_.emplace(pair->id_, pair->make_->make(init_info))}; add_result.second) {
					return *builder.cast(add_result.first->second).except();
				}
				return *builder.cast(init_info.dyn_buffer.indexed_.at(pair->id_)).except();
			}
			return *builder.cast(init_info.dyn_buffer.non_indexed_.emplace_back(pair->make_->make(init_info))).except();
		}
		return *std::get_if<1>(&make_dyn.data_);
	}
	
	template<typename Type_>
	MakeDyn<Type_>::MakeDyn(size_t id, bp::BoxPtr<MakeType> make) : data_(Pair{id, std::move(make)}) {
	}
	
	template<typename Type_>
	MakeDyn<Type_>::MakeDyn(bp::BoxPtr<MakeType> make) : data_(Pair{0, std::move(make)}) {
	}
	
	template<typename Type_>
	MakeDyn<Type_>::MakeDyn(Type_& ref) : data_(ref) {
	}
	
	template<typename Type_>
	Type_& MakeDyn<Type_>::make(SInitInfo init_info) {
		return init_info.dyn_buffer.get(std::move(*this), init_info);
	}
	
	template<typename Type_>
	orl::Option<MakeDyn<Type_> > MakeDyn<Type_>::decode(ieml::Node const& node) {
		auto& tag_node{node.get_clear_data<ieml::NodeType::GetAnchor, ieml::NodeType::TakeAnchor>()};
		return ieml::Decode<char, bp::BoxPtr<MakeType> >::decode(tag_node).map([&](auto&& value) -> MakeDyn<Type_> {
			if(&tag_node != &node) {
				size_t id{reinterpret_cast<size_t>(&tag_node)};
				return {id, std::move(value)};
			}
			return {std::move(value)};
		});
	}
	
	template<typename Type_>
	ie::MakeDyn<Type_>::Pair::Pair(size_t id_, bp::BoxPtr<MakeType> make_) : id_(id_), make_(std::move(make_)) {
	}
}

template<typename Type_>
auto tnl::TypeName<ie::MakeDyn<Type_> >::type_name() -> StringView {
	return tnl::type_name<bp::BoxPtr<typename Type_::Make> >();
}

template<typename Type_>
orl::Option<ie::MakeDyn<Type_> > ieml::Decode<char, ie::MakeDyn<Type_> >::decode(const ieml::Node& node) {
	return ie::MakeDyn<Type_>::decode(node);
}
