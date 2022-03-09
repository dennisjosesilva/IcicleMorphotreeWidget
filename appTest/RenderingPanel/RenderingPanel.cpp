#include "RenderingPanel/RenderingPanel.hpp"

#include "RenderingPanel/FlatRenderingWidget.hpp"

#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QSplitter>

#include <QHBoxLayout>
#include <QVBoxLayout>

RenderingPanel::RenderingPanel(IcicleMorphotreeWidget *treeVis, 
  QWidget *parent)
  : QWidget{parent}, treeVis_{treeVis}
{
  QVBoxLayout *mainLayout = new QVBoxLayout;
  
  mainLayout->addItem(createTitleSection());
  mainLayout->addItem(createRenderingStyleComboSection());  
  mainLayout->addWidget(defaultRenderingMode());
  mainLayout->addStretch();
  setLayout(mainLayout);
}

NodeRenderingWidget *RenderingPanel::defaultRenderingMode()
{
  return new FlatRenderingWidget{treeVis_, this};
}

QLayout *RenderingPanel::createTitleSection()
{
  QLayout *layout = new QVBoxLayout;
  QHBoxLayout *titleLayout = new QHBoxLayout;

  QFont font;
  font.setBold(true);
  font.setPointSize(14);

  QLabel *titleLabel = new QLabel{"Node Rendering Style"};
  titleLabel->setFont(font);
  titleLayout->addStretch();

  titleLayout->addWidget(titleLabel);
  layout->addItem(titleLayout);
  titleLayout->addStretch();

  layout->addWidget(createHLine());  

  return layout;
}

QLayout *RenderingPanel::createRenderingStyleComboSection()
{
  QHBoxLayout *layout = new QHBoxLayout;

  QLabel *label = new QLabel{"Rendering Method: ",this};
  renderingMethodCombo_ = new QComboBox{this};
  renderingMethodCombo_->addItem("Flat", 
    static_cast<int>(NodeRenderingStyle::FLAT));
  renderingMethodCombo_->addItem("Horizontal Gradient", 
    static_cast<int>(NodeRenderingStyle::HGradient));
  renderingMethodCombo_->addItem("Geometry Shader Gradient",
    static_cast<int>(NodeRenderingStyle::GeoShaderGradient));
  renderingMethodCombo_->addItem("Tessellation Shader Gradient",
    static_cast<int>(NodeRenderingStyle::TessShaderGradient));

  layout->addWidget(label);
  layout->addWidget(renderingMethodCombo_);
  layout->setContentsMargins(0, 0, 0, 15);
  return layout;
}


QWidget *RenderingPanel::createHLine() 
{
  QFrame *line = new QFrame{this};
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  return line;
}

QWidget *RenderingPanel::createVLine() 
{
  QFrame *line = new QFrame{this};
  line->setFrameShape(QFrame::VLine);
  line->setFrameShadow(QFrame::Sunken);
  return line;
}