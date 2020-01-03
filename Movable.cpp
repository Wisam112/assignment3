#include "Movable.h"

Movable::Movable()
{
	Translate1 = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Translate2 = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Translate3 = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Phi = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Psi = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Theta = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Scale = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	IK= Eigen::Transform<float, 3, Eigen::Affine>::Identity();
}

Eigen::Matrix4f Movable::MakeTrans()
{
	
	return Eigen::Transform<float, 3, Eigen::Affine>::Identity().matrix();
}

void Movable::MyTranslate(Eigen::Vector3f amt)
{
	Translate1.pretranslate(amt);
}

void Movable::MyTranslate2(Eigen::Vector3f amt)
{
	Translate2.pretranslate(amt);
}

//angle in radians
void Movable::MyRotate(Eigen::Vector3f rotAxis, float angle)
{
	if (rotAxis[0] != 0) {
		Phi.rotate(Eigen::AngleAxisf(angle, Eigen::Vector3f(rotAxis[0], 0, 0)));
	} if (rotAxis[1] != 0) {
		Theta.rotate(Eigen::AngleAxisf(angle, Eigen::Vector3f(0, rotAxis[1], 0)));
		Psi.rotate(Eigen::AngleAxisf(angle, Eigen::Vector3f(0, -rotAxis[1], 0)));
	}
}


void Movable::MyScale(Eigen::Vector3f amt)
{
	Scale.scale(amt);
}

void Movable::reset_matrix() {
	Translate1 = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Translate2 = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Translate3 = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Phi = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Psi = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Theta = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Scale = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	IK = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
}

void Movable::to_euler()
{
	Eigen::Matrix3f m;
	Eigen::Matrix4f m1;
	m1 = Theta.matrix() * Phi.matrix() * Psi.matrix()*IK.matrix();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m(i, j) = m1(i, j);
	Eigen::Vector3f angles; 
	//angles = m.eulerAngles(1, 0, 1);
	angles = to_euler(m);
	Phi = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Psi = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Theta = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	IK = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
	Phi.rotate(Eigen::AngleAxisf(angles[1] , Eigen::Vector3f(1, 0, 0)));
	Theta.rotate(Eigen::AngleAxisf(angles[0] , Eigen::Vector3f(0, 1, 0)));
	Psi.rotate(Eigen::AngleAxisf(angles[2] , Eigen::Vector3f(0, 1, 0)));
	
	//printf("%f ,%f ,%f  euler angles ", angles[0] , angles[1] , angles[2] );
}

Eigen::Vector3f Movable::to_euler(Eigen::Matrix3f m)
{
	float x, y0, y1;
	if (m(1, 1) < 1)
	{
		if (m(1, 1) > -1)
		{
			x = std::acos(m(1, 1));
			y0 = std::atan2(m(0, 1), m(2, 1));
			y1 = std::atan2(m(1, 0), -1*m(1, 2));
		}
		else 
		{
			x = M_PI;
			y0 = -1 * std::atan2(m(0, 2), m(0, 0));
			y1 = 0;
		}
	
	}
	else
	{
		x = 0;
		y1 = 0;
		y0 = std::atan2(m(0, 2), m(0, 0));
	}

	return Eigen::Vector3f(y0,x,y1);
}
