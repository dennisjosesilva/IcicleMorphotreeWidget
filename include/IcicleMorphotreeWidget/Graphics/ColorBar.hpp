#pragma once

#include <QWidget>
#include <QColor>
#include <QLinearGradient>

#include "IcicleMorphotreeWidget/Graphics/ColorMap.hpp"

namespace IcicleMorphotreeWidget
{
  class ColorBar : public QWidget
  {
    Q_OBJECT
  
  public:
    ColorBar(ColorMap *colorMap, QWidget *parent=nullptr);

    inline float maxValue() const { return maxValue_; }
    inline float minValue() const { return minValue_; }
    inline void setMaxValue(float val) { maxValue_ = val; }
    inline void setMinValue(float val) { minValue_ = val; }

    inline bool showNumbers() const { return showNumbers_; }
    inline void setShowNumbers(bool show) { showNumbers_ = show; }

  protected:
    ColorMap *colorMap_;
    QLinearGradient gradient_;

    bool showNumbers_;
    float maxValue_;
    float minValue_;
  };

  class VColorBar : public ColorBar 
  {
    Q_OBJECT
  
  public:
    VColorBar(ColorMap *colorMap, QWidget *parent=nullptr);
    void paintEvent(QPaintEvent *event) override;
  };

  class HColorBar : public ColorBar
  {
    Q_OBJECT
  
  public:
    HColorBar(ColorMap *colorMap, QWidget *parent=nullptr);
    void paintEvent(QPaintEvent *event) override;
  };
}