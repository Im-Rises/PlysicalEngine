#include "Matrix34.h"

Matrix34::Matrix34()
{
	for (int i = 0; i < 12; i++) {
		m_value[i] = 0;
	}
}

Matrix34::Matrix34(float values[12])
{
	for (int i = 0; i < 12; i++) {
		m_value[i] = values[i];
	}
}

Matrix33& Matrix34::extractMatrix33() const
{
	float valueRes[9];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			valueRes[3 * i + j] = m_value[4 * i + j];
		}
	}
	return Matrix33(valueRes);
}

void Matrix34::setFromRotationTranslation(Matrix33& const rotationMatrix, Vector3d& const translation)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m_value[4 * i + j] = rotationMatrix(i,j);
		}
	}
	m_value[3]=translation.x;
	m_value[7]=translation.y;
	m_value[11]=translation.z;
}

Matrix34& Matrix34::matrix34FromRotationTranslation(Matrix33& const rotationMatrix, Vector3d& const translation) const
{
	Matrix34 res;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			res. m_value[4 * i + j] = rotationMatrix(i, j);
		}
	}
	res.m_value[3] = translation.x;
	res.m_value[7] = translation.y;
	res.m_value[11] = translation.z;
	return res;
}

Matrix34 Matrix34::operator*(const Matrix34& other) const
{
	Matrix44 tempThis = transformationAffineMatrix();
	Matrix44 tempOther = other.transformationAffineMatrix();
	Matrix34 res = transformationAffineMatrixToMatrix34(tempThis * tempOther);
	return res;
}

Matrix34 Matrix34::inverse() const
{
	Matrix33 M33Inv = extractMatrix33().inverse();
	Vector3d vecInv;
	vecInv.x = -m_value[3];
	vecInv.y = -m_value[7];
	vecInv.z = -m_value[11];
	return matrix34FromRotationTranslation(M33Inv, vecInv);
}

void Matrix34::inverseMat()
{
	Matrix34 inv = inverse();
	for (int k = 0; k < 12; k++) {
		m_value[k] = inv.m_value[k];
	}
}

Vector3d Matrix34::TransformPosition(const Vector3d vec) const
{
	Vector3d res = extractMatrix33() * vec;
	res.x += m_value[3];
	res.y += m_value[7];
	res.z += m_value[11];
	return Vector3d();
}

Vector3d Matrix34::TransformDirection(const Vector3d vec) const
{
	return extractMatrix33() * vec;
}

Matrix34::~Matrix34()
{
	delete [] m_value;
}

Matrix34& Matrix34::transformationAffineMatrixToMatrix34(Matrix44& const mat44) const
{
	Matrix34 res;
	for (int k = 0; k < 12; k++) {
		res.m_value[k] = mat44[k];
	}
	return res;
}

Matrix44& Matrix34::transformationAffineMatrix() const
{
	float values[16];
	for (int k = 0; k < 12; k++) {
		values[k] = m_value[k];
	}
	values[12] = 0;
	values[13] = 0;
	values[14] = 0;
	values[15] = 1;
	return Matrix44(values);
}

void Matrix34::setOrientationAndPosition(Quaternion& const quaternion,Vector3d& const translation)
{
	Matrix33 rotationMatrix;
	rotationMatrix.setOrientation(quaternion);
	setFromRotationTranslation(rotationMatrix, translation);

}
