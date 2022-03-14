#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

class QOpenGLShaderProgram;

namespace IcicleMorphotreeWidget
{
  // Tessellation Based on a function Node
  class TessFunctionNode : public GNode 
  {
  public:
    enum {
      SHADER_PROGRAM_POSITION_ATTR_LOC = 0,
      SHADER_PROGRAM_COLOR_ATTR_LOC = 1
    };

    TessFunctionNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode=nullptr,
      float minValue=0.7f, float maxValue=1.0f);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options,
      QWidget *widget) override;

    float maxValue() const { return maxValue_; }
    float &maxValue() { return maxValue_; }
    void setMaxValue(float val) { maxValue_ = val; }

    float minValue() const { return minValue_; }
    float &minValue() { return minValue_; }
    void setMinValue(float val) { minValue_ = val; }

  private:
    static void initShaders();

  private:
    float maxValue_;
    float minValue_;

    static QOpenGLShaderProgram *shaderProgram_;
  };
}