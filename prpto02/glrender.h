#ifndef GLRENDER_H
#define GLRENDER_H


#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QOpenGLFunctions>
#include "camera_.h"

#include <opencv2\opencv.hpp>

namespace jun {
	class Tracker;
	class DisparityMaker;
}

class GlRender : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
public:
	explicit GlRender(QWidget* parent = nullptr);
	virtual ~GlRender();

	QSurfaceFormat format;

	void setInit(jun::Tracker *p_Tracker, jun::DisparityMaker *p_Disparity);
	void setColorVertexVisiable(bool visiable);
	void setViewBoxVisiable(bool visiable);

	void cleanUp();
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
	jun::Tracker		*m_Tracker;
	jun::DisparityMaker	*m_Disparity;
	
	float m_ImgSizeX, m_ImgSizeY;
	int m_ModelViewBox;
	float m_ScaleVal;

	cv::Mat m_ReprojectData, m_ReprojectColorData;

	jun::Camera m_Cam;
	
	///////////////////////////FUNCT//////////////////////////
	void drawScene();
	void drawTrackCam();

	///////////////////////////SLOTS//////////////////////////
	private slots :

};


#endif // !GLRENDER_H