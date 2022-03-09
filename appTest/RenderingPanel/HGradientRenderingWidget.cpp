#include "RenderingPanel/HGradientRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>

HGradientRenderingWidget::HGradientRenderingWidget(IcicleMorphotreeWidget *treeVis,
  QWidget *parent)
  :NodeRenderingWidget{treeVis, parent}
{
  QVBoxLayout *layout = new QVBoxLayout;

  layout->addItem(createTitle("Horizontal Gradient Rendering"));
  layout->addWidget(new UnitSliderWidget{"proportion: ", this});

  setLayout(layout);
}