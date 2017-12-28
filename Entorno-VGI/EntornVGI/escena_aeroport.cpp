#include "stdafx.h"
#include "material.h"
#include "escena.h"

void terminal() {
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 1, 0);
		glTranslatef(0, -5, -60);
		glScalef(5, 5, 5);
		glCallList(TERMINAL);
	glPopMatrix();
}

void pista() {
	glPushMatrix();
		//glColor3f(1.0, 0.0, 0.0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 1, 0);
		glScalef(30, 30, 30);
		glCallList(PISTA);
	glPopMatrix();
}

void finger() {
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, -0.75, 0);
		glScalef(0.2, 0.2, 0.2);
		glCallList(FINGER);
	glPopMatrix();
}

void finger1() {
	glPushMatrix();
	glTranslatef(37, 0, 0);
	glRotatef(-45, 0, 0, 1);
	finger();
	glPopMatrix();
}

void finger2() {
	glPushMatrix();
	glTranslatef(30, 0, 0);
	glRotatef(45, 0, 0, 1);
	finger();
	glPopMatrix();
}

void finger3() {
	glPushMatrix();
	glTranslatef(7, 0, 0);
	glRotatef(45, 0, 0, 1);
	finger();
	glPopMatrix();
}

void finger4() {
	glPushMatrix();
	glTranslatef(-16, 0, 0);
	glRotatef(45, 0, 0, 1);
	finger();
	glPopMatrix();
}

void fingers() {
	glPushMatrix();
	glTranslatef(0, -49, 0);


	if (MyVariable::getInstance()->getFingerList()[0] || MyVariable::getInstance()->getFingerList()[1])
		finger1();

	if (MyVariable::getInstance()->getFingerList()[0] || MyVariable::getInstance()->getFingerList()[2])
		finger2();

	if (MyVariable::getInstance()->getFingerList()[0] || MyVariable::getInstance()->getFingerList()[3])
		finger3();

	if (MyVariable::getInstance()->getFingerList()[0] || MyVariable::getInstance()->getFingerList()[4])
		finger4();
	

	glPopMatrix();
}

void aerportPrat(CColor col_object, bool ref_mat, bool sw_mat[4], bool textur, GLuint VTextu[NUM_MAX_TEXTURES])
{
	SeleccionaMaterialiColor(MAT_CAP, sw_mat, ref_mat, col_object);

	glPushMatrix();
		pista();
		terminal();
		fingers();
	glPopMatrix();

}

void drawAirplane(Airplane* airplane) {
	glPushMatrix();
	glTranslatef(airplane->getPosition()->x, airplane->getPosition()->y, airplane->getPosition()->z);
	glRotatef(airplane->getDirection()->z, 0, 0, 1);
	glRotatef(airplane->getDirection()->x, 1, 0, 0);
	glRotatef(airplane->getDirection()->y, 0, 1, 0);
	//glRotatef(90, 1, 0, 0);
	glScalef(0.0002, 0.0002, 0.0002);
	glCallList(PROMETHEUS);
	glPopMatrix();
}

void animationAirport(CColor col_object, bool ref_mat, bool sw_mat[4], bool textur, GLuint VTextu[NUM_MAX_TEXTURES]){
	aerportPrat(col_object, ref_mat, sw_mat, textur, VTextu);

	for (int i = 0; i < MyVariable::getInstance()->getAirplaneList().size(); i++) {
		drawAirplane(MyVariable::getInstance()->getAirplaneList()[i]);

		/*
		glPushMatrix();
			_D3DVECTOR pos = MyVariable::getInstance()->calcNextPosition(*MyVariable::getInstance()->getAirplaneList()[i]->getPosition(),
				*MyVariable::getInstance()->getAirplaneList()[i]->getDirection(), .5f);
			glTranslatef(pos.x, pos.y, pos.z + 0.5f);
			glScalef(1.f, 1.0f, 1.0f);
			glutSolidCube(1.0);
		glPopMatrix();
		*/
	}

	/*
	glPushMatrix();
		glTranslatef(60, -35, 0);
		//glRotatef(90, 1, 0, 0);
		glScalef(0.0002, 0.0002, 0.0002);
		glCallList(PROMETHEUS);
	glPopMatrix();
	*/
}



/*
AeroportPrat::AeroportPrat()
{
	COBJModel* terminal = NULL;
	COBJModel* landing_track = NULL;
	COBJModel* plane = NULL;
	COBJModel* finger = NULL;
}


AeroportPrat::~AeroportPrat()
{
}

void AeroportPrat::LoadFixedOBJ()
{
	glPushMatrix();
	glPushMatrix();
	SelectObject(this->terminal);
	glPopMatrix();

	glPushMatrix();
	SelectObject(this->landing_track);
	glPopMatrix();
	glPopMatrix();
}

bool AeroportPrat::SelectObject(COBJModel * obj)
{
	HGLRC     m_hRC;
	CDC*      m_pDC;
	CString fileName;
	CFileDialog openOBJ(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("OBJ Files(*.obj)|*.obj|Error Files (*.err)|*err|All Files (*.*)|*.*||"));
	if (openOBJ.DoModal() != IDOK)
		return false;
	else
		fileName = openOBJ.GetPathName();
	const char* name = (LPCSTR)fileName.GetString();
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	this->terminal->LoadModel((char*)name, OBJECTEOBJ);
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	return false;
}
*/