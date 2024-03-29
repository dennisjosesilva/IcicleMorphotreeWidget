#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

namespace IcicleMorphotreeWidget
{
  class TessBLGradientNodeFactory : public GNodeFactory
  {
  public:
    TessBLGradientNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr,
      float topLeftProportion=1.0f, float topRightProportion=0.8f,
      float bottomLeftProportion=0.8f, float bottomRightProportion=0.8f);

    float topLeftProportion() const { return topLeftProportion_; }
    float &topLeftProportion() { return topLeftProportion_; }
    void setTopLeftProportion(float val) { topLeftProportion_ = val; }

    float topRightProportion() const { return topRightProportion_; }
    float &topRightProportion() { return topRightProportion_; }
    void setTopRightProportion(float val) { topRightProportion_ = val; }

    float bottomLeftProportion() const { return bottomLeftProportion_; }
    float &bottomLeftProportion() { return bottomLeftProportion_; }
    void setBottomLeftProportion(float val) { bottomLeftProportion_ = val; }

    float bottomRightProportion() const { return bottomRightProportion_;}
    float &bottomRightProportion() { return bottomRightProportion_; }
    void setBottomRightProportion(float val) { bottomRightProportion_ = val; }

    GNodeStyle style() const override { return GNodeStyle::BilinearGradientColor; }

    GNode *create(MTreeNodePtr mnode = nullptr) override;

    virtual ~TessBLGradientNodeFactory();

  private:
    float topLeftProportion_;
    float topRightProportion_;
    float bottomLeftProportion_;
    float bottomRightProportion_;
  };

  // ================= [ PRESETS ] ==================================================
  class TessBLPreset 
  {
  public:
    using TessBLGradientNodeFactoryPtr = std::shared_ptr<TessBLGradientNodeFactory>;
    virtual void setUpFactory(TessBLGradientNodeFactoryPtr factory) = 0;
  };

  class TessBLBottomRightLShapedPreset : public TessBLPreset
  {
  public:
    TessBLBottomRightLShapedPreset(float darkerLProportion = 0.85f);
    void setUpFactory(TessBLGradientNodeFactoryPtr factory);

    float darkerLProportion() const { return darkerLProportion_; }
    float &darkerLProportion() { return darkerLProportion_; }
    void setDarkerLProportion(float val) { darkerLProportion_ = val; }

  private:
    float darkerLProportion_;
  };

  class TessBLTopLeftLShapedPreset : public TessBLPreset
  {
  public:
    TessBLTopLeftLShapedPreset(float darkerLProportion = 0.85f);
    void setUpFactory(TessBLGradientNodeFactoryPtr factory);

    float darkerLProportion() const { return darkerLProportion_; }
    float &darkerLProportion() { return darkerLProportion_; }
    void setDarkerLProportion(float val) { darkerLProportion_ = val; }
    
  private:
    float darkerLProportion_;
  };
}