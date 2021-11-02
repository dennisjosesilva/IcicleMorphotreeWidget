#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar.hpp"

#include <QPainter>
#include <QDebug>

namespace IcicleMorphotreeWidget
{
  GrayScaleBar::GrayScaleBar(qreal unitWidth, qreal unitHeight, 
    unsigned int numberOfLevels)
    :unitWidth_{unitWidth}, unitHeight_{unitHeight}, 
     numberOfLevels_{numberOfLevels}
  {
    setZValue(-1);
  }

  QRectF GrayScaleBar::boundingRect() const 
  {
    return QRectF{0, 0, unitWidth_, unitHeight_*numberOfLevels_};
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
    unsigned int L = numberOfLevels_;
    for (unsigned int l=0; l < L; ++l) {
      qreal relLevel = static_cast<qreal>(l) / static_cast<qreal>(L);
      int level = 255 * relLevel;     
      painter->setPen(QPen{Qt::black, 0});
      painter->setBrush(QColor::fromRgb(level, level, level));            
      painter->drawRect(0, static_cast<qreal>(l)*unitHeight_, unitWidth_, unitHeight_);    
    }
  }
}