#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNodeFactory.hpp"
#include "RenderingPanel/CustomWidgets/UnitSliderWidget.hpp"

#include "NodeRenderingWidget.hpp"
#include <QWidget>

class PresetWidget;
class QComboBox;
class QDoubleSpinBox;

enum GeoShaderPresetType {
  None,
  Default,
  Flat,
  Vertical,
  Horizontal,
  SymmetricTentLikeCushion,
  AsymmetricTentLikeCushion
};

class GeoShaderRenderingWidget : public NodeRenderingWidget
{
  Q_OBJECT
public:
  using OpenGLGNodeFactory = IcicleMorphotreeWidget::OpenGLGNodeFactory;
  using OpenGLGNodeFactoryPtr = std::shared_ptr<OpenGLGNodeFactory>;

  GeoShaderRenderingWidget(TreeVisuliser *treeVis, QWidget *parent=nullptr);

  void changePresetWidget(PresetWidget *presetWidget);

protected:
  QLayout *createPresetComboBox();
  void setupGNodeFactory();

protected slots:
  void presetComboBox_onCurrentIndexChanged(int index);

protected:
  QComboBox *presetComboBox_;
  OpenGLGNodeFactoryPtr factory_;  
  PresetWidget *presetWidget_;
};

class PresetWidget : public QWidget 
{
Q_OBJECT
public:
  using TreeVisualiser = IcicleMorphotreeWidget::IcicleMorphotreeWidget;
  using OpenGLGNodeFactory = IcicleMorphotreeWidget::OpenGLGNodeFactory;
  using OpenGLGNodeFactoryPtr = std::shared_ptr<OpenGLGNodeFactory>;

  PresetWidget(TreeVisualiser *treeVis, OpenGLGNodeFactoryPtr factory);
  
protected:
  TreeVisualiser *treeVis_;
  OpenGLGNodeFactoryPtr factory_;
};

class PresetNoneWidget : public PresetWidget
{
Q_OBJECT
public:
  PresetNoneWidget(TreeVisualiser *treeVis, OpenGLGNodeFactoryPtr factory);

protected:
  QLayout *createSliders();

protected slots:
  void sliderTop_onValueChanged(double val);
  void sliderLeft_onValueChanged(double val);
  void sliderBottom_onValueChanged(double val);
  void sliderRight_onValueChanged(double val);
  void sliderCenter_onValueChanged(double val);
  void sliderTopLeft_onValueChanged(double val);
  void sliderTopRight_onValueChanged(double val);
  void sliderBottomLeft_onValueChanged(double val);
  void sliderBottomRight_onValueChanged(double val);

protected:
  UnitSliderWidget *sliderTop_;
  UnitSliderWidget *sliderLeft_;
  UnitSliderWidget *sliderBottom_;
  UnitSliderWidget *sliderRight_;

  UnitSliderWidget *sliderCenter_;

  UnitSliderWidget *sliderTopLeft_;
  UnitSliderWidget *sliderTopRight_;
  UnitSliderWidget *sliderBottomLeft_;
  UnitSliderWidget *sliderBottomRight_;
};

class PresetDefaultWidget : public PresetWidget
{
Q_OBJECT
public:
  using DefaultPreset = IcicleMorphotreeWidget::DefaultPreset;
  PresetDefaultWidget(TreeVisualiser *treeVis, OpenGLGNodeFactoryPtr factory);

protected:
  QLayout *createSliders();

protected slots:
  void sliderTop_onValueChanged(double val);
  void sliderLeft_onValueChanged(double val);
  void sliderBottom_onValueChanged(double val);
  void sliderRight_onValueChanged(double val);

protected:
  UnitSliderWidget *sliderTop_;
  UnitSliderWidget *sliderLeft_;
  UnitSliderWidget *sliderBottom_;
  UnitSliderWidget *sliderRight_;

  std::unique_ptr<DefaultPreset> preset_;
};

class PresetFlatWidget : public PresetWidget
{
Q_OBJECT
public:
  using FlatPreset = IcicleMorphotreeWidget::FlatPreset;
  PresetFlatWidget(TreeVisualiser *treeVis, OpenGLGNodeFactoryPtr factory);

protected:
  QLayout *createMessage();

protected:
  std::unique_ptr<FlatPreset> preset_;
};

class PresetVerticalWidget : public PresetWidget
{
Q_OBJECT
public:
  using VerticalPreset = IcicleMorphotreeWidget::VerticalPreset;
  PresetVerticalWidget(TreeVisualiser *treeVis, OpenGLGNodeFactoryPtr factory);

protected:
  QLayout *createSliders();

protected slots:
  void sliderTop_onValueChanged(double val);
  void sliderBottom_onValueChanged(double val);

protected:
  UnitSliderWidget *sliderTop_;
  UnitSliderWidget *sliderBottom_;

  std::unique_ptr<VerticalPreset> preset_;
};

class PresetHorizontalWidget : public PresetWidget
{
Q_OBJECT
public:
  using HorizontalPreset = IcicleMorphotreeWidget::HorinzontalPreset;
  PresetHorizontalWidget(TreeVisualiser *treeVis, OpenGLGNodeFactoryPtr factory);

protected:
  QLayout *createSliders();

protected slots:
  void sliderLeft_onValueChanged(double val);
  void sliderRight_onValueChanged(double val);

protected:
  std::unique_ptr<HorizontalPreset> preset_;
  UnitSliderWidget *sliderLeft_;
  UnitSliderWidget *sliderRight_;
};

class PresetSymmetricTentLikeCushionWidget : public PresetWidget
{
Q_OBJECT
public:  
  using SymmetricTentLikeCushionPreset = IcicleMorphotreeWidget::SymmetricTentLikeCushion;
  PresetSymmetricTentLikeCushionWidget(TreeVisualiser *treeVis, 
    OpenGLGNodeFactoryPtr factory);
  
protected:
  QLayout *createSliders();

protected slots:
  void sliderCorner_onValueChanged(double val);
  void sliderSide_onValueChanged(double val);

protected:
  UnitSliderWidget *sliderCorner_;
  UnitSliderWidget *sliderSide_;

  std::unique_ptr<SymmetricTentLikeCushionPreset> preset_;
};

class PresetAsymmetricTentLikeCushionWidget : public PresetWidget
{
Q_OBJECT
public:
  using AsymmetricTentLikeCushionPreset = IcicleMorphotreeWidget::AsymetricTentLikeCushion;
  PresetAsymmetricTentLikeCushionWidget(TreeVisualiser *treeVis, 
    OpenGLGNodeFactoryPtr factory);

protected:
  QLayout *createControls();

protected slots:
  void sliderCorner_onValueChanged(double val);
  void sliderSide_onValueChanged(double val);
  void spinBoxIncreaseFactor_onValueChanged(double val);

protected:
  std::unique_ptr<AsymmetricTentLikeCushionPreset> preset_;

  UnitSliderWidget *sliderCorners_;
  UnitSliderWidget *sliderSides_;
  QDoubleSpinBox *spinBoxIncreaseFactor_;
};