#include "RenderingPanel/FlatRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

FlatRenderingWidget::FlatRenderingWidget(TreeVisuliser *treeVis,
  QWidget *parent)
  : NodeRenderingWidget{treeVis, parent}
{
  QVBoxLayout *layout = new QVBoxLayout;

  setupGNodeFactory();
  layout->addItem(createTitle("Flat Rendering"));
  layout->addItem(createMessage());

  setLayout(layout);
}

void FlatRenderingWidget::setupGNodeFactory()
{
  factory_ = std::make_shared<FixedColorGNodeFactory>(treeVis_);
  treeVis_->setGNodeFactory(factory_);
  treeVis_->updateTreeRendering();
}

QLayout *FlatRenderingWidget::createMessage()
{
  QHBoxLayout *layout = new QHBoxLayout;
  QLabel *label = new QLabel{
      "Flat Rendering has no parameter for tunning."};
  layout->addWidget(label);
  return layout;
}