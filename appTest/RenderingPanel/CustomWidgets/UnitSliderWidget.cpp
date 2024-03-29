#include "RenderingPanel/CustomWidgets/UnitSliderWidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include <QSlider>
#include <QDoubleSpinBox>

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
  emit valueChanged(spinBox_->value());
}

void UnitSliderWidget::spinBox_onValueChanged(double value)
{
  slider_->setValue(static_cast<int>(value * 100));
  emit valueChanged(value);
}

double UnitSliderWidget::value()
{
  return spinBox_->value();
}

void UnitSliderWidget::setValue(double val)
{
  spinBox_->setValue(val);
  emit valueChanged(val);
}