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

  GNode *GradientGNodeFactory::create(MTreeNodePtr node)
  {
    return new GradientGNode{treeVis_, node, 
      gradientProportion_};
  }
}