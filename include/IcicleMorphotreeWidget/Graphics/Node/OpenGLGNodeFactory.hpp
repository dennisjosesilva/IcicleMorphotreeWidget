#pragma once

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

class QOpenGLShaderProgram;

namespace IcicleMorphotreeWidget
{
  class OpenGLGNodeFactory : public GNodeFactory 
  {
  public:
    OpenGLGNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr, 
      float topProportion=0.5f, float leftProportion = 0.4f, 
      float bottomProportion=0.5f, float rightPorportion=0.4f);

    float topProportion() const { return topProportion_; }
    float &topProportion() { return topProportion_; }
    void setTopProportion(float val) { topProportion_ = val; }

    float leftProportion() const { return leftProportion_; }
    float &leftProportion() { return leftProportion_; }
    void setLeftProportion(float val) { leftProportion_ = val; }

    float bottomProportion() const { return bottomProportion_; }
    float &bottomProportion() { return bottomProportion_; }
    void setBottomProportion(float val) { bottomProportion_ = val; }

    float rightProportion() const { return rightProportion_; }
    float &rightProportion() { return rightProportion_; }
    void setRightProportion(float val) { rightProportion_ = val; }

    float centerProportion() const { return centerProportion_; }
    float &centerProportion() { return centerProportion_; }
    void setCenterProportion(float val) { centerProportion_ = val; }

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

    GNodeStyle style() const override { return GNodeStyle::BilinearGradientColor; }

    GNode *create(MTreeNodePtr mnode = nullptr) override;

    virtual ~OpenGLGNodeFactory();

  private:
    float topProportion_;
    float leftProportion_;
    float bottomProportion_;
    float rightProportion_;

    float centerProportion_;
    float topLeftProportion_;
    float topRightProportion_;
    float bottomLeftProportion_;
    float bottomRightProportion_;
  };


  class Preset
  {
  public: 
    using GNodeFactoryPtr = std::shared_ptr<OpenGLGNodeFactory>;
    virtual void setUpFactory(GNodeFactoryPtr factory) = 0;
  };

  class DefaultPreset : public Preset 
  {
  public:
    DefaultPreset(float topProportion=0.6f, float leftProportion=0.3f,
      float rightProportion=0.3f, float bottomProportion=0.6f);
    void setUpFactory(GNodeFactoryPtr factory) override;

    float topProportion() const { return topProportion_; }
    float &topProportion() { return topProportion_; }
    void setTopProportion(float val) { topProportion_ = val; }

    float leftProportion() const { return leftProportion_; }
    float &leftProportion() { return leftProportion_; }
    void setLeftProporition(float val) { leftProportion_ = val; }

    float rightProportion() const { return rightProportion_; }
    float &rightProportion() { return rightProportion_; }
    void setRightProportion(float val) { rightProportion_ = val; }

    float bottomProportion() const { return bottomProportion_; }
    float &bottomProportion() { return bottomProportion_; }
    void setBottomProportion(float val) { bottomProportion_ = val; }

  private:
    float topProportion_;
    float leftProportion_;
    float rightProportion_;
    float bottomProportion_;
  };

  class FlatPreset : public Preset 
  {
  public:
    FlatPreset();
    void setUpFactory(GNodeFactoryPtr factory) override;
  };

  class VerticalPreset : public Preset
  {
  public:
    VerticalPreset(float topProportion = 0.6f, float bottomProportion = 0.3f);
    void setUpFactory(GNodeFactoryPtr factory) override;

    float topProportion() const { return topProportion_; }
    float &topProportion() { return topProportion_; }
    void setTopProportion(float val) { topProportion_ = val; }

    float bottomProportion() const { return bottomProportion_; }
    float &bottomProportion() { return bottomProportion_; }
    void setBottomProportion(float val) { bottomProportion_ = val; }

  private:
    float topProportion_;
    float bottomProportion_;
  };

  class HorinzontalPreset : public Preset 
  {
  public:
    HorinzontalPreset(float leftProportion = 0.6f, float rightProportion = 0.3f);
    void setUpFactory(GNodeFactoryPtr factory) override;

    float leftProportion() const { return leftProportion_; }
    float &leftProportion() { return leftProportion_; }
    void setLeftProportion(float val) { leftProportion_ = val; }

    float rightProportion() const { return rightProportion_; }
    float &rightProportion() { return rightProportion_; }
    void setRightProportion(float val) { rightProportion_ = val; }

  private:
    float leftProportion_;
    float rightProportion_;
  };  

  class SymmetricTentLikeCushion : public Preset 
  {
  public:
    SymmetricTentLikeCushion(float cornerProportion = 0.3f, float sideProportion = 0.6f);
    virtual void setUpFactory(GNodeFactoryPtr factory) override;

    float cornerProportion() const { return cornerProportion_; }
    float &cornerProportion() { return cornerProportion_; }
    void setCornerProportion(float val) { cornerProportion_ = val; }

    float sideProportion() const { return sideProportion_; }
    float &sideProportion() { return sideProportion_; }
    void setSideProportion(float val) { sideProportion_ = val; }

  protected:
    float cornerProportion_;
    float sideProportion_;
  };

  class AsymetricTentLikeCushion : public SymmetricTentLikeCushion
  {
  public:
    AsymetricTentLikeCushion(float cornerProportion = 0.2f, float sideProportion = 0.7f,
      float increaseProportion = 1.1f);

    void setUpFactory(GNodeFactoryPtr factory) override;

    float increaseProportion() const { return increaseProportion_; }
    float &increaseProportion() { return increaseProportion_; }
    void setIncreaseProportion(float val) { increaseProportion_ = val; }

  private:
    float increaseProportion_;
  };
}