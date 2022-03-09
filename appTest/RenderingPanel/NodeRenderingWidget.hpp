#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"

class NodeRenderingWidget : public QWidget
{
public:
  using IcicleMorphotreeWidget = IcicleMorphotreeWidget::IcicleMorphotreeWidget;

  NodeRenderingWidget(IcicleMorphotreeWidget *treeVis, QWidget *parent=nullptr);

protected:
  IcicleMorphotreeWidget *treeVis_;
};