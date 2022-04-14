#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "RenderingPanel/NodeRenderingWidget.hpp"

#include <QWidget>

class QLayout;
class QComboBox;

enum NodeRenderingStyle {
  FLAT = 0,
  HGradient = 1,
  GeoShaderGradient = 2,
  TessShaderGradient = 3,
  TessFunctionShader = 4,
  BezierFuncShader = 5
};


class RenderingPanel : public QWidget
{
public:
  using IcicleMorphotreeWidget = IcicleMorphotreeWidget::IcicleMorphotreeWidget;

  RenderingPanel(IcicleMorphotreeWidget *treeVis, QWidget *parent=nullptr);

  void changeNodeRendering(NodeRenderingWidget *curNodeRendering);

protected:
  QLayout *createTitleSection();
  QLayout *createRenderingStyleComboSection();

  QWidget *createHLine();
  QWidget *createVLine();

  NodeRenderingWidget *defaultRenderingMode();

protected slots:
  void renderingMethodCombo_onCurrentIndexChanged(int index);

protected:
  IcicleMorphotreeWidget *treeVis_;
  NodeRenderingWidget *curNodeRendering_;
  QComboBox *renderingMethodCombo_;
};