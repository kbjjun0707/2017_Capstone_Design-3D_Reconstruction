#include "filerender.h"

#include <qmessagebox.h>

#include <gl/glu.h>


FileRender::FileRender(QWidget* parent) {
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setProfile(QSurfaceFormat::CoreProfile);
	this->setFormat(format);

	m_DataSizeX = 1;
	m_DataSizeY = 1;

	m_ColorModel = 0;
	m_Model = 0;
	m_ModelViewBox = 0;

	m_Scale = 1.f;
	m_Min = 0;
	m_Max = 255;

	m_ViewBoxVisable = true;
	m_ColorVertexVisiable = true;
}

FileRender::~FileRender() {
	glDeleteLists(m_ColorModel, 1);
	glDeleteLists(m_Model, 1);
}

void FileRender::setColorVertexVisiable(bool visiable) {
	m_ColorVertexVisiable = visiable;
}

void FileRender::setViewBoxVisiable(bool visiable) {
	m_ViewBoxVisable = visiable;
}

void FileRender::setZScale(float scale, float min, float max) {
	m_Scale = scale;
	m_Max = max;
	m_Min = min;
}

void FileRender::initializeGL() {
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
	for (int i = 0; i < num * 3; i += 3) {
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

	m_Cam.setPosition(0, 0, 650);

	startTimer(40);
}

void FileRender::resizeGL(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	gluPerspective(45, (float)w / h, 0.1, 10000);
}

void FileRender::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float camMat[16] = { 0 };
	m_Cam.getCamMat(camMat);
	glMultMatrixf(camMat);

	glPushMatrix(); {
		glTranslatef(0, 0, m_Min);

		glScalef(1.f, 1.f, (m_Max - m_Min));
		if (m_ViewBoxVisable) {
			glPushMatrix(); {
				glColor3f(1.f, 0.f, 0.f);
				glScalef(m_DataSizeX, m_DataSizeY, 1);
				glTranslatef(0.f, 0.f, -0.5f);
				glCallList(m_ModelViewBox);
			}glPopMatrix();
		}
		glPushMatrix(); {
			if (m_ColorModel != 0 && m_ColorModel != 0) {
				glPushAttrib(GL_POINT_BIT);
				glPointSize(m_Scale);
				if (m_ColorVertexVisiable)
					glCallList(m_ColorModel);
				else
					glCallList(m_Model);
				glPopAttrib();
			}
		}glPopMatrix();


	}glPopMatrix();

}

void FileRender::timerEvent(QTimerEvent * e) {

	update();
}

void FileRender::wheelEvent(QWheelEvent * e) {
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

void FileRender::mousePressEvent(QMouseEvent * e) {
	mouseClicked = true;

	xAtPress = e->x();
	yAtPress = e->y();
	xPre = xAtPress;
	yPre = yAtPress;
	dx = 0; dy = 0;
}

void FileRender::mouseMoveEvent(QMouseEvent * e) {
	if (mouseClicked) {

		dx = (e->x() - xPre);
		dy = (e->y() - yPre);

		xPre += dx;
		yPre += dy;

		m_Cam.rotateAround(dx, glm::fvec3(0, 1, 0));
	}
}

void FileRender::mouseReleaseEvent(QMouseEvent * e) {
	int xAtRelease = e->x();
	int yAtRelease = e->y();

	mouseClicked = false;
}

void FileRender::render(const char * fileName) {
	FILE *fp;
	fopen_s(&fp, fileName, "r");
	if (!fp) {
		QMessageBox::warning(this, "Fail", "failed to create file");
		return;
	}
	char buf[50];
	fgets(buf, 49, fp);
	fgets(buf, 49, fp);
	fgets(buf, 49, fp);
	fscanf_s(fp, " %s", buf, 49);
	fscanf_s(fp, " %s", buf, 49);
	fscanf_s(fp, " %d", &m_DataSizeX);
	fscanf_s(fp, " %s", buf, 49);
	fscanf_s(fp, " %d", &m_DataSizeY);
	fscanf_s(fp, " %s", buf, 49);
	fscanf_s(fp, " %s", buf, 49);
	int vertexnum;
	fscanf_s(fp, "%d", &vertexnum);

	float *xyz = new float[vertexnum*3];
	unsigned char *color = new unsigned char[vertexnum*3];
	int r = 0, g = 0, b = 0;
	for (int i = 0; i < vertexnum; i ++) {
		fscanf_s(fp, "%f %f %f %d %d %d",
			&xyz[(i * 3) + 0], &xyz[(i * 3) + 1], &xyz[(i * 3) + 2], &r, &g, &b);
		color[(i * 3) + 0] = r; color[(i * 3) + 1] = g; color[(i * 3) + 2] = b;
	}
	fclose(fp);

	glDeleteLists(m_ColorModel, 1);
	glDeleteLists(m_Model, 1);

	m_ColorModel = glGenLists(1);
	glNewList(m_ColorModel, GL_COMPILE);
	glTranslatef(-m_DataSizeX / 2.0, -m_DataSizeY / 2.0, -1.f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, color);
	glVertexPointer(3, GL_FLOAT, 0, xyz);
	glDrawArrays(GL_POINTS, 0, m_DataSizeX*m_DataSizeY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glEndList();

	m_Model = glGenLists(1);
	glNewList(m_Model, GL_COMPILE);
	glTranslatef(-m_DataSizeX / 2.0, -m_DataSizeY / 2.0, -1.f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(0.f, 0.8f, 0.f);
	glVertexPointer(3, GL_FLOAT, 0, xyz);
	glDrawArrays(GL_POINTS, 0, m_DataSizeX*m_DataSizeY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glEndList();


	delete[]xyz;
	delete[]color;
}
