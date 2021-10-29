#include "IcicleMorphotreeWidget/Graphics/GNode.hpp"
#include "IcicleMorphotreeWidget/Graphics/GNodeEventHandler.hpp"

#include <QSizeF>
#include <QPointF>
#include <QPainter>

#include <string>


namespace IcicleMorphotreeWidget
{
  GNode::GNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode)
    :treeVis_{treeVis},
     mnode_{mnode},
     isSelected_{false},
     backgroundColor_{Qt::lightGray}
  {
    setZValue(-1);
  }

  QRectF GNode::boundingRect() const
  {
    return QRectF{0,0, width_, height_};
  }

  QPainterPath GNode::shape() const 
  {
    QPainterPath path;
    path.addRect(0, 0, width_, height_);
    return path;
  }

  void GNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *options,
    QWidget *)
  {
    if (isSelected_) {
      painter->setPen(QPen(Qt::black, 3));
      painter->setBrush(backgroundColor_);
      painter->drawRect(boundingRect());
    }
    else {
      painter->setPen(QPen{Qt::darkGray, 0});
      painter->setBrush(backgroundColor_);
      painter->drawRect(boundingRect());
    }
  }

  void GNode::mousePressEvent(QGraphicsSceneMouseEvent *e)
  {
    GNodeEventHandler::Singleton()->emitMousePress(this, e);
    e->accept();
  }

  void GNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
  {
    GNodeEventHandler::Singleton()->emitMouseRelease(this, e);
    e->accept();
  }

  void GNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
  {
    GNodeEventHandler::Singleton()->emitMouseDoubleClick(this, e);
    e->accept();
  }
}