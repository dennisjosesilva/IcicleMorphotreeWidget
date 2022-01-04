#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar.hpp"

#include <QPainter>
#include <QDebug>

namespace IcicleMorphotreeWidget
{
  GrayScaleBar::GrayScaleBar(qreal unitWidth, qreal unitHeight, 
    unsigned int numberOfLevels, TreeLayoutOrientation orientation)
    :unitWidth_{unitWidth}, unitHeight_{unitHeight}, 
     numberOfLevels_{numberOfLevels},
     showBorders_{true},
     orientation_{orientation}
  {
    setZValue(-1);
  }

  QRectF GrayScaleBar::boundingRect() const 
  {
    if (orientation_ == TreeLayoutOrientation::Vertical)
      return QRectF{0, 0, unitWidth_, unitHeight_*numberOfLevels_};
    else 
      return QRectF{0, 0, unitWidth_*numberOfLevels_, unitHeight_};
  }

  QPainterPath GrayScaleBar::shape() const 
  {
    QPainterPath path;
    path.addRect(0, 0, unitWidth_, unitHeight_*numberOfLevels_);    
    return path;
  }

  void GrayScaleBar::paint(QPainter *painter, 
    const QStyleOptionGraphicsItem *options, QWidget *)
  {  
    switch (orientation_)
    {
    case TreeLayoutOrientation::Vertical:
      paintVertical(painter);
      break;
    
    case TreeLayoutOrientation::Horizontal:
      paintHorizontal(painter);
      break;
    }
  }

  void GrayScaleBar::paintVertical(QPainter *painter)
  {
    unsigned int L = numberOfLevels_;
    for (unsigned int l=0; l < L; ++l) {
      qreal relLevel = static_cast<qreal>(l) / static_cast<qreal>(L);
      int level = 255 * relLevel;     
      
      if (showBorders_){
        painter->setPen(QPen{Qt::black, 0});
      }
      else {
        painter->setPen(QColor::fromRgb(level, level, level));
      }

      painter->setBrush(QColor::fromRgb(level, level, level));            
      painter->drawRect(0, static_cast<qreal>(l)*unitHeight_, unitWidth_, unitHeight_);    
    }
  }

  void GrayScaleBar::paintHorizontal(QPainter *painter)
  {
    unsigned int L = numberOfLevels_;
    for (unsigned int l = 0; l < L; ++l) {
      qreal relLevel = static_cast<qreal>(l) / static_cast<qreal>(L);
      int level = 255 * relLevel;

      if (showBorders_) {
        painter->setPen(QPen{Qt::black});
      }
      else {
        painter->setPen(QColor::fromRgb(level, level, level));
      }

      painter->setBrush(QColor::fromRgb(level, level, level));
      painter->drawRect(static_cast<qreal>(l) * unitWidth_, 0, unitWidth_, unitHeight_);
    }
  }
}