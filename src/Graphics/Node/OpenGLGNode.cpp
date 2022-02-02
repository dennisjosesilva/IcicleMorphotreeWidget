#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNode.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNodeFactory.hpp"

#include <QPainter>

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

namespace IcicleMorphotreeWidget
{
  QOpenGLShaderProgram *OpenGLGNode::shaderProgram_ = nullptr;

  void OpenGLGNode::initShaders()
  {
    if (!shaderProgram_) {
      shaderProgram_ = new QOpenGLShaderProgram;

      const char *vertexShaderCode = 
        "#version 330 core\n"
        "layout(location = 0) in vec2 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "out vec3 fcolor;\n"
        "\n"
        "uniform mat4 transform;\n"      
        "void main()\n"
        "{\n"
        "   fcolor = aColor;\n"
        "   gl_Position = transform * vec4(aPos, 0.0, 1.0);\n"
        "}\0";

      const char *fragmentShaderCode = 
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "in vec3 fcolor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   fragColor = vec4(fcolor, 1.0);\n"
        "}\0";

      shaderProgram_ = new QOpenGLShaderProgram;
      shaderProgram_->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderCode);
      shaderProgram_->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderCode);
      shaderProgram_->bindAttributeLocation("aPos", SHADER_PROGRAM_POSITION_ATTR_LOC);
      shaderProgram_->bindAttributeLocation("aColor", SHADER_PROGRAM_COLOR_ATTR_LOC);
      shaderProgram_->link();

      shaderProgram_->bind();
    }
  }

  OpenGLGNode::OpenGLGNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode)
    : GNode{treeVis, mnode}
  {}  

  void OpenGLGNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *options,
    QWidget *widget)
  {
    Q_UNUSED(widget);
    Q_UNUSED(options);
    
    QRectF r = boundingRect();

    QVector<QVector2D> pos = {
      QVector2D{r.topLeft()}, QVector2D{r.topRight()}, 
      QVector2D{r.bottomRight()}, 
      QVector2D{r.topLeft()}, QVector2D{r.bottomLeft()},
      QVector2D{r.bottomRight()}};

    QVector<QVector3D> color = {
      QVector3D{1.0f, 1.0f, 0.0f}, QVector3D{1.0f, 1.0f, 0.0f}, 
      QVector3D{1.0f, 1.0f, 0.0f}, 
      QVector3D{1.0f, 1.0f, 0.0f}, QVector3D{1.0f, 1.0f, 0.0f},
      QVector3D{1.0f, 1.0f, 0.0f}};    

    painter->beginNativePainting();

    QOpenGLFunctions *gl = QOpenGLContext::currentContext()->functions();

    initShaders();

    shaderProgram_->bind();
    
    QMatrix4x4 proj;
    gl->glGetFloatv(GL_PROJECTION_MATRIX, proj.data());

    QMatrix4x4 model;
    gl->glGetFloatv(GL_MODELVIEW_MATRIX, model.data());

    shaderProgram_->setUniformValue("transform", proj * model);

    shaderProgram_->enableAttributeArray(SHADER_PROGRAM_POSITION_ATTR_LOC);
    shaderProgram_->enableAttributeArray(SHADER_PROGRAM_COLOR_ATTR_LOC);
    shaderProgram_->setAttributeArray(SHADER_PROGRAM_POSITION_ATTR_LOC, GL_FLOAT, 
      pos.constData(), 2, 0);
    shaderProgram_->setAttributeArray(SHADER_PROGRAM_COLOR_ATTR_LOC, GL_FLOAT, 
      color.constData(), 3, 0);

    gl->glDrawArrays(GL_TRIANGLES, 0, pos.size());

    painter->endNativePainting();


    // drawing borders
    painter->setPen(Qt::black);
    painter->drawRect(r);
  }
}