#pragma once

#include "transform_.h"

namespace jun {

	/*
	ī�޶��� �⺻ ����
		Pos = { 0, 0, 0 }
		Up = { 0, 1, 0 }, Dir = { 0, 0, -1 }
	*/
	class Camera : public Transform {

	public:
		Camera(const glm::fvec3 &p_Pos);
		Camera(const float *p_Pos);
		Camera(float x = 0, float y = 0, float z = 0);

		// 4x4 matrix
		void getCamMat(float *dst);
		// point3
		void getTarget(float *dst);
		// vec3 (target - pos)
		void getFront(float *dst);
		// vec3
		void getUp(float *dst);

		void rotateAround(const float dgree, const glm::fvec3 &axis, const glm::fvec3 &center = glm::fvec3(0, 0, 0));
	};

}