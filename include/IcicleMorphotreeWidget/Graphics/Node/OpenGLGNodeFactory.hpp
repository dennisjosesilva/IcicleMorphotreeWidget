#pragma once

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

class QOpenGLShaderProgram;

namespace IcicleMorphotreeWidget
{
  class OpenGLGNodeFactory : public GNodeFactory 
  {
  public:
    OpenGLGNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr);

    GNodeStyle style() const override { return GNodeStyle::GradientColor; }

    GNode *create(MTreeNodePtr mnode = nullptr) override;

    virtual ~OpenGLGNodeFactory();
  };
}