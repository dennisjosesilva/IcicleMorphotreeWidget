#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "RenderingPanel/NodeRenderingWidget.hpp"

class HGradientRenderingWidget : public NodeRenderingWidget
{
public:
  HGradientRenderingWidget(IcicleMorphotreeWidget *treeVis, 
    QWidget *parent=nullptr);

protected:
  UnitSliderWidget *propotionSlider_;
};