#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <string>
#include "Container.h"
#include "Base.h"
#include "Shapes.h"


Shape * CreateRandomShape()
{
	int shapeID = 1 + rand() % 6;
	Shape * result;
	switch( shapeID )
	{
		case 1:
		{
			result = new Point();
			break;
		}
		case 2:
		{
			result = new Circle();
			break;
		}
		case 3:
		{
			result = new Rect();
			break;
		}
		case 4:
		{
			result = new Square();
			break;
		}
		case 5:
		{
			result = new Polyline();
			break;
		}
		case 6:
		{
			result = new Polygon();
			break;
		}
		default:
			result = new Point();
	}
	result->SetRandom();
	return result;
}

int main()
{
	// create shapes
	Container< Shape * > shapes;
	for( int cnt = 0; cnt < 20; ++cnt )
	{
		Shape * shape = CreateRandomShape();
		shapes.AddLast( shape );
	}
	std::cout << "Shapes Counter " << Shape::GetCount() << std::endl << std::endl;

	// print shapes
	for( shapes.ResetCurrent(); shapes.HasNext(); shapes.MoveCurrent() )
	{
		std::cout << * shapes.GetCurrent() << std::endl << std::endl;
	}
	std::cout << * shapes.GetCurrent() << std::endl << std::endl;

	// delete shapes
	while( ! shapes.IsEmpty() )
	{
		delete shapes.GetFirst();
		shapes.RemoveFirst();
	}
	std::cout << "Shapes Counter " << Shape::GetCount() << std::endl << std::endl;

	return 0;
}
