#include "SkySphere.h"

SkySphere::SkySphere(const char* fileName)
{

}


SkySphere::~SkySphere()
{
	for (auto& v : vList) {
		if (v != nullptr)
		{
			delete v;
			v = nullptr;
		}
	}
	vList.clear();
}
