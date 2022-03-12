#include "RenderingPanel/TessShaderRenderingWidget.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QComboBox>
#include <QLabel>

TessShaderRenderingWidget::TessShaderRenderingWidget(
  TreeVisuliser *treeVis, QWidget *parent)
  :NodeRenderingWidget{treeVis, parent}
{
  QVBoxLayout *layout = new QVBoxLayout;
  setupGNodeFactory();

  layout->addItem(createPresetComboBox());
  presetWidget_ = new TessBLShaderPresetNoneWidget{treeVis_, factory_};
  layout->addWidget(presetWidget_);

  setLayout(layout);
}

QLayout *TessShaderRenderingWidget::createPresetComboBox()
{
  QHBoxLayout *layout = new QHBoxLayout;

  QLabel *label = new QLabel{"Preset: ", this};
  layout->addWidget(label);

  presetComboBox_ = new QComboBox{this};
  presetComboBox_->addItem("None", static_cast<int>(TessShaderPresetType::TessNone));
  connect(presetComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
    this, &TessShaderRenderingWidget::presetComboBox_onCurrentIndexChanged);
  
  layout->addWidget(presetComboBox_);
  layout->addStretch();
  return layout;
}

void TessShaderRenderingWidget::presetComboBox_onCurrentIndexChanged(int index)
{
  TessShaderPresetType t = static_cast<TessShaderPresetType>(
    presetComboBox_->currentData().value<int>());

  switch (t)
  {
  case TessShaderPresetType::TessNone:
    changePresetWidget(new TessBLShaderPresetNoneWidget{treeVis_, factory_});
    break;
  }
}

void TessShaderRenderingWidget::changePresetWidget(
  TessBLShaderPresetWidget *presetWidget)
{
  QLayout *l = layout();
  l->replaceWidget(presetWidget_, presetWidget);

  presetWidget_->deleteLater();
  presetWidget_ = presetWidget;
}

void TessShaderRenderingWidget::setupGNodeFactory()
{
  factory_ = std::make_shared<TessBLGradientNodeFactory>(treeVis_);
  treeVis_->setGNodeFactory(factory_);
  treeVis_->updateTreeRendering();
}

// ===================== [ PRESET ] ==========================================
TessBLShaderPresetWidget::TessBLShaderPresetWidget(TreeVisualiser *treeVis,
  TessBLGradientNodeFactoryPtr factory)
  : treeVis_{treeVis}, factory_{factory}
{}

// ===================== [ PRESET NONE ] =====================================
TessBLShaderPresetNoneWidget::TessBLShaderPresetNoneWidget(
  TreeVisualiser *treeVis, TessBLGradientNodeFactoryPtr factory)
  :TessBLShaderPresetWidget{treeVis, factory}
{
  QVBoxLayout *layout = new QVBoxLayout;

  layout->addItem(createSliders());
  setLayout(layout);
}

QLayout *TessBLShaderPresetNoneWidget::createSliders()
{
  QVBoxLayout *layout = new QVBoxLayout;

  sliderTopLeft_ = new UnitSliderWidget{"top left: ", this};
  sliderTopLeft_->setValue(factory_->topLeftProportion());
  connect(sliderTopLeft_, &UnitSliderWidget::valueChanged, this, 
    &TessBLShaderPresetNoneWidget::sliderTopLeft_onValueChanged);
  layout->addWidget(sliderTopLeft_);

  sliderTopRight_ = new UnitSliderWidget{"top right: ", this};
  sliderTopRight_->setValue(factory_->topRightProportion());
  connect(sliderTopRight_, &UnitSliderWidget::valueChanged, this, 
    &TessBLShaderPresetNoneWidget::sliderTopRight_onValueChanged);
  layout->addWidget(sliderTopRight_);

  sliderBottomLeft_ = new UnitSliderWidget{"bottom left: ", this};
  sliderBottomLeft_->setValue(factory_->bottomRightProportion());
  connect(sliderBottomLeft_, &UnitSliderWidget::valueChanged, this,
    &TessBLShaderPresetNoneWidget::sliderBottomLeft_onValueChanged);
  layout->addWidget(sliderBottomLeft_);

  sliderBottomRight_ = new UnitSliderWidget{"bottom right: ", this};
  sliderBottomRight_->setValue(factory_->bottomRightProportion());
  connect(sliderBottomRight_, &UnitSliderWidget::valueChanged, this, 
    &TessBLShaderPresetNoneWidget::sliderBottomRight_onValueChanged);
  layout->addWidget(sliderBottomRight_);

  return layout;
}

void TessBLShaderPresetNoneWidget::sliderTopLeft_onValueChanged(double val)
{
  factory_->setTopLeftProportion(val);
  treeVis_->updateTreeRendering();
}

void TessBLShaderPresetNoneWidget::sliderTopRight_onValueChanged(double val)
{
  factory_->setTopRightProportion(val);
  treeVis_->updateTreeRendering();
}

void TessBLShaderPresetNoneWidget::sliderBottomLeft_onValueChanged(double val)
{
  factory_->setBottomLeftProportion(val);
  treeVis_->updateTreeRendering();
}

void TessBLShaderPresetNoneWidget::sliderBottomRight_onValueChanged(double val)
{
  factory_->setBottomRightProportion(val);
  treeVis_->updateTreeRendering();
}

// ===================== [ PRESET WIDGET ] ==================================
