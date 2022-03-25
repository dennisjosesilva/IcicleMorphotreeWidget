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
  QLayout *createSliders();

protected slots:
  void minValueSlider_onValueChanged(double val);
  void maxValueSlider_onValueChanged(double val);

  void topLeftProportionSlider_onValueChanged(double val);
  void topRightProportionSlider_onValueChanged(double val);
  void bottomLeftProportionSlider_onValueChanged(double val);
  void bottomRightProportionSlider_onValueChanged(double val);

protected:
  UnitSliderWidget *minValueSlider_;
  UnitSliderWidget *maxValueSlider_;

  UnitSliderWidget *topLeftProportionSlider_;
  UnitSliderWidget *topRightProportionSlider_;
  UnitSliderWidget *bottomLeftProportionSlider_;
  UnitSliderWidget *bottomRightProportionSlider_;

  TessFunctionNodeFactoryPtr factory_;
};