#pragma once 

#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"
#include "IcicleMorphotreeWidget/MorphoTreeType.hpp"
#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar/GrayScaleProfile.hpp"
#include <QGraphicsItem>

namespace IcicleMorphotreeWidget
{
  class GrayScaleBar : public QGraphicsItem
  {
  public:
    GrayScaleBar(const GrayScaleProfile &grayscaleProfile={Range{0,255}, Range{0, 255}},
      qreal unitWidth = 20.f, qreal unitHeight = 20.f,      
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
 
    bool showBorders() const { return showBorders_; }
    bool &showBorders() { return showBorders_; }
    void setShowBorders(bool val) { showBorders_ = val; }

    TreeLayoutOrientation &orientation() { return orientation_; }
    TreeLayoutOrientation orientation() const { return orientation_; }
    void setOrientation(TreeLayoutOrientation val) { orientation_ = val; } 

    const GrayScaleProfile &grayscaleProfile() const { return grayscaleProfile_; }
    void setGrayscaleProfile(const GrayScaleProfile &val) { grayscaleProfile_ = val; }

    MorphoTreeType mtreeType() const { return mtreeType_; }
    MorphoTreeType &mtreeType() { return mtreeType_; }
    void setMTreeType(MorphoTreeType val) { mtreeType_ = val; }

  private:
    void paintVertical(QPainter *painter);
    void paintHorizontal(QPainter *painter);

  private:
    qreal unitWidth_;
    qreal unitHeight_;
    TreeLayoutOrientation orientation_;
    bool showBorders_;
    MorphoTreeType mtreeType_;

    GrayScaleProfile grayscaleProfile_;
  };
}