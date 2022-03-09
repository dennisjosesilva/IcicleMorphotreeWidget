#pragma once

#include <QWidget>

class QSlider;
class QDoubleSpinBox;
class QLabel;

class UnitSliderWidget : public QWidget
{
  Q_OBJECT
public:
  UnitSliderWidget(const QString &labelText,
    QWidget *parent=nullptr);

  void setLabelText(const QString &labelText);
  QString labelText();

  double value();
  void setValue(double val);

protected slots:
  void slider_onSliderMoved(int value);
  void spinBox_onValueChanged(double value);
       
public:
signals:
  void valueChanged(double value);

protected:
  QLabel *label_;
  QSlider *slider_;
  QDoubleSpinBox *spinBox_;
};