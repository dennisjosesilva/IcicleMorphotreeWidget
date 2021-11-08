#pragma once 

#include <QGraphicsView>

#include <morphotree/core/alias.hpp>
#include <morphotree/core/box.hpp>
#include <morphotree/tree/mtree.hpp>

#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"
#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar.hpp"

#include "IcicleMorphotreeWidget/Graphics/ColorBar.hpp"

#include "IcicleMorphotreeWidget/Filtering/TreeFiltering.hpp"

namespace IcicleMorphotreeWidget
{
  class GNode;

  class IcicleMorphotreeWidget : public QGraphicsView
  {
  public:
    using Box = morphotree::Box;
    using uint8 = morphotree::uint8;
    using uint32 = morphotree::uint32;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using TreeLayoutPtr = std::unique_ptr<TreeLayout>;
    using UI32Point = morphotree::UI32Point;
    using I32Point = morphotree::I32Point;    

    using ColorMapPtr = std::unique_ptr<ColorMap>;
    using NormAttributesPtr = std::unique_ptr<std::vector<float>>;

    IcicleMorphotreeWidget(QWidget *parent = nullptr, 
      TreeLayoutPtr treeLayout=std::make_unique<FixedHeightTreeLayout>());

    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void updateTreeRendering();

    MTree filter(std::shared_ptr<TreeFiltering> treeFiltering);
    void ifilter(std::shared_ptr<TreeFiltering> treeFiltering);    

    void loadImage(Box domain, const std::vector<uint8> &f);

    inline const MTree& mtree() const { return tree_; }

    void loadAttributes(NormAttributesPtr attr);
    void clearAttributes();

    bool hasAttributes() const { return attr_ != nullptr; }
    float normAttributeValue(uint32 idx) const { return attr_->at(idx); }

    inline void setColorMap(ColorMapPtr colorMap) { colorMap_ = std::move(colorMap); }
    inline VColorBar* createVColorBar(QWidget *parent=nullptr) { return colorMap_->createVColorBar(parent); }
    inline HColorBar* createHColorBar(QWidget *parent=nullptr) { return colorMap_->createHColorBar(parent); }
    void addGNodeToScene(GNode *node);

    void scaleView(qreal scaleFactor);
    void visZoomIn();
    void visZoomOut();

    const QVector<GNode *> &gnodes() const { return gnodes_; }
    QVector<GNode *>& gnodes() { return gnodes_; }

    GNode *gnode(const I32Point &p);
    GNode *gnode(const QPoint &p);
    GNode *gnode(int x, int y);

    inline std::vector<uint8> recImage() const { return tree_.reconstructImage(); }
    inline Box domain() const { return domain_; }

    void addGrayScaleBar(unsigned int numberOfLevels=256, qreal unitWidth=20, 
      qreal unitHeight = 5.0f);
    void removeGrayScaleBar();

  protected:    
    void paintNodesBasedOnNormAttribute();
    void resetNodesColor();

  protected:
    void keyPressEvent(QKeyEvent *e) override;

  private:
    TreeLayoutPtr treeLayout_;
    Box domain_;
    MTree tree_;
    GrayScaleBar *grayScaleBar_;

    QVector<GNode *> gnodes_;

    NormAttributesPtr attr_;
    ColorMapPtr colorMap_;
  };
}