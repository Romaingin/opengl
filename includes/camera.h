#ifndef CAMERA_H
#define CAMERA_H

#include "../includes/struct.h"

class CCamera
{
public:
	CVector3 m_vPosition;
	CVector3 m_vView;
	CVector3 m_vUpVector;

	CCamera();	
	
	void PositionCamera(float positionX, float positionY, float positionZ,
			 		    float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ);

	void RotateView(float angle, float X, float Y, float Z);

	void RotateAroundPoint(CVector3 vCenter, float angle, float x, float y, float z);

	void MoveCamera(float speed);
};

#endif