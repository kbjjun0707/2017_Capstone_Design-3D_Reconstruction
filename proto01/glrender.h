#pragma once

#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

namespace iMiner {
	class Tracker;
	class DisparityMaker;
}

class GlRender : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
public:
	explicit GlRender(QWidget* parent = nullptr);
	virtual ~GlRender();

	QSurfaceFormat format;
	float m_FirstFar;
	float m_CamX, m_CamY, m_CamFar, m_CamAxisX, m_CamAxisY;

	void setInit(iMiner::Tracker *p_Tracker, iMiner::DisparityMaker *p_Disparity);
	void setCamView(bool visiable);
	void setColorVertexVisiable(bool Enable);

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	virtual void timerEvent(QTimerEvent *e);

	virtual void wheelEvent(QWheelEvent *e);

	int xAtPress, yAtPress, xPre, yPre;
	float dx, dy;
	bool mouseClicked = 0, m_CameraModel, m_ColorVertexVisiable;;

	virtual void mousePressEvent(QMouseEvent *e);

	virtual void mouseMoveEvent(QMouseEvent *e);

	virtual void mouseReleaseEvent(QMouseEvent *e);

private:
	iMiner::Tracker *m_Tracker;
	iMiner::DisparityMaker *m_Disparity;

	QMatrix4x4 *m_GLCam;

	int m_CamModel;
	
	///////////////////////////FUNCT//////////////////////////
	void drawScene();

	void drawTrackCam();

	///////////////////////////SLOTS//////////////////////////
	private slots :
	void cleanUp();

};