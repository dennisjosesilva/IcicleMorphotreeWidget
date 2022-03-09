#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"

class NodeRenderingWidget : public QWidget
{
public:
  using IcicleMorphotreeWidget = IcicleMorphotreeWidget::IcicleMorphotreeWidget;

  NodeRenderingWidget(IcicleMorphotreeWidget *treeVis, QWidget *parent=nullptr);

protected:
  QLayout *createTitle(const QString &title);

  QWidget *createHline();
  QWidget *createVline();
protected:
  IcicleMorphotreeWidget *treeVis_;
};


class QSlider;
class QDoubleSpinBox;
class QLabel;

class UnitSliderWidget : public QWidget
{
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

protected:
  QLabel *label_;
  QSlider *slider_;
  QDoubleSpinBox *spinBox_;
};