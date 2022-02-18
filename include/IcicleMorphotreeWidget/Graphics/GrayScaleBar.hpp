#pragma once 

#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"
#include "IcicleMorphotreeWidget/MorphoTreeType.hpp"
#include <QGraphicsItem>

namespace IcicleMorphotreeWidget
{
  class GrayScaleBar : public QGraphicsItem
  {
  public:
    GrayScaleBar(qreal unitWidth = 20.f, qreal unitHeight = 20.f,
      unsigned int numberOfLevels=256, 
      TreeLayoutOrientation orientation = TreeLayoutOrientation::Vertical,
      MorphoTreeType mtreeType=MorphoTreeType::MAX_TREE_8C);

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

    bool showBorders() const { return showBorders_; }
    bool &showBorders() { return showBorders_; }
    void setShowBorders(bool val) { showBorders_ = val; }

    TreeLayoutOrientation &orientation() { return orientation_; }
    TreeLayoutOrientation orientation() const { return orientation_; }
    void setOrientation(TreeLayoutOrientation val) { orientation_ = val; } 

  private:
    void paintVertical(QPainter *painter);
    void paintHorizontal(QPainter *painter);

  private:
    qreal unitWidth_;
    qreal unitHeight_;
    unsigned int numberOfLevels_;
    TreeLayoutOrientation orientation_;
    bool showBorders_;
    MorphoTreeType mtreeType_;
  };
}