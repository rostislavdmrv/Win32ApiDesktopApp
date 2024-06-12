
#if !defined(AFX_WIN32_7_H__A3B0A137_49AD_4CBE_BE1A_6CD68AAFC89C__INCLUDED_)
#define AFX_WIN32_7_H__A3B0A137_49AD_4CBE_BE1A_6CD68AAFC89C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class Rect
{
public:
	Rect() {};
	~Rect() {};

	POINTS begin;
	POINTS end;

	void Draw(HDC hdc)
	{
		Rectangle(hdc, begin.x, begin.y, end.x, end.y);
	}

	void DrawAsSelected(HDC hdc)
	{
		HPEN newpen = CreatePen(PS_DOT, 0 , RGB(0, 0, 255));
		HPEN oldpen = (HPEN)SelectObject(hdc, newpen);
		Rectangle(hdc, begin.x, begin.y, end.x, end.y);
		SelectObject(hdc, oldpen);
		DeleteObject(newpen);
	}

	Rect* HitTest(POINTS point)
	{
		if(point.x >= begin.x && point.x < end.x && point.y <= end.y && point.y > begin.y)
			return this;
		return NULL;
	}

	void MoveFromTo(POINTS from, POINTS to)
	{
		begin.x = begin.x + to.x - from.x;
		end.x = end.x + to.x - from.x;
		begin.y = begin.y + to.y - from.y;
		end.y = end.y + to.y - from.y;
	}
};

#endif // !defined(AFX_WIN32_7_H__A3B0A137_49AD_4CBE_BE1A_6CD68AAFC89C__INCLUDED_)
