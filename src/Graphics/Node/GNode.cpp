#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/GNodeEventHandler.hpp"

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

  void GNode::mousePressEvent(QGraphicsSceneMouseEvent *e)
  {
    GNodeEventHandler::Singleton()->emitMousePress(this, e);
    // e->accept();
    QGraphicsItem::mousePressEvent(e);
  }

  void GNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
  {
    GNodeEventHandler::Singleton()->emitMouseRelease(this, e);
    // e->accept();
    QGraphicsItem::mouseReleaseEvent(e);
  }

  void GNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
  {
    GNodeEventHandler::Singleton()->emitMouseDoubleClick(this, e);
    // e->accept();
    QGraphicsItem::mouseDoubleClickEvent(e);
  }

  // ====================== Fixed Color Graphical Node =================
  FixedColorGNode::FixedColorGNode(IcicleMorphotreeWidget *treeVis,
    MTreeNodePtr mnode)
    : GNode{treeVis, mnode}
  {}
  
  void FixedColorGNode::paint(QPainter *painter, 
    const QStyleOptionGraphicsItem *options, QWidget *)
  {
    QRectF r = boundingRect();

    if (isSelected_) {
      if (height_ < 5.0f)
        painter->setPen(QPen(Qt::black, 1));            
      else
        painter->setPen(QPen(Qt::black, 3));            

      painter->setBrush(backgroundColor_);
      painter->drawRect(boundingRect());
    }
    else {
      painter->setPen(QPen{Qt::darkGray, 0});      
      painter->setBrush(backgroundColor_);
      painter->drawRect(r);
    }
  }
      

  // ====================== Gradient Graphical Node ====================
  GradientGNode::GradientGNode(IcicleMorphotreeWidget *treeVis, 
    MTreeNodePtr mnode, float gradientProportion)
    : GNode{treeVis, mnode}, 
      gradientProportion_{gradientProportion}
  {}
  
  // =============== Horizontal Gradient Graphical Node ====================
  HGradientGNode::HGradientGNode(IcicleMorphotreeWidget *treeVis, 
    MTreeNodePtr mnode, float gradientProportion)
    : GradientGNode{treeVis, mnode, gradientProportion}
  {}
  
  void HGradientGNode::paint(QPainter *painter, 
    const QStyleOptionGraphicsItem *options, QWidget *)
  {
    QRectF r = boundingRect();
    QColor start = backgroundColor_;
    const QColor end{
      static_cast<int>(backgroundColor_.red() * gradientProportion_),
      static_cast<int>(backgroundColor_.green() * gradientProportion_),
      static_cast<int>(backgroundColor_.blue() * gradientProportion_)};

    QLinearGradient linearGradient(r.x(), r.y(), r.right(), r.y());
    linearGradient.setColorAt(0.0, start);
    linearGradient.setColorAt(1.0, end);

    if (isSelected_) {
      if (height_ < 5.0f)
        painter->setPen(QPen(Qt::black, 1));            
      else
        painter->setPen(QPen(Qt::black, 3));            

      painter->setBrush(linearGradient);
      painter->drawRect(boundingRect());
    }
    else {
      painter->setPen(Qt::NoPen);      
      painter->setBrush(linearGradient);
      painter->drawRect(r);
    }
  }

  // ============= Vertical Gradient Graphical Node =======================
  VGradientGNode::VGradientGNode(IcicleMorphotreeWidget *treeVis, 
    MTreeNodePtr mnode, float gradientProportion)
    : GradientGNode{treeVis, mnode, gradientProportion}
  {}

  void VGradientGNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
    QWidget *)
  {
    QRectF r = boundingRect();
    QColor start = backgroundColor_;
    const QColor end{
      static_cast<int>(backgroundColor_.red() * gradientProportion_),
      static_cast<int>(backgroundColor_.green() * gradientProportion_),
      static_cast<int>(backgroundColor_.blue() * gradientProportion_)
    };

    QLinearGradient linearGradient{r.x(), r.y(), r.x(), r.bottom()};
    linearGradient.setColorAt(0.0, start);
    linearGradient.setColorAt(1.0, end);

    if (isSelected_) {
      if (width_ < 5.0f) 
        painter->setPen(QPen(Qt::black, 1));
      else 
        painter->setPen(QPen(Qt::black, 3));

      painter->setBrush(linearGradient);
      painter->drawRect(boundingRect());
    }
    else {
      painter->setPen(Qt::NoPen);
      painter->setBrush(linearGradient);
      painter->drawRect(r);
    }
  }
}