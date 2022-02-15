#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNode.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNodeFactory.hpp"

#include <QPainter>

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

void loadQtResources() { 
   Q_INIT_RESOURCE(IcicleMorphotreeWidgetResource); 
}

namespace IcicleMorphotreeWidget
{
  QOpenGLShaderProgram *OpenGLGNode::shaderProgram_ = nullptr;

  void OpenGLGNode::initShaders()
  {    
    if (!shaderProgram_ || !shaderProgram_->isLinked()) {
      loadQtResources();

      shaderProgram_ = new QOpenGLShaderProgram;      

      shaderProgram_ = new QOpenGLShaderProgram;
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex.glsl");
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/geometry.glsl");
      shaderProgram_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment.glsl");
      shaderProgram_->bindAttributeLocation("aPos", SHADER_PROGRAM_POSITION_ATTR_LOC);      
      shaderProgram_->link();

      shaderProgram_->bind();
    }
  }

  OpenGLGNode::OpenGLGNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode,
    float topProportion, float leftProportion, float bottomProportion, 
    float rightProportion, float centerProportion,
    float topLeftProportion, float topRightProportion,
    float bottomLeftProportion, float bottomRightProportion)
    : GNode{treeVis, mnode},
      topProportion_{topProportion}, 
      leftProportion_{leftProportion},
      bottomProportion_{bottomProportion},
      rightProportion_{rightProportion},
      centerProportion_{centerProportion},
      topLeftProportion_{topLeftProportion},
      topRightProportion_{topRightProportion},
      bottomLeftProportion_{bottomLeftProportion},
      bottomRightProportion_{bottomRightProportion}
  { }  

  void OpenGLGNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *options,
    QWidget *widget)
  {
    Q_UNUSED(widget);
    Q_UNUSED(options);
    
    QRectF r = boundingRect();

    QVector<QVector2D> pos = {
      QVector2D{r.topLeft()}, QVector2D{r.topRight()},
      QVector2D{r.bottomRight()}, QVector2D{r.bottomLeft()}};
      
    painter->beginNativePainting();

    QOpenGLFunctions *gl = QOpenGLContext::currentContext()->functions();

    initShaders();

    shaderProgram_->bind();
    
    QMatrix4x4 proj;
    gl->glGetFloatv(GL_PROJECTION_MATRIX, proj.data());

    QMatrix4x4 model;
    gl->glGetFloatv(GL_MODELVIEW_MATRIX, model.data());

    gl->glEnable(GL_BLEND);

    shaderProgram_->setUniformValue("transform", proj * model);

    shaderProgram_->setUniformValue("opacity", static_cast<float>(opacity()));
    shaderProgram_->setUniformValue("lp", leftProportion_);
    shaderProgram_->setUniformValue("rp", rightProportion_);
    shaderProgram_->setUniformValue("tp", topProportion_);
    shaderProgram_->setUniformValue("bp", bottomProportion_);

    shaderProgram_->setUniformValue("cp", centerProportion_);
    shaderProgram_->setUniformValue("tlp", topLeftProportion_);
    shaderProgram_->setUniformValue("trp", topRightProportion_);
    shaderProgram_->setUniformValue("blp", bottomLeftProportion_);
    shaderProgram_->setUniformValue("brp", bottomRightProportion_);

    shaderProgram_->setUniformValue("centerColor", backgroundColor_);

    shaderProgram_->enableAttributeArray(SHADER_PROGRAM_POSITION_ATTR_LOC);    
    shaderProgram_->setAttributeArray(SHADER_PROGRAM_POSITION_ATTR_LOC, GL_FLOAT, 
      pos.constData(), 2, 0);
    
    gl->glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, pos.size());

    painter->endNativePainting();

    // drawing borders
    if (isSelected_) {
      painter->setPen(QPen(selectionColor_, 3));                  
      painter->drawRect(boundingRect());
    }
  }
}