class Printable
{
public:
	virtual std::string print() const = 0;
};


class Named : public Printable
{
public:
	Named( std::string const & iName ) : m_name( iName )
	{}

	virtual std::string print() const
	{
		return m_name;
	}

	virtual ~Named()
	{}

protected:
	std::string m_name;
};
