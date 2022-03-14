#include "RenderingPanel/TessFunctionRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>

TessFunctionRenderingWidget::TessFunctionRenderingWidget(
  TreeVisuliser *treeVis, QWidget *parent)
  :NodeRenderingWidget{treeVis, parent}
{
  QVBoxLayout *layout = new QVBoxLayout;

  setUpGNodeFactory();
  minValueSlider_ = new UnitSliderWidget{"min value: ", this};
  minValueSlider_->setValue(factory_->minValue());
  connect(minValueSlider_, &UnitSliderWidget::valueChanged, this, 
    &TessFunctionRenderingWidget::minValueSlider_onValueChanged);

  maxValueSlider_ = new UnitSliderWidget{"max value: ", this};
  maxValueSlider_->setValue(factory_->maxValue());
  connect(maxValueSlider_, &UnitSliderWidget::valueChanged, this,
    &TessFunctionRenderingWidget::maxValueSlider_onValueChanged);

  layout->addItem(createTitle("Tessallation based on function"));
  layout->addWidget(minValueSlider_);
  layout->addWidget(maxValueSlider_);

  setLayout(layout);
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