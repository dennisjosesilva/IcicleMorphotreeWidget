#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNode.hpp"

#include <QOpenGLShaderProgram>

namespace IcicleMorphotreeWidget
{
  OpenGLGNodeFactory::OpenGLGNodeFactory(IcicleMorphotreeWidget *treeVis)
    : GNodeFactory{treeVis}
  {}

  GNode *OpenGLGNodeFactory::create(MTreeNodePtr mnode)
  {
    return new OpenGLGNode{treeVis_, mnode};
  }

  OpenGLGNodeFactory::~OpenGLGNodeFactory()
  {}
}