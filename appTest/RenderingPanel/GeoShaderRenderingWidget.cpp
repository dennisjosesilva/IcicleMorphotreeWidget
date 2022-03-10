#include "RenderingPanel/GeoShaderRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>

GeoShaderRenderingWidget::GeoShaderRenderingWidget(TreeVisuliser *treeVis,
  QWidget *parent)
  : NodeRenderingWidget{treeVis, parent}
{
  QVBoxLayout *layout = new QVBoxLayout;
  setupGNodeFactory();

  layout->addItem(createPresetComboBox());
  presetWidget_ = new PresetNoneWidget{treeVis_, factory_};
  layout->addWidget(presetWidget_);

  setLayout(layout);
}

QLayout *GeoShaderRenderingWidget::createPresetComboBox()
{
  QHBoxLayout *layout = new QHBoxLayout;

  QLabel *label = new QLabel{"Preset: ", this};
  layout->addWidget(label);

  presetComboBox_ = new QComboBox{this};
  presetComboBox_->addItem("None", 
    static_cast<int>(GeoShaderPresetType::None));
  presetComboBox_->addItem("Default", 
    static_cast<int>(GeoShaderPresetType::Default));
  presetComboBox_->addItem("Flat", 
    static_cast<int>(GeoShaderPresetType::Flat));
  presetComboBox_->addItem("Vertical", 
    static_cast<int>(GeoShaderPresetType::Vertical));
  presetComboBox_->addItem("Horizontal", 
    GeoShaderPresetType::Horizontal);
  presetComboBox_->addItem("Symmetric Tent-Like Cushion",
    GeoShaderPresetType::SymmetricTentLikeCushion);
  presetComboBox_->addItem("Asymetric Tent-Like Cushion",
    GeoShaderPresetType::AsymmetricTentLikeCushion);
  connect(presetComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged), 
    this, &GeoShaderRenderingWidget::presetComboBox_onCurrentIndexChanged);

  layout->addWidget(presetComboBox_);
  layout->addStretch();
  return layout;
}

void GeoShaderRenderingWidget::presetComboBox_onCurrentIndexChanged(int index)
{
  GeoShaderPresetType t = static_cast<GeoShaderPresetType>(
    presetComboBox_->currentData().value<int>());
  
  switch (t)
  {
  case GeoShaderPresetType::None:
    changePresetWidget(new PresetNoneWidget{treeVis_, factory_});
    break;
  
  case GeoShaderPresetType::Default:
    changePresetWidget(new PresetDefaultWidget{treeVis_, factory_});
    break;
  }
}

void GeoShaderRenderingWidget::changePresetWidget(PresetWidget *presetWidget)
{
  QLayout *l = layout();
  l->replaceWidget(presetWidget_, presetWidget);

  presetWidget_->deleteLater();
  presetWidget_ = presetWidget;
}

void GeoShaderRenderingWidget::setupGNodeFactory()
{
  factory_ = std::make_shared<OpenGLGNodeFactory>(treeVis_);
  treeVis_->setGNodeFactory(factory_);
  treeVis_->updateTreeRendering();  
}

// =============== [ PRESETS ] ======================================

// =============== [ PRESET WIDGET ] ================================
PresetWidget::PresetWidget(TreeVisualiser *treeVis, 
  OpenGLGNodeFactoryPtr factory)
: treeVis_{treeVis}, factory_{factory}
{}

// ============= [ PRESET NONE ] ====================================
PresetNoneWidget::PresetNoneWidget(TreeVisualiser *treeVis, 
  OpenGLGNodeFactoryPtr factory)
  : PresetWidget{treeVis, factory}
{
  QVBoxLayout *layout = new QVBoxLayout;

  layout->addItem(createSliders());
  setLayout(layout);
}

QLayout *PresetNoneWidget::createSliders()
{
  QVBoxLayout *layout = new QVBoxLayout;

  sliderTop_ = new UnitSliderWidget{"top: ", this};
  sliderTop_->setValue(factory_->topProportion());
  connect(sliderTop_, &UnitSliderWidget::valueChanged, this, 
    &PresetNoneWidget::sliderTop_onValueChanged);
  layout->addWidget(sliderTop_);

  sliderLeft_ = new UnitSliderWidget{"left: ", this};
  sliderLeft_ ->setValue(factory_->leftProportion());
  connect(sliderLeft_, &UnitSliderWidget::valueChanged, this, 
    &PresetNoneWidget::sliderLeft_onValueChanged);
  layout->addWidget(sliderLeft_);

  sliderBottom_ = new UnitSliderWidget{"bottom: ", this};
  sliderBottom_->setValue(factory_->bottomProportion());
  connect(sliderBottom_, &UnitSliderWidget::valueChanged, this, 
    &PresetNoneWidget::sliderBottom_onValueChanged);
  layout->addWidget(sliderBottom_);

  sliderRight_ = new UnitSliderWidget{"right: ", this};
  sliderRight_->setValue(factory_->rightProportion());
  connect(sliderRight_, &UnitSliderWidget::valueChanged, this,
    &PresetNoneWidget::sliderRight_onValueChanged);
  layout->addWidget(sliderRight_);
  
  sliderCenter_ = new UnitSliderWidget{"center: ", this};
  sliderCenter_->setValue(factory_->centerProportion());
  connect(sliderCenter_, &UnitSliderWidget::valueChanged, this,
    &PresetNoneWidget::sliderCenter_onValueChanged);
  layout->addWidget(sliderCenter_);

  sliderTopLeft_ = new UnitSliderWidget{"top left: ", this};
  sliderTopLeft_->setValue(factory_->topLeftProportion());
  connect(sliderTopLeft_, &UnitSliderWidget::valueChanged, this,
    &PresetNoneWidget::sliderTopLeft_onValueChanged);
  layout->addWidget(sliderTopLeft_);

  sliderTopRight_ = new UnitSliderWidget{"top right: ", this};
  sliderTopRight_->setValue(factory_->topRightProportion());
  connect(sliderTopRight_, &UnitSliderWidget::valueChanged, this, 
    &PresetNoneWidget::sliderTopRight_onValueChanged);
  layout->addWidget(sliderTopRight_);

  sliderBottomLeft_ = new UnitSliderWidget{"bottom left: ", this};
  sliderBottomLeft_->setValue(factory_->bottomLeftProportion());
  connect(sliderBottomLeft_, &UnitSliderWidget::valueChanged, this,
    &PresetNoneWidget::sliderBottomLeft_onValueChanged);
  layout->addWidget(sliderBottomLeft_);

  sliderBottomRight_ = new UnitSliderWidget{"bottom right: ", this};
  sliderBottomRight_->setValue(factory_->bottomRightProportion());
  connect(sliderBottomRight_, &UnitSliderWidget::valueChanged, this,
    &PresetNoneWidget::sliderBottomRight_onValueChanged);
  layout->addWidget(sliderBottomRight_);

  return layout;
}

void PresetNoneWidget::sliderTop_onValueChanged(double val)
{
  factory_->setTopProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetNoneWidget::sliderLeft_onValueChanged(double val)
{
  factory_->setLeftProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetNoneWidget::sliderBottom_onValueChanged(double val)
{
  factory_->setBottomProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetNoneWidget::sliderRight_onValueChanged(double val)
{
  factory_->setRightProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetNoneWidget::sliderCenter_onValueChanged(double val)
{
  factory_->setCenterProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetNoneWidget::sliderTopLeft_onValueChanged(double val)
{
  factory_->setTopLeftProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetNoneWidget::sliderTopRight_onValueChanged(double val)
{
  factory_->setTopRightProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetNoneWidget::sliderBottomLeft_onValueChanged(double val)
{
  factory_->setBottomLeftProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetNoneWidget::sliderBottomRight_onValueChanged(double val)
{
  factory_->setBottomRightProportion(val);
  treeVis_->updateTreeRendering();
}

// ============= [ PRESET DEFAULT ] ====================================
PresetDefaultWidget::PresetDefaultWidget(TreeVisualiser *treeVis,
  OpenGLGNodeFactoryPtr factory)
  : PresetWidget{treeVis, factory}
{
  QVBoxLayout *layout = new QVBoxLayout;

  layout->addItem(createSliders());
  setLayout(layout);
}

QLayout *PresetDefaultWidget::createSliders()
{
  QVBoxLayout *layout = new QVBoxLayout;

  sliderTop_ = new UnitSliderWidget{"top: ", this};
  sliderTop_->setValue(factory_->topProportion());
  connect(sliderTop_, &UnitSliderWidget::valueChanged, this, 
    &PresetDefaultWidget::sliderTop_onValueChanged);
  layout->addWidget(sliderTop_);

  sliderLeft_ = new UnitSliderWidget{"left: ", this};
  sliderLeft_->setValue(factory_->leftProportion());
  connect(sliderLeft_, &UnitSliderWidget::valueChanged, this,
    &PresetDefaultWidget::sliderLeft_onValueChanged);
  layout->addWidget(sliderLeft_);

  sliderBottom_ = new UnitSliderWidget{"bottom: ", this};
  sliderBottom_->setValue(factory_->bottomProportion());
  connect(sliderBottom_, &UnitSliderWidget::valueChanged, this,
    &PresetDefaultWidget::sliderBottom_onValueChanged);
  layout->addWidget(sliderBottom_);
  
  sliderRight_ = new UnitSliderWidget{"right: ", this};
  sliderRight_->setValue(factory_->rightProportion());
  connect(sliderRight_, &UnitSliderWidget::valueChanged, this, 
    &PresetDefaultWidget::sliderRight_onValueChanged);
  layout->addWidget(sliderRight_);
  
  return layout;
}

void PresetDefaultWidget::sliderTop_onValueChanged(double val)
{
  factory_->setTopProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetDefaultWidget::sliderLeft_onValueChanged(double val)
{
  factory_->setLeftProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetDefaultWidget::sliderBottom_onValueChanged(double val)
{
  factory_->setBottomProportion(val);
  treeVis_->updateTreeRendering();
}

void PresetDefaultWidget::sliderRight_onValueChanged(double val)
{
  factory_->setRightProportion(val);
  treeVis_->updateTreeRendering();
}