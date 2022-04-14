#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

namespace IcicleMorphotreeWidget
{
  class BezierFuncNodeFactory : public GNodeFactory
  {
  public:
    BezierFuncNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr, 
      float hleft = 0.7f, float hmiddle = 1.0f, float hright = 0.7f,
      float vtop = 0.7f, float vmiddle = 0.7f, float vbottom = 0.7f);

  float hleft() const { return hleft_; }
  float &hleft() { return hleft_; }
  void setHLeft(float val) { hleft_ = val; }

  float  hmiddle() const { return hmiddle_; }
  float &hmiddle()  { return hmiddle_; }
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

  GNodeStyle style() const override { return GNodeStyle::BilinearGradientColor; }

  GNode *create(MTreeNodePtr mnode = nullptr) override;

  virtual ~BezierFuncNodeFactory();

  private:
    float hleft_;
    float hmiddle_;
    float hright_;

    float vtop_;
    float vmiddle_;
    float vbottom_;
  };
}