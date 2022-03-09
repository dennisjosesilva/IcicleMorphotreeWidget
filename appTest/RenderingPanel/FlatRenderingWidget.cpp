#include "RenderingPanel/FlatRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

FlatRenderingWidget::FlatRenderingWidget(IcicleMorphotreeWidget *treeVis,
  QWidget *parent)
  : NodeRenderingWidget{treeVis, parent}
{
  QVBoxLayout *layout = new QVBoxLayout;

  layout->addItem(createTitle("Flat Rendering"));
  layout->addItem(createMessage());

  setLayout(layout);
}

QLayout *FlatRenderingWidget::createMessage()
{
  QHBoxLayout *layout = new QHBoxLayout;
  QLabel *label = new QLabel{
      "Flat Rendering has no parameter for tunning."};
  layout->addWidget(label);
  return layout;
}