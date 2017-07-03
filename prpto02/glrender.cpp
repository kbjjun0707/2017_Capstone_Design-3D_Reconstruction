#include "glrender.h"
#include "mainwin.h"

#include "optical_.h"
#include "disparity.h"

#include <gl/glu.h>

#include <qdebug.h>


GlRender::GlRender(QWidget* parent) : QOpenGLWidget(parent) {
	m_Disparity = nullptr; m_Tracker = nullptr;

	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setProfile(QSurfaceFormat::CoreProfile);
	this->setFormat(format);

	m_ImgSizeX = 1;
	m_ImgSizeY = 1;
	m_ColorVertexVisiable = false;
	m_ViewBoxVisable = true;

	m_ScaleVal = 500.f;
}

GlRender::~GlRender() {
	cleanUp();
	m_Tracker = nullptr;
	m_Disparity = nullptr;
	glDeleteLists(m_ModelViewBox, 1);
}

void GlRender::setInit(jun::Tracker * p_Tracker, jun::DisparityMaker * p_Disparity) {
	m_Tracker = p_Tracker;
	m_Disparity = p_Disparity;
}

void GlRender::setColorVertexVisiable(bool visiable) {
	m_ColorVertexVisiable = visiable;
}

void GlRender::setViewBoxVisiable(bool visiable) {
	m_ViewBoxVisable = visiable;
}

void GlRender::initializeGL() {
	initializeOpenGLFunctions();
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	int num;
	float viewboxdata[48] = { 0 };
	FILE *fp;
	fopen_s(&fp, "Resources/viewbox.txt", "r");
	fscanf_s(fp, "%d", &num);
	for (int i = 0; i < num*3; i += 3) {
		fscanf_s(fp, "%f %f %f",
			&viewboxdata[i + 0], &viewboxdata[i + 1], &viewboxdata[i + 2]);
	};
	fclose(fp);

	m_ModelViewBox = glGenLists(1);
	glNewList(m_ModelViewBox, GL_COMPILE); {
		glPushAttrib(GL_POLYGON_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, viewboxdata);
		glDrawArrays(GL_QUADS, 0, sizeof(viewboxdata) / 12);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopAttrib();
	}glEndList();

	m_Cam.setPosition(0, 0, 778);

	startTimer(40);
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

	float camMat[16] = { 0 };
	m_Cam.getCamMat(camMat);
	glMultMatrixf(camMat);

	glPushMatrix(); {

		if (m_ViewBoxVisable) {
			glPushMatrix(); {
				glColor3f(1.f, 0.f, 0.f);
				glTranslatef(0.f, 0.f, -m_ScaleVal / 2.0);
				glScalef(m_ImgSizeX, m_ImgSizeY, m_ScaleVal);
				glCallList(m_ModelViewBox);
			}glPopMatrix();
		}
		glPushMatrix(); {
			drawScene();
		}glPopMatrix();
				

	}glPopMatrix();
}

void GlRender::timerEvent(QTimerEvent * e) {
	
	update();
}

void GlRender::wheelEvent(QWheelEvent * e) {
	int numDegrees = e->delta() / 8;
	int numSteps = numDegrees / 3;

	float camFront[3] = { 0 };
	m_Cam.getFront(camFront);

	if (e->orientation() == Qt::Horizontal) {
		m_Cam.translate(camFront[0] * numSteps, camFront[1] * numSteps, camFront[2] * numSteps);
	} else {
		m_Cam.translate(-camFront[0] * numSteps, -camFront[1] * numSteps, -camFront[2] * numSteps);
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

		dx = (e->x() - xPre);
		dy = (e->y() - yPre);

		xPre += dx;
		yPre += dy;

		m_Cam.rotateAround(dx, glm::fvec3(0, 1, 0));
	}
}

void GlRender::mouseReleaseEvent(QMouseEvent * e) {
	int xAtRelease = e->x();
	int yAtRelease = e->y();

	mouseClicked = false;
}

void GlRender::drawScene() {
	if (m_Disparity != nullptr && m_Disparity->isGet()) {
		m_ReprojectData = m_Disparity->getReprojectMat();
		m_ReprojectColorData = m_Disparity->getReprojectColor();
		m_ImgSizeX = (float)m_ReprojectData.cols;
		m_ImgSizeY = (float)m_ReprojectData.rows;
	}
	if (m_ReprojectData.size() == cv::Size(0, 0)) return;

	glTranslatef(-m_ImgSizeX / 2.0, -m_ImgSizeY / 2.0, -m_ScaleVal);
	glScalef(m_ImgSizeX, m_ImgSizeY, m_ScaleVal);
	glEnableClientState(GL_VERTEX_ARRAY);
	if (m_ColorVertexVisiable) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, m_ReprojectColorData.data);
	} else {
		glColor3f(0.f, 0.8f, 0.f);
	}
	glVertexPointer(3, GL_FLOAT, 0, m_ReprojectData.data);
	glDrawArrays(GL_POINTS, 0, m_ImgSizeX*m_ImgSizeY);
	glDisableClientState(GL_VERTEX_ARRAY);
	if (m_ColorVertexVisiable)
		glDisableClientState(GL_COLOR_ARRAY);
}

void GlRender::drawTrackCam() {
	
}

void GlRender::cleanUp() {
	m_ImgSizeX = 1;
	m_ImgSizeY = 1;
	m_ReprojectData.release();
	m_ReprojectColorData.release();
}