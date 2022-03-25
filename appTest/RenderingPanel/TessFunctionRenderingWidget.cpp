#include "RenderingPanel/TessFunctionRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>

TessFunctionRenderingWidget::TessFunctionRenderingWidget(
  TreeVisuliser *treeVis, QWidget *parent)
  :NodeRenderingWidget{treeVis, parent}
{
  QVBoxLayout *layout = new QVBoxLayout;

  setUpGNodeFactory();
  
  layout->addItem(createTitle("Tessallation based on function"));
  layout->addItem(createSliders());

  setLayout(layout);
}

QLayout *TessFunctionRenderingWidget::createSliders()
{
  QVBoxLayout *layout = new QVBoxLayout;

  minValueSlider_ = new UnitSliderWidget{"min value: ", this};
  minValueSlider_->setValue(factory_->minValue());
  connect(minValueSlider_, &UnitSliderWidget::valueChanged, this, 
    &TessFunctionRenderingWidget::minValueSlider_onValueChanged);

  maxValueSlider_ = new UnitSliderWidget{"max value: ", this};
  maxValueSlider_->setValue(factory_->maxValue());
  connect(maxValueSlider_, &UnitSliderWidget::valueChanged, this,
    &TessFunctionRenderingWidget::maxValueSlider_onValueChanged);

  topLeftProportionSlider_ = new UnitSliderWidget{"top left: ", this};
  topLeftProportionSlider_->setValue(factory_->topLeftProportion());
  connect(topLeftProportionSlider_, &UnitSliderWidget::valueChanged, this,
    &TessFunctionRenderingWidget::topLeftProportionSlider_onValueChanged);

  topRightProportionSlider_ = new UnitSliderWidget{"top right: ", this};
  topRightProportionSlider_->setValue(factory_->topRightProportion());
  connect(topRightProportionSlider_, &UnitSliderWidget::valueChanged, this,
    &TessFunctionRenderingWidget::topRightProportionSlider_onValueChanged);

  bottomLeftProportionSlider_ = new UnitSliderWidget{"bottom left: ", this};
  bottomLeftProportionSlider_->setValue(factory_->topRightProportion());
  connect(bottomLeftProportionSlider_, &UnitSliderWidget::valueChanged, this, 
    &TessFunctionRenderingWidget::bottomLeftProportionSlider_onValueChanged);

  bottomRightProportionSlider_ = new UnitSliderWidget{"bottom right: ", this};
  bottomRightProportionSlider_->setValue(factory_->bottomRightProportion());
  connect(bottomRightProportionSlider_, &UnitSliderWidget::valueChanged, this, 
    &TessFunctionRenderingWidget::bottomRightProportionSlider_onValueChanged);

  layout->addWidget(minValueSlider_);
  layout->addWidget(maxValueSlider_);
  layout->addWidget(topLeftProportionSlider_);
  layout->addWidget(topRightProportionSlider_);
  layout->addWidget(bottomLeftProportionSlider_);
  layout->addWidget(bottomRightProportionSlider_);

  return layout;
}

void TessFunctionRenderingWidget::setUpGNodeFactory()
{
  using IcicleMorphotreeWidget::TessFunctionNodeFactory;
  factory_ = std::make_shared<TessFunctionNodeFactory>();

  treeVis_->setGNodeFactory(factory_);
  treeVis_->updateTreeRendering();
}

void TessFunctionRenderingWidget::minValueSlider_onValueChanged(double val)
{
  factory_->setMinValue(val);
  treeVis_->updateTreeRendering();
}

void TessFunctionRenderingWidget::maxValueSlider_onValueChanged(double val)
{
  factory_->setMaxValue(val);
  treeVis_->updateTreeRendering();
}

void TessFunctionRenderingWidget::topLeftProportionSlider_onValueChanged(double val)
{
  factory_->setTopLeftProportion(val);
  treeVis_->updateTreeRendering();
}

void TessFunctionRenderingWidget::topRightProportionSlider_onValueChanged(double val)
{
  factory_->setTopRightProportion(val);
  treeVis_->updateTreeRendering();
}

void TessFunctionRenderingWidget::bottomLeftProportionSlider_onValueChanged(double val)
{
  factory_->setBottomLeftProportion(val);
  treeVis_->updateTreeRendering();
}

void TessFunctionRenderingWidget::bottomRightProportionSlider_onValueChanged(double val)
{
  factory_->setBottomRightProportion(val);
  treeVis_->updateTreeRendering();
}
