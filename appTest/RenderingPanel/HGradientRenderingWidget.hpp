#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "RenderingPanel/NodeRenderingWidget.hpp"
#include "RenderingPanel/CustomWidgets/UnitSliderWidget.hpp"

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

class HGradientRenderingWidget : public NodeRenderingWidget
{
public:
  using GradientGNodeFactory = IcicleMorphotreeWidget::GradientGNodeFactory;
  using GradientGNodeFactoryPtr = std::shared_ptr<GradientGNodeFactory>;

  HGradientRenderingWidget(TreeVisuliser *treeVis, 
    QWidget *parent=nullptr);

protected:
  void setupGNodeFactory();

protected slots:
  void proportionSlider_onValueChanged(double val);

protected:
  UnitSliderWidget *propotionSlider_;
  GradientGNodeFactoryPtr factory_;
};