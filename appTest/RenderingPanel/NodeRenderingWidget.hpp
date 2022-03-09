#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"

class NodeRenderingWidget : public QWidget
{
public:
  using TreeVisuliser = IcicleMorphotreeWidget::IcicleMorphotreeWidget;

  NodeRenderingWidget(TreeVisuliser *treeVis, QWidget *parent=nullptr);

protected:
  QLayout *createTitle(const QString &title);

  QWidget *createHline();
  QWidget *createVline();
protected:
  TreeVisuliser *treeVis_;
};


