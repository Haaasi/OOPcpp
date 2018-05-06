class Shape : public Printable
{
public:
	static uint32_t GetCount()
	{
		return Shape::sm_counter;
	}

	Shape()
	{
		++Shape::sm_counter;
	}

	virtual ~Shape()
	{
		--Shape::sm_counter;
	}

	virtual void SetRandom() = 0;

private:
	static uint32_t sm_counter;

};

uint32_t Shape::sm_counter = 0;
std::ostream & operator << ( std::ostream & ioStream, Shape const & iShape )
{
	return ioStream << iShape.print();
}


class Point : public Named, public Shape
{
public:
	std::string print() const override
	{
		return "shape " + Named::print() + "\n"
			   + "x = " + std::to_string(m_x) + "\n"
			   + "y = " + std::to_string(m_y);
	}

	void SetRandom() override
	{
		m_x = 1 + rand() % 10;
		m_y = 1 + rand() % 10;
	}

	double GetDistToPoint( Point const & iPoint )
	{
		return sqrt( pow( m_x - iPoint.m_x, 2 ) + pow( m_y - iPoint.m_y, 2 ) );
	}

	Point() : Named( "Point" )
	{}

	Point( double iX, double iY ) : Point()
	{
		m_x = iX;
		m_y = iY;
	}

	Point( Point const & iPoint ) : Point( iPoint.m_x, iPoint.m_y )
	{}

	double m_x;
	double m_y;
};


class Circle : public Named, public Shape
{
public:
	std::string print() const override
	{
		return "shape " + Named::print() + "\n"
			   + "centr = " + m_center.print() + "\n"
			   + "radius = " + std::to_string( m_radius ) + "\n"
			   + "square = " + std::to_string( GetSquare() ) + "\n"
			   + "length = " + std::to_string( GetLength() );
	}

	void SetRandom() override
	{
		m_center.SetRandom();
		m_radius = 1 + rand() % 10;
	}

	double GetSquare() const
	{
		return M_PI * pow( m_radius, 2 );
	}

	double GetLength() const
	{
		return M_PI * 2 * m_radius;
	}

	Circle() : Named( "Cirlce" )
	{}

	Circle( Point iCenter, double iRadius )
		: m_center( iCenter )
		, m_radius( std::abs( iRadius ) )
		, Named( "Cirlce" )
	{}

	Point m_center;
	double m_radius;
};


class Rect : public Named, public Shape
{
public:
	std::string print() const override
	{
		return "shape " + Named::print() + "\n"
			   + "leftBot = " + leftBot.print() + "\n"
			   + "rightTop = " + rightTop.print() + "\n"
			   + "square = " + std::to_string( GetSquare() ) + "\n"
			   + "perimeter = " + std::to_string( GetPerimeter() );
	}

	void SetRandom() override
	{
		double x1 = 1 + rand() % 10;
		double x2 = 1 + rand() % 10;
		double y1 = 1 + rand() % 10;
		double y2 = 1 + rand() % 10;
		leftBot.m_x = fmin( x1, x2 );
		leftBot.m_y = fmin( y1, y2 );
		rightTop.m_x = fmax( x1, x2 );
		rightTop.m_y = fmax( y1, y2 );
	}

	double GetSquare() const
	{
		return GetWidth() * GetHeight();
	}

	double GetPerimeter() const
	{
		return 2 * ( GetWidth() + GetHeight() );
	}

	double GetWidth() const
	{
		return rightTop.m_x - leftBot.m_x;
	}

	double GetHeight() const
	{
		return rightTop.m_y - leftBot.m_y;
	}

	Rect() : Named( "Rect" )
	{}

	Rect( double x1, double y1, double x2, double y2 )
		: leftBot( fmin( x1, x2 ), fmin( y1, y2 ) )
		, rightTop( fmax( x1, x2 ), fmax( y1, y2 ) )
		, Named( "Rect" )
	{}

	Rect( Point const & first, Point const & second )
		: Rect( first.m_x, first.m_y, second.m_x, second.m_y )
	{}

	Point leftBot;
	Point rightTop;
};


class Square : public Rect
{
public:
	virtual void SetRandom()
	{
		leftBot.SetRandom();
		double width = 1 + rand() % 10;
		rightTop.m_x = leftBot.m_x + width;
		rightTop.m_y = leftBot.m_y + width;
	}

	Square()
	{
		m_name = "Square";
	}

	Square( double x, double y, double width )
		: Rect( x, y, x + width, y + width )
	{
		m_name = "Square";
	}

	Square( Point const & leftBot, double width )
		: Square ( leftBot.m_x, leftBot.m_y, width )
	{}
};


class Polyline : public Named, public Shape
{
public:
	std::string print() const override
	{
		std::string result = "shape " + Named::print() + "\n";
		Container< Point >::Element * curr = m_points.m_first;
		while ( curr->next )
		{
			result += curr->data.print() + "\n";
			curr = curr->next;
		}
		result += curr->data.print() + "\n";
		result += "length = " + std::to_string( GetLength() );
		return result;
	}

	void SetRandom() override
	{
		int size = 1 + rand() % 10;
		for ( int cnt = 0; cnt < size; ++cnt )
		{
			Point p;
			p.SetRandom();
			AddPoint( p );
		}
	}

	void AddPoint( Point const & iPoint )
	{
		m_points.AddLast( iPoint );
	}

	virtual double GetLength() const
	{
		double length = 0;
		Container< Point >::Element * curr = m_points.m_first;
		Container< Point >::Element * next;
		while ( curr->next )
		{
			next = curr->next;
			length += curr->data.GetDistToPoint( next->data );
			curr = next;
		}
		return length;
	}

	Polyline()
		: m_points()
		, Named( "Polyline" )
	{}

	Polyline( Point const & iPoint ) : Polyline()
	{
		AddPoint( iPoint );
	}

	Container< Point > m_points;
};


class Polygon : public Polyline
{
public:
	virtual double GetLength() const
	{
		return Polyline::GetLength() + m_points.GetFirst().GetDistToPoint( m_points.GetLast() );
	}

	Polygon() : Polyline()
	{
		m_name = "Polygon";
	}

	Polygon( Point const & iPoint ) : Polyline( iPoint )
	{
		m_name = "Polygon";
	}
};
