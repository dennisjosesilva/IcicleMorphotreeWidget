#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "RenderingPanel/NodeRenderingWidget.hpp"
#include "RenderingPanel/CustomWidgets/UnitSliderWidget.hpp"

#include "IcicleMorphotreeWidget/Graphics/Node/BezierFuncNodeFactory.hpp"

class BezierFuncRenderingWidget : public NodeRenderingWidget
{
Q_OBJECT
public:
  using BezierFuncNodeFactory = IcicleMorphotreeWidget::BezierFuncNodeFactory;
  using BezierFuncNodeFactoryPtr = std::shared_ptr<BezierFuncNodeFactory>;

  BezierFuncRenderingWidget(TreeVisuliser *treeVis, QWidget *parent=nullptr);

protected:
  void setUpGNodeFactory();
  QLayout *createSliders();

protected slots:
  void hleftSlider_onValueChanged(double val);
  void hmiddleSlider_onValueChanged(double val);
  void hrightSlider_onValueChanged(double val);

  void vtopSlider_onValueChanged(double val);
  void vmiddleSlider_onValueChanged(double val);
  void vbottomSlider_onValueChanged(double val);

protected:
  UnitSliderWidget *hleftSlider_;
  UnitSliderWidget *hmiddleSlider_;
  UnitSliderWidget *hrightSlider_;

  UnitSliderWidget *vtopSlider_;
  UnitSliderWidget *vmiddleSlider_;
  UnitSliderWidget *vbottomSlider_;

  BezierFuncNodeFactoryPtr factory_;
};