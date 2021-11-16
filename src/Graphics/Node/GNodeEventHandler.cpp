#include "IcicleMorphotreeWidget/Graphics/Node/GNodeEventHandler.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

namespace IcicleMorphotreeWidget
{
  GNodeEventHandler *GNodeEventHandler::singleton_ = nullptr;

  GNodeEventHandler::GNodeEventHandler()
    :QObject()
  {}

  GNodeEventHandler* GNodeEventHandler::Singleton() 
  {
    if (singleton_ == nullptr) 
      singleton_ = new GNodeEventHandler;
    return singleton_;
  }

  void GNodeEventHandler::emitMousePress(GNode *node, 
    QGraphicsSceneMouseEvent *e)
  {
    emit mousePress(node, e);
  }

  void GNodeEventHandler::emitMouseRelease(GNode *node,
    QGraphicsSceneMouseEvent *e)
  {
    emit mouseRelease(node, e);
  }

  void GNodeEventHandler::emitMouseDoubleClick(GNode *node,
    QGraphicsSceneMouseEvent *e)
  {
    emit mouseDoubleClick(node, e);
  }
}