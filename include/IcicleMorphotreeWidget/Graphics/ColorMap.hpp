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


  // The colourmap class below are based on the lookup tables 
  // downdload from this page: https://colorcet.com/index.html
  class CETColorMap : public ColorMap
  {
  public:
    CETColorMap(const QString &csvFilePath=":/colormap/iso_luminant_01");

    QColor color(float u) const override;

  private:
    void loadLookUpTable(const QString &csvFilePath);

  private:
    QVector<QColor> lookUp_;
  };
}