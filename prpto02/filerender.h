#ifndef FILERENDER_H
#define FILERENDER_H

#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QOpenGLFunctions>

#include "camera_.h"


class FileRender : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
public:
	explicit FileRender(QWidget* parent = nullptr);
	virtual ~FileRender();

	QSurfaceFormat format;
	
	void setColorVertexVisiable(bool visiable);
	void setViewBoxVisiable(bool visiable);
	void setZScale(float scale, float min, float max);
	void render(const char *fileName);
protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	virtual void timerEvent(QTimerEvent *e);

	// mouse
	int xAtPress, yAtPress, xPre, yPre;
	float dx, dy;
	bool mouseClicked = 0,
		m_ColorVertexVisiable, m_ViewBoxVisable;

	virtual void wheelEvent(QWheelEvent *e);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);

private:
	int		m_DataSizeX, m_DataSizeY;
	int		m_ColorModel, m_Model;
	int		m_ModelViewBox;
	float	m_Scale, m_Min, m_Max;

	jun::Camera m_Cam;
	///////////////////////////FUNCT//////////////////////////

	///////////////////////////SLOTS//////////////////////////
private slots :

};



#endif // !FILERENDER_H

