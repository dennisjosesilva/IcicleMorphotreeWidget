#pragma once 

#include <QObject>
#include <QGraphicsSceneMouseEvent>

namespace IcicleMorphotreeWidget
{
  class GNode;

  class GNodeEventHandler : public QObject 
  {
    Q_OBJECT
  public:
    GNodeEventHandler();
    static GNodeEventHandler *Singleton();

    public:
      void emitMousePress(GNode *node, QGraphicsSceneMouseEvent *e);
      void emitMouseRelease(GNode *node, QGraphicsSceneMouseEvent *e);
      void emitMouseDoubleClick(GNode *node, QGraphicsSceneMouseEvent *e);

    signals:
      void mousePress(GNode *node, QGraphicsSceneMouseEvent *e);
      void mouseRelease(GNode *node, QGraphicsSceneMouseEvent *e);
      void mouseDoubleClick(GNode *node, QGraphicsSceneMouseEvent *e);

    private:
      static GNodeEventHandler *singleton_;
  };
}