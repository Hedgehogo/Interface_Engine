#pragma once

#include "../BasicInteractiveData.hpp"
#include "IE/IComponent/ILayout/ILayoutObject/ILayoutObject.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/IUninteractive.hpp"

namespace ie {
	class BaseButton : public virtual ILayoutObject, public virtual IScalable, public virtual IUpdatable {
	public:
		BaseButton(BoxPtr<IScalable::Make>&& background, InitInfo initInfo);
		
		BaseButton(BoxPtr<IScalable>&& background);
		
		void init(InitInfo initInfo) override;
		
		IScalable& getObject() override;
		
		const IScalable& getObject() const override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		LayoutData& layoutGetData() override;
		
		const LayoutData& layoutGetData() const override;
		
		LayoutData layout;
		BoxPtr<IScalable> background;
	};
}
