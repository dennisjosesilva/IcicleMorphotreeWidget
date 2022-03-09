#include "RenderingPanel/NodeRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

NodeRenderingWidget::NodeRenderingWidget(IcicleMorphotreeWidget *treeVis, 
  QWidget *parent)
  :QWidget{parent}, treeVis_{treeVis}
{}

QLayout *NodeRenderingWidget::createTitle(const QString &title)
{
  QVBoxLayout *layout = new QVBoxLayout;
  QHBoxLayout *titleLayout = new QHBoxLayout;
  
  QFont font;
  font.setBold(true);  
  font.setPointSize(14);

  QLabel *titleLabel = new QLabel{title};
  titleLabel->setAlignment(Qt::AlignHCenter);
  titleLabel->setFont(font);

  titleLayout->addWidget(titleLabel);
  layout->addItem(titleLayout);
  titleLayout->addStretch();
  
  layout->addWidget(createHline());

  return layout;
}

QWidget *NodeRenderingWidget::createHline()
{
  QFrame *line = new QFrame{this};
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  return line;
}

QWidget *NodeRenderingWidget::createVline()
{
  QFrame *line = new QFrame{this};
  line->setFrameShape(QFrame::VLine);
  line->setFrameShadow(QFrame::Sunken);
  return line;
}