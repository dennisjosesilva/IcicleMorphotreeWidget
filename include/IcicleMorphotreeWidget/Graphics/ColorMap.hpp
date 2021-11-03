#pragma once 

#include <QWidget>
#include <QColor>
#include <QLinearGradient>

namespace IcicleMorphotreeWidget
{
  // Forward declaration;
  class VColorBar;
  class HColorBar;

  class ColorMap
  {
  public:
    virtual QColor color(float u) const = 0;

    VColorBar *createVColorBar(QWidget *parent=nullptr);
    HColorBar *createHColorBar(QWidget *parent=nullptr);
  };

  class RainbowColorMap : public ColorMap
  {
  public:
    RainbowColorMap(float dx = 0.8f);

    QColor color(float u) const override;

  private:
    float dx_;
  };
}