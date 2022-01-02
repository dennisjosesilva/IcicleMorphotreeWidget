#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"
#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"

namespace IcicleMorphotreeWidget
{
  
  // ================ GNODE FACTORY ============================
  GNodeFactory::GNodeFactory(IcicleMorphotreeWidget *treeVis)
    :treeVis_{treeVis}
  {}

  // =========== FIXED COLOR GNODE FACTORY ======================
  FixedColorGNodeFactory::FixedColorGNodeFactory(
    IcicleMorphotreeWidget *treeVis)
    :GNodeFactory{treeVis}
  {}

  GNode *FixedColorGNodeFactory::create(MTreeNodePtr node)
  {
    return new FixedColorGNode{treeVis_, node};
  }

  // ========== GRADIENT GNODE FACTORY ===========================
  GradientGNodeFactory::GradientGNodeFactory(
    IcicleMorphotreeWidget *treeVis, float gradientProportion)
    :GNodeFactory{treeVis}, 
     gradientProportion_{gradientProportion}
  {}


  // ======== HORINZONTAL GNODE FACTORY ===========================
  HGradientGNodeFactory::HGradientGNodeFactory(
    IcicleMorphotreeWidget *treeVis, float gradientProportion)
  : GradientGNodeFactory{treeVis, gradientProportion}
  {}
  
  GNode *HGradientGNodeFactory::create(MTreeNodePtr node)
  {
    return new HGradientGNode{treeVis_, node, 
      gradientProportion_};
  }

  // ======= VERTICAL GNODE FACTORY =================================
  VGradientGNodeFactory::VGradientGNodeFactory(
    IcicleMorphotreeWidget *treeVis, float gradientProportion)
  : GradientGNodeFactory{treeVis, gradientProportion}
  {}

  GNode *VGradientGNodeFactory::create(MTreeNodePtr node)
  {
    return new VGradientGNode{treeVis_, node, 
      gradientProportion_};
  }
}