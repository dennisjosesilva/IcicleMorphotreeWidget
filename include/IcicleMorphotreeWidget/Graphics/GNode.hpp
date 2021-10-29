#pragma once 

#include <QGraphicsItem>
#include <QList>
#include <morphotree/tree/mtree.hpp>
#include <QColor>

namespace IcicleMorphotreeWidget
{
  class IcicleMorphotreeWidget;

  class GNode : public QGraphicsItem
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree =  morphotree::MorphologicalTree<uint8>;
    using MTreeNodePtr = typename MTree::NodePtr;
    using uint32 = morphotree::uint32;

    GNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode = nullptr);

    inline void setBackgroundColor(const QColor color) { backgroundColor_ = color; }
    const QColor& backgroundColor() const { return backgroundColor_; }
    QColor& backgroundColor() { return backgroundColor_; }

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget) override;
    
    inline bool isSelected() const { return isSelected_; }
    inline bool& isSelected() { return isSelected_; }
    inline void setSelected(bool isSelected) { isSelected_ = isSelected; }
    inline void select() { isSelected_ = true; }
    inline void unselect() { isSelected_ = false; }

    inline qreal width() const { return width_; }
    inline qreal& width() { return width_; }
    inline void setWidth(qreal w) { width_ = w; }

    inline qreal height() const { return height_; }
    inline qreal& height() { return height_; }
    inline void setHeight(qreal h) { height_ = h; }

    inline MTreeNodePtr mnode() const { return mnode_; }    

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e) override;

  private:
    IcicleMorphotreeWidget *treeVis_;
    MTreeNodePtr mnode_;
    QColor backgroundColor_;

    qreal width_;
    qreal height_;

    bool isSelected_;    
  };
}