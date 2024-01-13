#pragma once

#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISValue/SVec2/SVec2.hpp"
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
			SMakeMap<ISValue<sf::Color> > values_c;
			SMakeMap<SRVec2F> values_v;
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				sf::Shader* shader,
				size_t transmission,
				SMakeMap<ISFloat> values_f = {},
				SMakeMap<ISInt> values_i = {},
				SMakeMap<ISBool> values_b = {},
				SMakeMap<ISValue<sf::Color> > values_c = {},
				SMakeMap<SRVec2F> values_v = {},
				bool optimize = true,
				sf::Vector2f min_size = {}
			);
			
			BoxShader* make(InitInfo init_info) override;
		};
		
		BoxShader(Make&& make, InitInfo init_info);
		
		~BoxShader();
		
		void set_uniform(std::string const& name, float var);
		
		void set_uniform(std::string const& name, int var);
		
		void set_uniform(std::string const& name, bool var);
		
		void set_uniform(std::string const& name, sf::Color var);
		
		void set_uniform(std::string const& name, sf::Vector2f var);
		
		void set_size(sf::Vector2f size) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		BoxShader* copy() override;
	
	protected:
		sf::Shader* shader_;
		size_t transmission_;
		SReaderVec<ISFloat> values_f_;
		SReaderVec<ISInt> values_i_;
		SReaderVec<ISBool> values_b_;
		SReaderVec<ISValue<sf::Color> > values_c_;
		SReaderVec<SRVec2F> values_v_;
		
		sf::Clock clock_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<BoxShader> {
		static bool decode_pointer(const YAML::Node& node, BoxShader*& box_with_shader);
	};
	*/
}

template<>
struct ieml::Decode<char, ie::BoxShader::LoadTransmission> {
	static orl::Option<ie::BoxShader::LoadTransmission> decode(ieml::Node const& node);
};
