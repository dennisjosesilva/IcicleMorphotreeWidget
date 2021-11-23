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

    qreal  unitWidth() const { return unitWidth_; }
    qreal& unitWidth() { return unitWidth_; }
    void setUnitWidth(qreal val) { unitWidth_ = val; }    

    qreal unitHeight() const { return unitHeight_; }
    qreal& unitHeight() { return unitHeight_; }
    void setUnitHeight(qreal val) { unitHeight_ = val; }

    unsigned int numberOfLevels() const { return numberOfLevels_; }
    unsigned int& numberOfLevels() { return numberOfLevels_; }
    void setNumberOfLevels(unsigned int val) { numberOfLevels_ = val; }

  private:
    qreal unitWidth_;
    qreal unitHeight_;
    unsigned int numberOfLevels_;
  };
}