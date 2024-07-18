#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISVec2/ISVec2.hpp"
#include "../BoxRenderTexture/BoxRenderTexture.hpp"

namespace ie {
	class BoxShader : public BoxRenderTexture {
	public:
		template<typename T>
		using SMakeMap = absl::flat_hash_map<std::string, MakeDyn<T> >;
		
		template<typename T>
		using SReaderVec = std::vector<SReader<T> >;
		
		enum Transmission {
			None = 0,
			Texture = 1 << 0,
			MousePosition = 1 << 1,
			Size = 1 << 2,
			AspectRatio = 1 << 3,
			Time = 1 << 4,
		};
		
		struct LoadTransmission {
			size_t transmission;
		};
		
		struct Make : public BoxRenderTexture::Make {
			sf::Shader* shader;
			size_t transmission;
			SMakeMap<ISFloat> values_f;
			SMakeMap<ISInt> values_i;
			SMakeMap<ISBool> values_b;
			SMakeMap<ISReadable<sf::Color> > values_c;
			SMakeMap<ISRVec2F> values_v;
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				sf::Shader* shader,
				size_t transmission,
				SMakeMap<ISFloat> values_f = {},
				SMakeMap<ISInt> values_i = {},
				SMakeMap<ISBool> values_b = {},
				SMakeMap<ISReadable<sf::Color> > values_c = {},
				SMakeMap<ISRVec2F> values_v = {},
				bool optimize = true,
				sf::Vector2f min_size = {}
			);
			
			auto make(InitInfo init_info) -> BoxShader* override;
		};
		
		BoxShader(Make&& make, InitInfo init_info);
		
		~BoxShader();
		
		auto set_uniform(std::string const& name, float var) -> void;
		
		auto set_uniform(std::string const& name, int var) -> void;
		
		auto set_uniform(std::string const& name, bool var) -> void;
		
		auto set_uniform(std::string const& name, sf::Color var) -> void;
		
		auto set_uniform(std::string const& name, sf::Vector2f var) -> void;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto handle_event(Event event) -> bool override;
		
	protected:
		sf::Shader* shader_;
		size_t transmission_;
		SReaderVec<ISFloat> values_f_;
		SReaderVec<ISInt> values_i_;
		SReaderVec<ISBool> values_b_;
		SReaderVec<ISReadable<sf::Color> > values_c_;
		SReaderVec<ISRVec2F> values_v_;
		
		sf::Clock clock_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxShader::LoadTransmission> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxShader::LoadTransmission>;
};

template<>
struct ieml::Decode<char, ie::BoxShader::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxShader::Make>;
};
