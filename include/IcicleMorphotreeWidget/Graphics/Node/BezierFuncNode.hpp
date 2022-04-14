#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

class QOpenGLShaderProgram;

namespace IcicleMorphotreeWidget
{
  // Tessellation Based on a bezier function for luminance
  class BezierFuncNode : public GNode 
  {
  public:
    enum {
      SHADER_PROGRAM_POSITION_ATTR_LOC = 0
    };

    BezierFuncNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode = nullptr,
      float hleft = 0.7f, float hmiddle=1.0f, float hright=0.7f,
      float vtop = 0.7f, float vmiddle=1.0f, float vbottom=0.7f);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, 
      QWidget *widget);

    float hleft() const { return hleft_; }
    float &hleft() { return hleft_; }
    void setHLeft(float val) { hleft_ = val; }
    
    float hmiddle() const { return hmiddle_; }
    float &hmiddle() { return hmiddle_; }
    void setHMiddle(float val) { hmiddle_ = val; }

    float hright() const { return hright_; }
    float &hright() { return hright_; }
    void setHRight(float val) { hright_ = val; }
    
    float vtop() const { return vtop_; }
    float &vtop() { return vtop_; }
    void setVTop(float val) { vtop_ = val; }

    float vmiddle() const { return vmiddle_; }
    float &vmiddle() { return vmiddle_; }
    void setVMiddle(float val) { vmiddle_ = val; }

    float vbottom() const { return vbottom_; }
    float &vbottom() { return vbottom_; }
    void setVBottom(float val) { vbottom_ = val; }

  private:
    static void initShaders();

  private:
    float hleft_;
    float hmiddle_;
    float hright_;

    float vtop_;
    float vmiddle_;
    float vbottom_;

    static QOpenGLShaderProgram *shaderProgram_;
  };
}