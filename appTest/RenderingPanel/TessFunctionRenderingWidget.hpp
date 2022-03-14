#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "RenderingPanel/NodeRenderingWidget.hpp"
#include "RenderingPanel/CustomWidgets/UnitSliderWidget.hpp"

#include "IcicleMorphotreeWidget/Graphics/Node/TessFunctionNodeFactory.hpp"

class TessFunctionRenderingWidget : public NodeRenderingWidget
{
Q_OBJECT
public:
  using TessFunctionNodeFactory = IcicleMorphotreeWidget::TessFunctionNodeFactory;
  using TessFunctionNodeFactoryPtr = std::shared_ptr<TessFunctionNodeFactory>;

  TessFunctionRenderingWidget(TreeVisuliser *treeVis, QWidget *parent=nullptr);

protected:
  void setUpGNodeFactory();

protected slots:
  void minValueSlider_onValueChanged(double val);
  void maxValueSlider_onValueChanged(double val);

protected:
  UnitSliderWidget *minValueSlider_;
  UnitSliderWidget *maxValueSlider_;
  TessFunctionNodeFactoryPtr factory_;
};