#include "IcicleMorphotreeWidget/Graphics/Node/BezierFuncNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/BezierFuncNode.hpp"

namespace IcicleMorphotreeWidget
{
  BezierFuncNodeFactory::BezierFuncNodeFactory(IcicleMorphotreeWidget *treeVis,
    float hleft, float hmiddle, float hright,
    float vtop, float vmiddle, float vbottom)
  : GNodeFactory{treeVis},
    hleft_{hleft}, hmiddle_{hmiddle}, hright_{hright},
    vtop_{vtop}, vmiddle_{vmiddle}, vbottom_{vbottom}
  {}

  GNode *BezierFuncNodeFactory::create(MTreeNodePtr mnode)
  {
    return new BezierFuncNode{treeVis_, mnode, 
      hleft_, hmiddle_, hright_,
      vtop_, vmiddle_, vbottom_};
  }

  BezierFuncNodeFactory::~BezierFuncNodeFactory()
  {}
}