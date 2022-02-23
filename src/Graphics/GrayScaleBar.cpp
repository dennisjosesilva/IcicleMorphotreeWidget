#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar.hpp"

#include <QPainter>
#include <QDebug>

namespace IcicleMorphotreeWidget
{
  GrayScaleBar::GrayScaleBar(const GrayScaleProfile &grayscaleProfile,
    qreal unitWidth, qreal unitHeight, TreeLayoutOrientation orientation,
    MorphoTreeType mtreeType)
    :grayscaleProfile_{grayscaleProfile},
     unitWidth_{unitWidth}, unitHeight_{unitHeight}, 
     showBorders_{true},
     orientation_{orientation},
     mtreeType_{mtreeType}
  {
    setZValue(-1);
  }

  QRectF GrayScaleBar::boundingRect() const 
  {
    int N = grayscaleProfile_.irange().numberOfElements();
    if (orientation_ == TreeLayoutOrientation::Vertical)
      return QRectF{0, 0, unitWidth_, unitHeight_ * N};
    else 
      return QRectF{0, 0, unitWidth_*N, unitHeight_};
  }

  QPainterPath GrayScaleBar::shape() const 
  {
    QPainterPath path;
    int N = grayscaleProfile_.irange().numberOfElements();
    if (orientation_ == TreeLayoutOrientation::Vertical)
      path.addRect(0, 0, unitWidth_, unitHeight_*N);    
    else
      path.addRect(0, 0, unitWidth_ * N, unitHeight_);

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
    const Range &irange = grayscaleProfile_.irange();
    int N = irange.numberOfElements();
    for (unsigned int i=0;  i < N; ++i) {      
      int l;
      if (mtreeType_ == MorphoTreeType::MAX_TREE_8C || 
        mtreeType_ == MorphoTreeType::MAX_TREE_4C)
        l = i + irange.min;
      else if (mtreeType_ == MorphoTreeType::MIN_TREE_4C || 
        mtreeType_ == MorphoTreeType::MIN_TREE_8C) 
        l = irange.max - i;

      int level = grayscaleProfile_.grayLevel(l);
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
    const Range &irange = grayscaleProfile_.irange();
    const int N = irange.numberOfElements();
    for (int i = 0; i < N; ++i) {
      int l;
      if (mtreeType_ == MorphoTreeType::MAX_TREE_4C || 
        mtreeType_ == MorphoTreeType::MAX_TREE_8C) 
        l = i +irange.min;
      else if (mtreeType_ == MorphoTreeType::MIN_TREE_4C ||
        mtreeType_ == MorphoTreeType::MIN_TREE_8C)
        l = irange.max - i;

      int level = grayscaleProfile_.grayLevel(l);
      if (showBorders_) {
        painter->setPen(QPen{Qt::black, 0});
      }
      else {
        painter->setPen(QColor::fromRgb(level, level, level));
      }

      painter->setBrush(QColor::fromRgb(level, level, level));
      painter->drawRect(static_cast<qreal>(l) * unitWidth_, 0, unitWidth_, unitHeight_);
    }
  }
}