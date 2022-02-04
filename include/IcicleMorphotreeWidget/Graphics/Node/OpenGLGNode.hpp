#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

class QOpenGLShaderProgram;

void loadQtResources();

namespace IcicleMorphotreeWidget
{
  class OpenGLGNode : public GNode
  {
  public:
    enum {
      SHADER_PROGRAM_POSITION_ATTR_LOC = 0,
      SHADER_PROGRAM_COLOR_ATTR_LOC = 1
    };

    OpenGLGNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, 
      QWidget *widget) override;

  private:
    static void initShaders();

  private:
    static QOpenGLShaderProgram *shaderProgram_;
  };
}