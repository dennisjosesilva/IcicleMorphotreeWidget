#include "IcicleMorphotreeWidget/Graphics/Node/TessBLGradientNode.hpp"
#include "IcicleMorphotreeWidget/Resource/Loader.hpp"

#include <QPainter>

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

namespace IcicleMorphotreeWidget 
{
  QOpenGLShaderProgram *TessBLGradientNode::shaderProgram_ = nullptr;

  void TessBLGradientNode::initShaders()
  {
    if (!shaderProgram_ || !shaderProgram_->isLinked()) {
      loadQtResources();

      shaderProgram_ = new QOpenGLShaderProgram;
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::Vertex, 
        ":/shaders/bilinear_gradient/vertex.glsl");
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::TessellationControl,
        ":/shaders/bilinear_gradient/tess_control.glsl");
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation,
        ":/shaders/bilinear_gradient/tess_evaluation.glsl");
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::Fragment,
        ":/shaders/bilinear_gradient/fragment.glsl");
      shaderProgram_->link();
      shaderProgram_->bindAttributeLocation("position", SHADER_PROGRAM_POSITION_ATTR_LOC);
      shaderProgram_->bindAttributeLocation("color", SHADER_PROGRAM_COLOR_ATTR_LOC);      
      shaderProgram_->bind();      

      // Set tessellation subdivision levels
      shaderProgram_->setUniformValue("innerSubvisionLevel", 8);
      shaderProgram_->setUniformValue("outerSubdivisionLevel", 8);
    }
  }

  TessBLGradientNode::TessBLGradientNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode,
    float topLeftProportion, float topRightProportion,
    float bottomLeftProportion, float bottomRightProportion)
    : GNode{treeVis, mnode},
      topLeftProportion_{topLeftProportion}, 
      topRightProportion_{topRightProportion_},
      bottomLeftProportion_{bottomLeftProportion},
      bottomRightProportion_{bottomRightProportion_}
  {}

  void TessBLGradientNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *options,
    QWidget *widget)
  {
    Q_UNUSED(widget);
    Q_UNUSED(options);

    QRectF r = boundingRect();
    
    painter->beginNativePainting();
    
    QOpenGLFunctions *gl = QOpenGLContext::currentContext()->functions();
    QOpenGLExtraFunctions *egl = QOpenGLContext::currentContext()->extraFunctions();

    QVector3D bcolor{ static_cast<float>(backgroundColor_.redF()), 
      static_cast<float>(backgroundColor_.greenF()),
      static_cast<float>(backgroundColor_.blueF()) };

    QVector<QVector2D> pos = {
      QVector2D{r.topLeft()}, QVector2D{r.topRight()},
      QVector2D{r.bottomRight()}, QVector2D{r.bottomLeft()}
    };

    QVector<QVector3D> colors = {
      bcolor * topLeftProportion_, bcolor * topRightProportion_,
      bcolor * bottomRightProportion_, bcolor * bottomLeftProportion_ };

    initShaders();
    shaderProgram_->bind();
    
    QMatrix4x4 proj;
    gl->glGetFloatv(GL_PROJECTION_MATRIX, proj.data());

    QMatrix4x4 model;
    gl->glGetFloatv(GL_MODELVIEW_MATRIX, model.data());

    shaderProgram_->setUniformValue("transform", proj * model);
    shaderProgram_->setUniformValue("opacity", static_cast<float>(opacity()));
    
    shaderProgram_->enableAttributeArray(SHADER_PROGRAM_POSITION_ATTR_LOC);
    shaderProgram_->setAttributeArray(SHADER_PROGRAM_POSITION_ATTR_LOC, GL_FLOAT,
      pos.data(), 2, 0);

    shaderProgram_->enableAttributeArray(SHADER_PROGRAM_COLOR_ATTR_LOC);
    shaderProgram_->setAttributeArray(SHADER_PROGRAM_COLOR_ATTR_LOC, GL_FLOAT, 
      colors.data(), 3, 0);

    egl->glPatchParameteri(GL_PATCH_VERTICES, 4);    
    gl->glDrawArrays(GL_PATCHES, 0, pos.size());

    painter->endNativePainting();    

    if (isSelected_)  {
      painter->setPen(QPen(selectionColor_, 3));
      painter->drawRect(boundingRect());
    }    
  }
}