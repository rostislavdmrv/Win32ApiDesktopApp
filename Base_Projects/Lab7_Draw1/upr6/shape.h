#if !defined SHAPE_H
#define SHAPE_H

#include "resource.h"
#include <assert.h>

enum shpType {
	line,rect
};

class Shape{
public:
	POINTS begin;
	POINTS end;
	Shape(){};
	~Shape(){};
	Shape(const Shape& s){
		begin=s.begin;
		end = s.end;
	}
	Shape& operator=(const Shape& s){
		begin=s.begin;
		end=s.end;
		return *this;
	}
	virtual void Draw(HDC hds){
		assert(FALSE);
	}
};

class Line: public Shape{
public:
	virtual void Draw(HDC hdc){
		MoveToEx(hdc,begin.x,begin.y,NULL);
		LineTo(hdc,end.x,end.y);
	}
};

class Rect: public Shape{
public:
	virtual void Draw(HDC hdc){
		Rectangle(hdc,begin.x,begin.y,end.x,end.y);
	}
};
#endif
