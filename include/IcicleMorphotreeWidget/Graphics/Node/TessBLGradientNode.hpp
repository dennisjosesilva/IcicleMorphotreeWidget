#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

class QOpenGLShaderProgram;

namespace IcicleMorphotreeWidget
{
  // Tesselation BiLinear Gradient Node 
  class TessBLGradientNode : public GNode 
  {
  public:
    enum {
      SHADER_PROGRAM_POSITION_ATTR_LOC = 0,
      SHADER_PROGRAM_COLOR_ATTR_LOC = 1
    };

    TessBLGradientNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode=nullptr,
      float topLeftProportion=0.9, float topRightProportion=0.9,
      float bottomLeftProportion=0.9, float bottomRightProportion=0.9);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options,
      QWidget *widget) override;

    float topLeftProportion() const { return topLeftProportion_; }
    float &topLeftProportion() { return topLeftProportion_; }
    void setTopLeftProportion(float val) { topLeftProportion_ = val; }

    float topRightProportion() const { return topRightProportion_; }
    float &topRightProportion() { return topRightProportion_; }
    void setTopRightProportion(float val) { topRightProportion_ = val; }

    float bottomLeftProportion() const { return bottomLeftProportion_; }
    float &bottomLeftProportion() { return bottomLeftProportion_; }
    void setBottomLeftProportion(float val) { bottomLeftProportion_ = val; }

    float bottomRightProportion() const { return bottomRightProportion_; }
    float &bottomRightProportion() { return bottomRightProportion_; }
    void setBottomRightProportion(float val) { bottomRightProportion_ = val; }

  private:
    static void initShaders();

  private:
    float topLeftProportion_;
    float topRightProportion_;
    float bottomLeftProportion_;
    float bottomRightProportion_;

    static QOpenGLShaderProgram *shaderProgram_;
  };
}