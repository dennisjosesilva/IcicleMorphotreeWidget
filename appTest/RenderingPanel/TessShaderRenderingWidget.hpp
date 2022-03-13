#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/TessBLGradientNodeFactory.hpp"
#include "RenderingPanel/CustomWidgets/UnitSliderWidget.hpp"

#include "NodeRenderingWidget.hpp"
#include <QWidget>

class TessBLShaderPresetWidget;
class QComboBox;

enum TessShaderPresetType {
  TessNone,
  TessBottomRightLShaped,
  TessTopLeftLShaped
};

class TessShaderRenderingWidget : public NodeRenderingWidget
{
Q_OBJECT
public:
  using TessBLGradientNodeFactory = IcicleMorphotreeWidget::TessBLGradientNodeFactory;
  using TessBLGradientNodeFactoryPtr = std::shared_ptr<TessBLGradientNodeFactory>;

  TessShaderRenderingWidget(TreeVisuliser *treeVis, QWidget *parent=nullptr);

  void changePresetWidget(TessBLShaderPresetWidget *presetWidget);

protected:
  QLayout *createPresetComboBox();
  void setupGNodeFactory();

protected slots:
  void presetComboBox_onCurrentIndexChanged(int index);

protected:
  QComboBox *presetComboBox_;
  TessBLGradientNodeFactoryPtr factory_;
  TessBLShaderPresetWidget *presetWidget_;
};

class TessBLShaderPresetWidget : public QWidget
{
Q_OBJECT
public:
  using TreeVisualiser = IcicleMorphotreeWidget::IcicleMorphotreeWidget;
  using TessBLGradientNodeFactory = IcicleMorphotreeWidget::TessBLGradientNodeFactory;
  using TessBLGradientNodeFactoryPtr = std::shared_ptr<TessBLGradientNodeFactory>;

  TessBLShaderPresetWidget(TreeVisualiser *treeVis, TessBLGradientNodeFactoryPtr factory);

protected:
  TreeVisualiser *treeVis_;
  TessBLGradientNodeFactoryPtr factory_;
};

class TessBLShaderPresetNoneWidget : public TessBLShaderPresetWidget
{
Q_OBJECT
public:
  TessBLShaderPresetNoneWidget(TreeVisualiser *treeVis, TessBLGradientNodeFactoryPtr factory);

protected:
  QLayout *createSliders();

protected slots:
  void sliderTopLeft_onValueChanged(double val);
  void sliderTopRight_onValueChanged(double val);
  void sliderBottomLeft_onValueChanged(double val);
  void sliderBottomRight_onValueChanged(double val);

protected:
  UnitSliderWidget *sliderTopLeft_;
  UnitSliderWidget *sliderTopRight_;
  UnitSliderWidget *sliderBottomLeft_;
  UnitSliderWidget *sliderBottomRight_;
};

class TessBLShaderPresetLShapedBottomRightWidget : public TessBLShaderPresetWidget
{
Q_OBJECT
public:
  using TessBLBottomRightLShaderPreset
    = IcicleMorphotreeWidget::TessBLBottomRightLShapedPreset;
  using TessBLBottomRightLShaderPresetPtr = 
    std::unique_ptr<TessBLBottomRightLShaderPreset>;

  TessBLShaderPresetLShapedBottomRightWidget(TreeVisualiser *treeVis, 
    TessBLGradientNodeFactoryPtr factory);

protected: 
  QLayout *createSliders();

protected slots:
  void sliderDarkProportion__onValueChanged(double val);

protected:
  UnitSliderWidget *sliderDarkProportion_;
  TessBLBottomRightLShaderPresetPtr preset_;
};

class TessBLShaderPresetLShapedTopLeftWidget : public TessBLShaderPresetWidget
{
Q_OBJECT
public:  
  using TessBLTopLeftLShapedPreset = 
    IcicleMorphotreeWidget::TessBLTopLeftLShapedPreset;
  using TessBLTopLeftLShapedPresetPtr = 
    std::unique_ptr<TessBLTopLeftLShapedPreset>;

  TessBLShaderPresetLShapedTopLeftWidget(TreeVisualiser *treeVis, 
    TessBLGradientNodeFactoryPtr factory);

protected:
  QLayout *createSliders();

protected slots:
  void sliderDarkProportion__onValueChanged(double val);

protected:
  UnitSliderWidget *sliderDarkProportion_;
  TessBLTopLeftLShapedPresetPtr preset_;
};