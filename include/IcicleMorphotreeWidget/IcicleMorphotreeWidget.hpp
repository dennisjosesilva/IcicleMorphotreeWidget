#pragma once 

#include <QGraphicsView>

#include <morphotree/core/alias.hpp>
#include <morphotree/core/box.hpp>
#include <morphotree/tree/mtree.hpp>

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"
#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"
#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar.hpp"
#include "IcicleMorphotreeWidget/Graphics/ColorBar.hpp"
#include "IcicleMorphotreeWidget/Filtering/TreeFiltering.hpp"

#include "IcicleMorphotreeWidget/MorphoTreeType.hpp"
#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar/GrayScaleProfile.hpp"

namespace IcicleMorphotreeWidget
{
  class GNode;

  class IcicleMorphotreeWidget : public QGraphicsView
  {
    Q_OBJECT
  public:
    using Box = morphotree::Box;
    using uint8 = morphotree::uint8;
    using uint32 = morphotree::uint32;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using TreeLayoutPtr = std::shared_ptr<TreeLayout>;
    using UI32Point = morphotree::UI32Point;
    using I32Point = morphotree::I32Point;    
    using GNodeFactoryPtr = typename TreeLayout::GNodeFactoryPtr;

    using ColorMapPtr = std::unique_ptr<ColorMap>;
    using NormAttributesPtr = std::unique_ptr<std::vector<float>>;

    IcicleMorphotreeWidget(
      const GrayScaleProfile &grayscalePorfile=GrayScaleProfile{Range{0, 255}, Range{0, 255}},
      QWidget *parent = nullptr, 
      TreeLayoutPtr treeLayout=std::make_shared<FixedHeightTreeLayout>());

    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void updateTreeRendering();

    MTree filter(std::shared_ptr<TreeFiltering> treeFiltering);
    void ifilter(std::shared_ptr<TreeFiltering> treeFiltering);    

    void loadImage(Box domain, const std::vector<uint8> &f, 
      MorphoTreeType mtreeType=MAX_TREE_8C);
    
    inline MorphoTreeType treeType() const { return mtreeType_; }
    void setTreeType(MorphoTreeType mtreeType);

    inline const MTree& mtree() const { return tree_; }

    const GrayScaleProfile& grayscaleProfile() const  {return grayscaleProfile_; }
    void setGrayScaleProfile(const GrayScaleProfile &val);

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
    inline void fitToWidget() { scaleView(1.0f / scaleFactor_); }

    const QVector<GNode *> &gnodes() const { return gnodes_; }
    QVector<GNode *>& gnodes() { return gnodes_; }

    GNode *gnode(const I32Point &p);
    GNode *gnode(const QPoint &p);
    GNode *gnode(int x, int y);

    GNode *gnode(const I32Point &p, const QVector<bool> &mask);
    GNode *gnode(const QPoint &p, const QVector<bool> &mask);
    GNode *gnode(int x, int y, const QVector<bool> &mask);

    void setGNodeFactory(GNodeFactoryPtr f);
    GNodeFactoryPtr gnodeFactory() { return treeLayout_->gnodeFactory(); }

    inline std::vector<uint8> recImage() const { return tree_.reconstructImage(); }
    inline Box domain() const { return domain_; }

    void addGrayScaleBar(unsigned int numberOfLevels=256, qreal breadth=5.0f);    
    void removeGrayScaleBar();
    GrayScaleBar* grayscaleBar() { return grayScaleBar_; }

    bool isDownSpace() const { return isDownSpace_; }

    TreeLayoutPtr treeLayout() { return treeLayout_; }
    void setTreeLayout(TreeLayoutPtr treeLayout);

    TreeLayoutOrientation orientation() const { return treeLayout_->orientation(); }
    void setOrientation(TreeLayoutOrientation val);

    // QRectF boundingRect() const override { return scene()->sceneRect(); }

    inline QColor& nodeSelectionColor() { return GNode::selectionColor(); }
    inline void setNodeSelectionColor(const QColor &val) { GNode::setSelectionColor(val); }

    // grey-level rendering
    void activateGrayscaleNodeRender();
    void deactivactedGrayscaleNodeRender();
    inline bool isGrayscaleNodeRenderActivated() const { return grayLevelRendering_; }


  signals:
    void treeAboutToBeRedrawn();
    void keyPress(QKeyEvent *e);
    void keyRelease(QKeyEvent *e);

  protected:    
    void renderGrayScaleBar();
    void paintNodesBasedOnNormAttribute();
    void resetNodesColor();

  protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    void resizeEvent(QResizeEvent *e) override;

  private:
    qreal scaleFactor_;
    TreeLayoutPtr treeLayout_;
    Box domain_;
    MTree tree_;
    float grayScalerBarBreadth_;
    GrayScaleBar *grayScaleBar_;

    QVector<GNode *> gnodes_;

    NormAttributesPtr attr_;
    ColorMapPtr colorMap_;

    bool isDownSpace_;
    
    MorphoTreeType mtreeType_;
    GrayScaleProfile grayscaleProfile_;

    bool grayLevelRendering_;
  };
}