#include "RenderingPanel/BezierFuncRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>

BezierFuncRenderingWidget::BezierFuncRenderingWidget(TreeVisuliser *treeVis,
  QWidget *parent)
  : NodeRenderingWidget{treeVis, parent}
{
  QVBoxLayout *layout = new QVBoxLayout;

  setUpGNodeFactory();

  layout->addItem(createTitle("Bezier Function Rendering"));
  layout->addItem(createSliders());

  setLayout(layout);
}

QLayout *BezierFuncRenderingWidget::createSliders()
{
  QVBoxLayout *layout = new QVBoxLayout;

  hleftSlider_ = new UnitSliderWidget{"hleft: ", this};
  hleftSlider_->setValue(factory_->hleft());
  connect(hleftSlider_, &UnitSliderWidget::valueChanged, this, 
    &BezierFuncRenderingWidget::hleftSlider_onValueChanged);
  
  hmiddleSlider_ = new UnitSliderWidget{"hmiddle: ", this};
  hmiddleSlider_->setValue(factory_->hmiddle());
  connect(hmiddleSlider_, &UnitSliderWidget::valueChanged, this, 
    &BezierFuncRenderingWidget::hmiddleSlider_onValueChanged);

  hrightSlider_ = new UnitSliderWidget{"hright: ", this};
  hrightSlider_->setValue(factory_->hright());
  connect(hrightSlider_, &UnitSliderWidget::valueChanged, this,
    &BezierFuncRenderingWidget::hrightSlider_onValueChanged);

  vtopSlider_ = new UnitSliderWidget{"vtop: ", this};
  vtopSlider_->setValue(factory_->vtop());
  connect(vtopSlider_, &UnitSliderWidget::valueChanged, this, 
    &BezierFuncRenderingWidget::vtopSlider_onValueChanged);

  vmiddleSlider_ = new UnitSliderWidget{"vmiddle: ", this};
  vmiddleSlider_->setValue(factory_->vmiddle());
  connect(vmiddleSlider_, &UnitSliderWidget::valueChanged, this, 
    &BezierFuncRenderingWidget::vmiddleSlider_onValueChanged);

  vbottomSlider_ = new UnitSliderWidget{"vbottom: ", this};
  vbottomSlider_->setValue(factory_->vbottom());
  connect(vbottomSlider_, &UnitSliderWidget::valueChanged, this, 
    &BezierFuncRenderingWidget::vbottomSlider_onValueChanged);

  layout->addWidget(hleftSlider_);
  layout->addWidget(hmiddleSlider_);
  layout->addWidget(hrightSlider_);

  layout->addWidget(vtopSlider_);
  layout->addWidget(vmiddleSlider_);
  layout->addWidget(vbottomSlider_);

  return layout;
}

void BezierFuncRenderingWidget::setUpGNodeFactory()
{
  using IcicleMorphotreeWidget::BezierFuncNodeFactory;
  factory_ = std::make_shared<BezierFuncNodeFactory>();

  treeVis_->setGNodeFactory(factory_);
  treeVis_->updateTreeRendering();
}

void BezierFuncRenderingWidget::hleftSlider_onValueChanged(double val)
{
  factory_->setHLeft(val);
  treeVis_->updateTreeRendering();
}

void BezierFuncRenderingWidget::hmiddleSlider_onValueChanged(double val)
{
  factory_->setHMiddle(val);
  treeVis_->updateTreeRendering();
}

void BezierFuncRenderingWidget::hrightSlider_onValueChanged(double val)
{
  factory_->setHRight(val);
  treeVis_->updateTreeRendering();
}

void BezierFuncRenderingWidget::vtopSlider_onValueChanged(double val)
{
  factory_->setVTop(val);
  treeVis_->updateTreeRendering();
}

void BezierFuncRenderingWidget::vmiddleSlider_onValueChanged(double val)
{
  factory_->setVMiddle(val);
  treeVis_->updateTreeRendering();
}

void BezierFuncRenderingWidget::vbottomSlider_onValueChanged(double val)
{
  factory_->setVBottom(val);
  treeVis_->updateTreeRendering();
}