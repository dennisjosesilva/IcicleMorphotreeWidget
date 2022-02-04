#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNode.hpp"

#include <QOpenGLShaderProgram>

namespace IcicleMorphotreeWidget
{
  OpenGLGNodeFactory::OpenGLGNodeFactory(IcicleMorphotreeWidget *treeVis,
    float topProportion, float leftProportion, 
    float bottomProportion, float rightProportion)
    : GNodeFactory{treeVis},
      topProportion_{topProportion},
      leftProportion_{leftProportion},
      bottomProportion_{bottomProportion},
      rightProportion_{rightProportion}
  {}

  GNode *OpenGLGNodeFactory::create(MTreeNodePtr mnode)
  {
    return new OpenGLGNode{treeVis_, mnode, topProportion_, 
      leftProportion_, bottomProportion_, rightProportion_};
  }

  OpenGLGNodeFactory::~OpenGLGNodeFactory()
  {}
}