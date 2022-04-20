#include "IcicleMorphotreeWidget/Graphics/Node/BezierFuncNode.hpp"
#include "IcicleMorphotreeWidget/Resource/Loader.hpp"

#include <QPainter>

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

namespace IcicleMorphotreeWidget 
{
  QOpenGLShaderProgram *BezierFuncNode::shaderProgram_ = nullptr;

  void BezierFuncNode::initShaders()
  {
    if (!shaderProgram_ || !shaderProgram_->isLinked()) {
      loadQtResources();

      shaderProgram_ = new QOpenGLShaderProgram;
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::Vertex, 
        ":/shaders/tess_function_bezier/vertex.glsl");
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::TessellationControl,
        ":/shaders/tess_function_bezier/tess_control.glsl");
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation,
        ":/shaders/tess_function_bezier/tess_evaluation.glsl");
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::Fragment,
        ":/shaders/tess_function_bezier/fragment.glsl");
      shaderProgram_->link();
      shaderProgram_->bind();

      // set tessellation subdivision levels
      shaderProgram_->setUniformValue("innerSubdivisionLevel", 8);
      shaderProgram_->setUniformValue("outerSubdivisionLevel", 8);
    }
  }

  BezierFuncNode::BezierFuncNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode, 
    float hleft, float hmiddle, float hright,
    float vtop, float vmiddle, float vbottom)
  : GNode{treeVis, mnode}, hleft_{hleft}, hmiddle_{hmiddle}, hright_{hright},
    vtop_{vtop}, vmiddle_{vmiddle}, vbottom_{vbottom}
  {}

  void BezierFuncNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *options,
    QWidget *widget)
  {
    Q_UNUSED(widget);
    Q_UNUSED(options);

    QRectF r = boundingRect();

    painter->beginNativePainting();

    QOpenGLFunctions *gl = QOpenGLContext::currentContext()->functions();
    QOpenGLExtraFunctions *egl = QOpenGLContext::currentContext()->extraFunctions();

    QVector<QVector2D> pos = {
      QVector2D{r.topLeft()}, QVector2D{r.topRight()},
      QVector2D{r.bottomRight()}, QVector2D{r.bottomLeft()}};
    
    QVector3D bcolor{ static_cast<float>(backgroundColor_.redF()), 
      static_cast<float>(backgroundColor_.greenF()),
      static_cast<float>(backgroundColor_.blueF()) };

    initShaders();
    shaderProgram_->bind();

    QMatrix4x4 proj;
    gl->glGetFloatv(GL_PROJECTION_MATRIX, proj.data());

    QMatrix4x4 model;
    gl->glGetFloatv(GL_MODELVIEW_MATRIX, model.data());

    shaderProgram_->setUniformValue("controlPoints.hl", hleft_);
    shaderProgram_->setUniformValue("controlPoints.hm", hmiddle_);
    shaderProgram_->setUniformValue("controlPoints.hr", hright_);

    shaderProgram_->setUniformValue("controlPoints.vt", vtop_);
    shaderProgram_->setUniformValue("controlPoints.vm", vmiddle_);
    shaderProgram_->setUniformValue("controlPoints.vb", vbottom_);

    shaderProgram_->setUniformValue("transform", proj * model);
    shaderProgram_->setUniformValue("bcolor", bcolor);
    shaderProgram_->setUniformValue("opacity", static_cast<float>(opacity()));

    shaderProgram_->enableAttributeArray(SHADER_PROGRAM_POSITION_ATTR_LOC);
    shaderProgram_->setAttributeArray(SHADER_PROGRAM_POSITION_ATTR_LOC, GL_FLOAT, pos.data(), 
      2, 0);

    egl->glPatchParameteri(GL_PATCH_VERTICES, 4);
    gl->glDrawArrays(GL_PATCHES, 0, pos.size());

    painter->endNativePainting();

    if (isSelected_) {
      painter->setPen(QPen(selectionColor_, 3));
      painter->drawRect(boundingRect());
    }
  }
}