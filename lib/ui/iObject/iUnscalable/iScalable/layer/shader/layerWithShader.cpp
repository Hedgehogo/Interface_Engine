#include "layerWithShader.hpp"

namespace ui {
	void convertTransmission(const YAML::Node& node, uint &transmission) {
		std::map<std::string, LayerWithShader::Transmission> transmissionMap {
			{"size", LayerWithShader::Transmission::size},
			{"texture", LayerWithShader::Transmission::texture},
			{"aspectRatio", LayerWithShader::Transmission::aspectRatio},
			{"mousePosition", LayerWithShader::Transmission::mousePosition},
			{"time", LayerWithShader::Transmission::time},
		};
		
		if(node.IsScalar()) {
			std::string strTransmission = node.as<std::string>();
			transmission = transmissionMap[strTransmission];
		} else if(node.IsSequence()) {
			std::string strTransmission;
			for(const auto &item: node) {
				strTransmission = item.as<std::string>();
				transmission = static_cast<LayerWithShader::Transmission>(transmission | transmissionMap[strTransmission]);
			}
		}
	}
	
    LayerWithShader::LayerWithShader(IScalable *object, sf::Shader *shader, uint transmission,
                                     std::map<std::string, PISfloat> sharedValuesf,
                                     std::map<std::string, PISint> sharedValuesi,
                                     std::map<std::string, PISbool> sharedValuesb,
                                     std::map<std::string, PISValue<sf::Color>> sharedValuesc,
                                     std::map<std::string, PSRVec2f> sharedValuesv,
                                     bool optimize, sf::Vector2f minSize) :
	    LayerWithRenderTexture(object, optimize, minSize), shader(shader), transmission(transmission){
        clock.restart();

	    for (auto &[name, value]: sharedValuesf){
			value->addSetter([&](float var){
				setUniform(name, var);
			});
	    }
	    for (auto &[name, value]: sharedValuesi){
		    value->addSetter([&](int var){
			    setUniform(name, var);
		    });
	    }
	    for (auto &[name, value]: sharedValuesb){
		    value->addSetter([&](bool var){
			    setUniform(name, var);
		    });
	    }
	    for (auto &[name, value]: sharedValuesc){
		    value->addSetter([&](sf::Color var){
			    setUniform(name, var);
		    });
	    }
	    for (auto &[name, value]: sharedValuesv){
		    value->addSetter([&](sf::Vector2f var){
			    setUniform(name, var);
		    });
	    }
    }

	void LayerWithShader::setUniform(std::string name, float var) {
		shader->setUniform(name, var);
	}

	void LayerWithShader::setUniform(std::string name, int var) {
		shader->setUniform(name, var);
	}

	void LayerWithShader::setUniform(std::string name, bool var) {
		shader->setUniform(name, var);
	}

	void LayerWithShader::setUniform(std::string name, sf::Color var) {
		shader->setUniform(name, sf::Glsl::Vec4{var});
	}

	void LayerWithShader::setUniform(std::string name, sf::Vector2f var) {
		shader->setUniform(name, var);
	}

	void LayerWithShader::setSize(sf::Vector2f size) {
		if (transmission & Transmission::size) shader->setUniform("size", size);
		if (transmission & Transmission::aspectRatio) shader->setUniform("aspectRatio", size.x / size.y);
		Layout::setSize(size);
	}

	void LayerWithShader::draw() {
		if(!optimize || active || interactionManager->isBlocked()) {
			renderTexture.clear(sf::Color(0, 0, 0, 0));
			drawManager.draw();
			renderTexture.display();
			sprite.setTexture(renderTexture.getTexture());
			active = false;
		}
		if (transmission & Transmission::time) shader->setUniform("time", clock.getElapsedTime().asSeconds());
		if (transmission & Transmission::texture) shader->setUniform("texture", renderTexture.getTexture());
		renderTarget->draw(sprite, shader);
	}

	void LayerWithShader::resize(sf::Vector2f size, sf::Vector2f position) {
		if (transmission & Transmission::size) shader->setUniform("size", size);
		if (transmission & Transmission::aspectRatio) shader->setUniform("aspectRatio", size.x / size.y);
		LayerWithRenderTexture::resize(size, position);
	}

	bool LayerWithShader::updateInteractions(sf::Vector2f mousePosition) {
		if (transmission & Transmission::mousePosition) shader->setUniform("mousePosition", mousePosition - position);
		return LayerWithRenderTexture::updateInteractions(mousePosition);
	}

	template<typename T>
	std::map<std::string, std::shared_ptr<T>> getSharedValuesf(const YAML::Node &node){
		std::map<std::string, std::shared_ptr<T>> result;
		for(auto &[name, nodeValue] : node.as<std::map<std::string, YAML::Node>>()){
			result[name] = Buffer::get<T>(nodeValue);
		}
		return result;
	}

    bool convertPointer(const YAML::Node &node, LayerWithShader *&layerWithShader) {
        IScalable* object;
        sf::Shader* shader = new sf::Shader{};
        uint transmission{};
	    std::map<std::string, PISfloat> sharedValuesf;
	    std::map<std::string, PISint> sharedValuesi;
	    std::map<std::string, PISbool> sharedValuesb;
	    std::map<std::string, PISValue<sf::Color>> sharedValuesc;
	    std::map<std::string, PSRVec2f> sharedValuesv;
        bool optimize{true};
        sf::Vector2f minSize{0, 0};
        node["object"] >> object;
        if (node["transmission"]) convertTransmission(node["transmission"], transmission);
        if (node["shader"]) node["shader"] >> *shader;
	    if (node["sharedValuesf"]) sharedValuesf = getSharedValuesf<ISfloat>(node["sharedValuesf"]);
	    if (node["sharedValuesi"]) sharedValuesi = getSharedValuesf<ISint>(node["sharedValuesi"]);
	    if (node["sharedValuesb"]) sharedValuesb = getSharedValuesf<ISbool>(node["sharedValuesb"]);
	    if (node["sharedValuesc"]) sharedValuesc = getSharedValuesf<ISValue<sf::Color>>(node["sharedValuesc"]);
	    if (node["sharedValuesv"]) sharedValuesv = getSharedValuesf<SRVec2f>(node["sharedValuesv"]);
        if (node["optimize"]) node["optimize"] >> optimize;
        if (node["min-size"]) node["min-size"] >> minSize;
        { layerWithShader = new LayerWithShader{object, shader, transmission, sharedValuesf, sharedValuesi, sharedValuesb, sharedValuesc, sharedValuesv, optimize, minSize}; return true; }
    }
}
