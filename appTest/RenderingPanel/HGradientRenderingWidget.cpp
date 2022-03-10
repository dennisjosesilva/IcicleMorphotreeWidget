#include "RenderingPanel/HGradientRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>

HGradientRenderingWidget::HGradientRenderingWidget(TreeVisuliser *treeVis,
  QWidget *parent)
  :NodeRenderingWidget{treeVis, parent}
{
  QVBoxLayout *layout = new QVBoxLayout;

  setupGNodeFactory();
  propotionSlider_ = new UnitSliderWidget{"proportion: ", this}; 
  propotionSlider_->setValue(factory_->gradientProportion());
  connect(propotionSlider_, &UnitSliderWidget::valueChanged, this, 
    &HGradientRenderingWidget::proportionSlider_onValueChanged);

  layout->addItem(createTitle("Horizontal Gradient Rendering"));
  layout->addWidget(propotionSlider_);

  setLayout(layout);
}

void HGradientRenderingWidget::setupGNodeFactory()
{
  using IcicleMorphotreeWidget::HGradientGNodeFactory;
  using IcicleMorphotreeWidget::VGradientGNodeFactory;
  using IcicleMorphotreeWidget::TreeLayoutOrientation;

  if (treeVis_->orientation() == TreeLayoutOrientation::Horizontal)
    factory_ = std::make_shared<VGradientGNodeFactory>(treeVis_);
  else 
    factory_ = std::make_shared<HGradientGNodeFactory>(treeVis_);

  treeVis_->setGNodeFactory(factory_);
  treeVis_->updateTreeRendering();
}

void HGradientRenderingWidget::proportionSlider_onValueChanged(double val)
{
  factory_->setGradientProportion(val);
  treeVis_->updateTreeRendering();
}