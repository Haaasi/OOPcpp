template< typename T > class Container
{
public:
	void AddFirst( T const & iData )
	{
		if( IsEmpty() )
		{
			Create( iData );
		}
		else
		{
			Element * second = m_first;
			m_first = new Element( iData, nullptr, second );
			second->prev = m_first;
			++m_size;
		}
	}

	void AddLast( T const & iData )
	{
		if( IsEmpty() )
		{
			Create( iData );
		}
		else
		{
			Element * penult = m_last;
			m_last = new Element( iData, penult, nullptr );
			penult->next = m_last;
			++m_size;
		}
	}

	void RemoveFirst()
	{
		if( IsEmpty() )
		{
			throw "removing from empty container";
		}
		else
		{
			Element * dead = m_first;
			m_first = m_first->next;
			if ( m_first )
			{
				m_first->prev = nullptr;
			}
			delete dead;
			--m_size;
		}
	}

	void RemoveLast()
	{
		if( IsEmpty() )
		{
			throw "removing from empty container";
		}
		else
		{
			Element * dead = m_last;
			m_last = m_last->prev;
			if ( m_last )
			{
				m_last->next = nullptr;
			}
			delete dead;
			--m_size;
		}
	}

	void ResetCurrent()
	{
		m_current = m_first;
	}

	bool HasNext() const
	{
		if( m_current )
		{
			return m_current->next != nullptr;
		}
		return false;
	}

	void MoveCurrent()
	{
		if( m_current )
		{
			m_current = m_current->next;
		}
		else
		{
			throw "current pointer is invalid";
		}
	}

	void Clear()
	{
		if( ! IsEmpty() )
		{
			Element * next = m_first->next;
			Element * dead = m_first;
			while( next )
			{
				delete dead;
				dead = next;
				next = next->next;
			}
			delete dead;
			m_size = 0;
			m_current = nullptr;
			m_last = nullptr;
			m_first = nullptr;
		}
	}

	bool IsEmpty() const
	{
		return 0 == m_size;
	}

	uint32_t GetSize() const
	{
		return m_size;
	}

	T GetFirst() const
	{
		return m_first->data;
	}

	T GetLast() const
	{
		return m_last->data;
	}

	T GetCurrent() const
	{
		return m_current->data;
	}

	Container()
		: m_first( nullptr )
		, m_last( nullptr )
		, m_current( nullptr )
		, m_size( 0 )
	{}

	Container( T const & iData )
	{
		Create( iData );
	}

	~Container()
	{
		Clear();
	}

	void Create( T const & iData )
	{
		m_first = new Element( iData, nullptr, nullptr );
		m_last = m_first;
		m_size = 1;
	}

	struct Element
	{
		T data;
		Element * prev;
		Element * next;

		Element( T const & iData, Element * iPrev, Element * iNext )
			: data( iData )
			, prev( iPrev )
			, next( iNext )
		{}
	};

	Element * m_first;
	Element * m_last;
	Element * m_current;
	uint32_t m_size;
};