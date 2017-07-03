#include "glrender.h"
#include "qmain.h"
#include <opencv2\opencv.hpp>

#include "optical_.h"
#include "disparity.h"

#include <gl/glu.h>

#include <qdebug.h>

float CameraModelVertices[] = {
	-0.5f, -0.5f, -0.5f, // triangle 1 : begin
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f, // triangle 1 : end
	0.5f,  0.5f, -0.5f, // triangle 2 : begin
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f, // triangle 2 : end
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	0.5f, -0.5f,  0.5f
};

GlRender::GlRender(QWidget* parent) : QOpenGLWidget(parent) {
	m_Disparity = nullptr; m_Tracker = nullptr;

	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	//format.setVersion(3, 2);
	format.setProfile(QSurfaceFormat::CoreProfile);
	this->setFormat(format);

	startTimer(40);

	m_CamX = m_CamY = m_CamAxisX = m_CamAxisY = 0;
	
	m_GLCam = new QMatrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	m_GLCam->lookAt(QVector3D(0, 15, 428), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
}

GlRender::~GlRender() {

	delete m_GLCam;
}

void GlRender::setInit(iMiner::Tracker * p_Tracker, iMiner::DisparityMaker * p_Disparity) {
	m_Tracker = p_Tracker;
	m_Disparity = p_Disparity;
}

void GlRender::setCamView(bool visiable) {
	m_CameraModel = visiable;
}

void GlRender::setColorVertexVisiable(bool Enable) {
	m_ColorVertexVisiable = Enable;
	qDebug() << m_ColorVertexVisiable << endl;
}

void GlRender::initializeGL() {
	initializeOpenGLFunctions();
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	m_CamModel = glGenLists(1);
	glNewList(m_CamModel, GL_COMPILE); {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, CameraModelVertices);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(CameraModelVertices) / 12);
		glDisableClientState(GL_VERTEX_ARRAY);
	}glEndList();

	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GlRender::cleanUp);
}

void GlRender::resizeGL(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	gluPerspective(45, (float)w / h, 0.1, 10000);

}

void GlRender::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMultMatrixf(m_GLCam->data());

	glPushMatrix(); {
		glTranslatef(0, 0, 128);
		drawScene();

		drawTrackCam();

		glColor3f(1.f, 1.f, 1.f);
		glCallList(m_CamModel);

	}glPopMatrix();
}

void GlRender::timerEvent(QTimerEvent * e) {
	
	update();
}

void GlRender::wheelEvent(QWheelEvent * e) {
	int numDegrees = e->delta() / 8;
	int numSteps = numDegrees / 15;

	if (e->orientation() == Qt::Horizontal) {
		m_CamFar += numSteps;
	} else {
		m_CamFar -= numSteps;
	}
	e->accept();
}

void GlRender::mousePressEvent(QMouseEvent * e) {
	mouseClicked = true;

	xAtPress = e->x();
	yAtPress = e->y();
	xPre = xAtPress;
	yPre = yAtPress;
	dx = 0; dy = 0;
}

void GlRender::mouseMoveEvent(QMouseEvent * e) {
	if (mouseClicked) {

		// example code
		dx = (e->x() - xPre);
		dy = (e->y() - yPre);

		xPre += dx;
		yPre += dy;

		m_GLCam->rotate(dx, 0, 1, 0);
	}
}

void GlRender::mouseReleaseEvent(QMouseEvent * e) {
	int xAtRelease = e->x();
	int yAtRelease = e->y();

	mouseClicked = false;
}

void GlRender::drawScene() {
	if (m_Disparity->getReprojectMat().size() != cv::Size(0,0)
		&& m_Disparity->getReprojectColor().size() != cv::Size(0, 0)) {
		cv::Mat xyz = m_Disparity->getReprojectMat();
		cv::Mat color = m_Disparity->getReprojectColor();

		cv::resize(xyz, xyz, cv::Size(), 0.5, 0.5);
		cv::resize(color, color, cv::Size(), 0.5, 0.5);
		int width = xyz.cols, height = xyz.rows;

		glPushMatrix(); {
			glTranslatef(-width / 2.0, -height / 2.0, -100);
			glColor3f(1.f, 0.f, 0.f);
			glBegin(GL_LINES); {
				glVertex3f(    0,      0, -255);
				glVertex3f(width,      0, -255);
				glVertex3f(width,      0, -255);
				glVertex3f(width, height, -255);
				glVertex3f(width, height, -255);
				glVertex3f(    0, height, -255);
				glVertex3f(    0, height, -255);
				glVertex3f(    0,      0, -255);


				glVertex3f(    0,      0,    0);
				glVertex3f(width,      0,    0);
				glVertex3f(width,      0,    0);
				glVertex3f(width, height,    0);
				glVertex3f(width, height,    0);
				glVertex3f(    0, height,    0);
				glVertex3f(    0, height,    0);
				glVertex3f(    0,      0,    0);


				glVertex3f(    0,      0, -255);
				glVertex3f(    0,      0,    0);
				glVertex3f(width,      0, -255);
				glVertex3f(width,      0,    0);
				glVertex3f(width, height, -255);
				glVertex3f(width, height,    0);
				glVertex3f(    0, height, -255);
				glVertex3f(    0, height,    0);
			}glEnd();
			
			glPointSize(2);
			glBegin(GL_POINTS); {
				for (int r = 0; r < height; r++) {
					for (int c = 0; c < width; c++) {
						cv::Vec3f pt =   xyz.at<cv::Vec3f>(r, c);
						if (pt[2] * 255 == 0) continue;
						if (m_ColorVertexVisiable) {
							cv::Vec3b cr = color.at<cv::Vec3b>(r, c);
							glColor3ub(cr[2], cr[1], cr[0]);
						} else {
							glColor3ub(0, 200, 0);
						}
						glVertex3f(pt[0] * width, height - (pt[1] * height), (pt[2] * 255) - 255);
					}
				}				
			}glEnd();
		}glPopMatrix();
		
	}
}

void GlRender::drawTrackCam() {
	if (m_Tracker != nullptr) {
		double *pos = m_Tracker->getPos();
		glPushMatrix(); {
			glTranslated(pos[0]/2.0, pos[1]/2.0, 0);
			glColor3f(1.f, 1.f, 1.f);
			glScalef(10, 10, 10);
			glCallList(m_CamModel);
		}glPopMatrix();
	}
}

void GlRender::cleanUp() {

}