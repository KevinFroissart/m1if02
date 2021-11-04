#ifndef SEQ_CIRC
#define SEQ_CIRC
#define SEQ_CIRC_DEFAULT_EXPENSION 10

template <class T>
class SequenceCirculaire
{
public:
	using value_type = T;
	using reference = value_type &;
	using const_reference = const value_type &;
	using index_type = int;

	SequenceCirculaire() : periode(0),
						   capacity(0),
						   expansion_factor(SEQ_CIRC_DEFAULT_EXPENSION),
						   data(nullptr)
	{
		std::cout << "SequenceCirculaire()" << std::endl;
	}

	SequenceCirculaire(const index_type &i, const_reference v) : periode(0),
																 capacity(0),
																 expansion_factor(SEQ_CIRC_DEFAULT_EXPENSION),
																 data(nullptr)
	{
		std::cout << "SequenceCirculaire(const index_type &i, const_reference v)" << std::endl;
		periode = i;
		capacity = (i / expansion_factor + 1) * expansion_factor;
		data = new value_type[capacity];
		for (index_type j = 0; j < periode; ++j)
		{
			data[j] = v;
		}
	}

	SequenceCirculaire(const SequenceCirculaire &that) : periode(that.periode),
														 capacity(that.capacity),
														 expansion_factor(that.expansion_factor),
														 data(new value_type[capacity])
	{
		std::cout << "SequenceCirculaire(const SequenceCirculaire &that)" << std::endl;
		for (index_type i = 0; i < periode; ++i)
		{
			data[i] = that.data[i];
		}
	}

	SequenceCirculaire &operator=(const SequenceCirculaire &that) noexcept
	{
		std::cout << "operator=(const SequenceCirculaire &that)" << std::endl;
		if (this == &that)
		{
			return *this;
		}
		else
		{
			delete[] data;
			capacity = that.capacity;
			periode = that.periode;
			expansion_factor = that.expansion_factor;
			data = new value_type[capacity];
			for (index_type i = 0; i < periode; ++i)
			{
				data[i] = that.data[i];
			}
			return *this;
		}
	}

	SequenceCirculaire(SequenceCirculaire &&that) : periode(that.periode),
													capacity(that.capacity),
													expansion_factor(that.expansion_factor),
													data(that.data)
	{
		std::cout << "SequenceCirculaire(SequenceCirculaire &&that)" << std::endl;
		that.data = nullptr;
	}

	SequenceCirculaire &operator=(SequenceCirculaire &&that)
	{
		std::cout << "operator=(SequenceCirculaire &&that)" << std::endl;
		if (&that != this)
		{
			delete[] data;
			capacity = that.capacity;
			periode = that.periode;
			expansion_factor = that.expansion_factor;
			data = that.data;
			that.data = nullptr;
		}
		return *this;
	}

	~SequenceCirculaire()
	{
		std::cout << "~SequenceCirculaire()" << std::endl;
		delete[] data;
	}

	reference operator[](index_type i)
	{
		return data[i % periode];
	}

	const_reference operator[](index_type i) const
	{
		return const_cast<const_reference>(data[i % periode]);
	}

	void insert(const_reference v, index_type position)
	{
		index_type pos = position % (periode + 1);
		if (periode == capacity)
		{
			expand(v, pos);
		}
		else
		{
			for (index_type i = periode; i > pos; --i)
			{
				data[i] = data[i - 1];
			}
			data[pos] = v;
			++periode;
		}
	}

	index_type search(const_reference v)
	{
		for (index_type i = 0; i < periode; i++)
		{
			if (data[i] == v)
			{
				return i;
			}
		}
		return -1;
	}

	void display()
	{
		std::cout << "Diplaying SeqCirc :" << std::endl
				  << "\t";
		for (index_type i = 0; i < periode; ++i)
		{
			std::cout << data[i] << "\t";
		}
		std::cout << std::endl;
	}

	class iterator
	{
	public:
		iterator(SequenceCirculaire<T> &seq, const index_type &p) : position(p),
																	target(&seq)
		{
			std::cout << "iterator(SequenceCirculaire<T> &seq, const index_type &p)" << std::endl;
		}

		iterator(const iterator &that) : position(that.position),
										 target(that.target)
		{
			std::cout << "iterator(const iterator &that)" << std::endl;
		}

		const bool operator!=(const iterator &that)
		{
			return (target != that.target) || (position != that.position);
		}

		const bool operator==(const iterator &that)
		{
			return !operator==(that);
		}

		iterator &operator=(iterator &&that)
		{
			std::cout << "&operator=(iterator &&that)" << std::endl;
			if (this != &that)
			{
				position = that.position;
				target = that.target;
			}
			return *this;
		}

		iterator &operator=(const iterator &that)
		{
			std::cout << "&operator=(const iterator &that)" << std::endl;
			if (this != &that)
			{
				position = that.position;
				target = that.target;
			}
			return *this;
		}

		~iterator()
		{
			std::cout << "~iterator() " << std::endl;
		}

		iterator &operator++()
		{
			++position;
			return *this;
		}

		iterator &operator++(int)
		{
			++position;
			return *this;
		}

		value_type &operator*()
		{
			return (*target)[position];
		}

	private:
		index_type position;
		SequenceCirculaire<T> *target;
	};

	iterator begin(const index_type &p)
	{
		return iterator(*this, p);
	}

	iterator end(const index_type &p)
	{
		return iterator(*this, periode + p);
	}

private:
	void expand(const_reference v, index_type position)
	{
		capacity += expansion_factor;
		value_type *new_data = new value_type[capacity];
		for (index_type i = 0; i < position; ++i)
		{
			new_data[i] = data[i];
		}
		new_data[position] = v;
		++periode;
		for (index_type i = position + 1; i < periode; ++i)
		{
			new_data[i] = data[i - 1];
		}
		delete[] data;
		data = new_data;
	}

private:
	index_type periode;
	index_type capacity;
	index_type expansion_factor;
	value_type *data;
};

#endif // SEQ_CIRC
