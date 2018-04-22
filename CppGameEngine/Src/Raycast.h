#pragma once
#include "vendor/physics/q3.h"


class Raycast : public q3QueryCallback
{
public:
	q3RaycastData data;
	r32 tfinal;
	q3Vec3 nfinal;
	q3Body *impactBody;

	bool ReportShape(q3Box *shape)
	{
		if (data.toi < tfinal)
		{
			tfinal = data.toi;
			nfinal = data.normal;
			impactBody = shape->body;
		}

		data.toi = tfinal;
		return true;
	}

	void Init(const q3Vec3& spot, const q3Vec3& dir)
	{
		data.start = spot;
		data.dir = q3Normalize(dir);
		data.t = r32(10000.0);
		tfinal = FLT_MAX;
		data.toi = data.t;
		impactBody = nullptr;
	}
};
