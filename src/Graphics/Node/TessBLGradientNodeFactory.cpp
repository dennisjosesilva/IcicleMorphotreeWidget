#include "IcicleMorphotreeWidget/Graphics/Node/TessBLGradientNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/TessBLGradientNode.hpp"

namespace IcicleMorphotreeWidget
{
  TessBLGradientNodeFactory::TessBLGradientNodeFactory(IcicleMorphotreeWidget *treeVis,
    float topLeftProportion, float topRightProportion,
    float bottomLeftProportion, float bottomRightProportion)
    : GNodeFactory{treeVis},
      topLeftProportion_{topLeftProportion},
      topRightProportion_{topRightProportion},
      bottomLeftProportion_{bottomLeftProportion},
      bottomRightProportion_{bottomRightProportion}
  {}

  GNode * TessBLGradientNodeFactory::create(MTreeNodePtr mnode)
  {
    return new TessBLGradientNode{treeVis_, mnode, 
      topLeftProportion_, topRightProportion_,
      bottomLeftProportion_, bottomRightProportion_};
  }

  TessBLGradientNodeFactory::~TessBLGradientNodeFactory() 
  {}  
}