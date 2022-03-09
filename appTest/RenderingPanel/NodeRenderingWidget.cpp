#include "RenderingPanel/NodeRenderingWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include <QSlider>
#include <QDoubleSpinBox>

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
  titleLayout->addStretch();
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

// ============== [ UNIT SLIDER WIDGET ] ========================
UnitSliderWidget::UnitSliderWidget(const QString &labelText, 
  QWidget *parent)
{
  QHBoxLayout *layout = new QHBoxLayout;

  label_ = new QLabel{labelText, this};
  layout->addWidget(label_);

  slider_ = new QSlider{this};
  slider_->setRange(0.0, 100);
  slider_->setSingleStep(1);
  slider_->setOrientation(Qt::Horizontal);
  connect(slider_, &QSlider::sliderMoved, this, 
    &UnitSliderWidget::slider_onSliderMoved);
  layout->addWidget(slider_);

  spinBox_ = new QDoubleSpinBox{this};
  spinBox_->setRange(0.0, 1.0);
  spinBox_->setSingleStep(0.01);
  connect(spinBox_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
    this, &UnitSliderWidget::spinBox_onValueChanged);
  layout->addWidget(spinBox_);

  setLayout(layout);
}

void UnitSliderWidget::setLabelText(const QString &labelText)
{
  label_->setText(labelText);
}

QString UnitSliderWidget::labelText()
{
  return label_->text();
}

void UnitSliderWidget::slider_onSliderMoved(int value)
{
  spinBox_->setValue(static_cast<double>(value) / 100.0);
}

void UnitSliderWidget::spinBox_onValueChanged(double value)
{
  slider_->setValue(static_cast<int>(value * 100));
}

double UnitSliderWidget::value()
{
  return spinBox_->value();
}

void UnitSliderWidget::setValue(double val)
{
  spinBox_->setValue(val);
}