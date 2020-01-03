#pragma once
#include <Eigen/core>
#include <Eigen/Geometry>
using namespace std;
class Movable
{
public:
	Movable();
	Eigen::Matrix4f MakeTrans();
	void MyTranslate(Eigen::Vector3f amt);
	void MyTranslate2(Eigen::Vector3f amt);
	void MyRotate(Eigen::Vector3f rotAxis,float angle);
	void MyScale(Eigen::Vector3f amt);
	void reset_matrix();
	Eigen::Transform<float, 3, Eigen::Affine> Translate1;
	Eigen::Transform<float, 3, Eigen::Affine> Translate2;
	Eigen::Transform<float, 3, Eigen::Affine> Translate3;
	Eigen::Transform<float, 3, Eigen::Affine> Phi;
	Eigen::Transform<float, 3, Eigen::Affine> Psi;
	Eigen::Transform<float, 3, Eigen::Affine> Theta;
	Eigen::Transform<float,3,Eigen::Affine> Scale;
	Eigen::Transform<float, 3, Eigen::Affine> IK;
	void to_euler();
	Eigen::Vector3f to_euler(Eigen::Matrix3f);
};

