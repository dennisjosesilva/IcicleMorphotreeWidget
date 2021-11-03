#pragma once 

#include <QGraphicsItem>

namespace IcicleMorphotreeWidget
{
  class GrayScaleBar : public QGraphicsItem
  {
  public:
    GrayScaleBar(qreal unitWidth = 20.f, qreal unitHeight = 20.f,
      unsigned int numberOfLevels=256);

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, 
      QWidget *widget);

    qreal unitWidth() const { return unitWidth_; }
    qreal unitHeight() const { return unitHeight_; }
    unsigned int numberOfLevels() const { return numberOfLevels_; }

  private:
    qreal unitWidth_;
    qreal unitHeight_;
    unsigned int numberOfLevels_;
  };
}