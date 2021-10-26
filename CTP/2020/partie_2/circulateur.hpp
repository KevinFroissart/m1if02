/**
 * @author      : David JULIEN (david.julien@etu.univ-lyon1.fr)
 * @file        : sequence
 * @created     : Friday Sep 18, 2020 14:10:27 CEST
 */

#ifndef SEQUENCE_HPP

#define SEQUENCE_HPP

#include <iostream>

template <typename T>
class Sequence
{
    private:
        /* private data */
		size_t capacity_;
		size_t size_;
		T* data_;
    public:
        Sequence(const size_t capacity, const T& value)
			: capacity_(capacity), size_(capacity), data_(new T[capacity])
		{
			for(size_t i = 0; i < size_; i++)
			{
				data_[i] = value;
			}
		}

		Sequence(const Sequence<T>& toCopy)
			: capacity_(toCopy.capacity_), size_(toCopy.size_)
			, data_(new T[capacity_])
		{
			for(size_t i = 0; i < size_; i++)
			{
				data_[i] = toCopy.data_[i];
			}
		}

        virtual ~Sequence()
		{
			delete[] data_;
		}

		/* OPERATORS */

		Sequence<T>& operator=(const Sequence<T>& toCopy)
		{
			capacity_ = toCopy.capacity_;
			size_ = toCopy.size_;
			delete[] data_;
			data_ = new T[capacity_];
			for(size_t i = 0; i < size_; i++)
			{
				data_[i] = toCopy.data_[i];
			}

			return *this;
		}

		T& operator[](const size_t pos) { return data_[pos % capacity_]; }

		std::ostream& operator<<(std::ostream& output);

		/* GETTERS */
		size_t capacity() const { return capacity_; }

		size_t size() const { return size_; }

		T* data() { return data_; }

		/* METHODS */
		void insere(const size_t pos, const T& value)
		{
			if(size_ == capacity_) // data_ is full
			{
				capacity_ += 5;
			}
			T* buff = new T[capacity_];
			size_t truePos = pos % capacity_;
			for(size_t i = 0; i < size_; i++)
			{
				if(i < truePos)
				{
					buff[i] = data_[i];
				}
				else
				{
					if(i == truePos)
					{
						buff[i] = value;
						size_++;
					}
					else
					{
						buff[i] = data_[i - 1];
					}
				}
			}
			delete[] data_;
			data_ = buff;
		}

		int find(T value)
		{
			int pos = -1;
			for(size_t i = 0; i < size_; i++)
			{
				if(value == data_[i])
				{
					pos = (int) i;
				}
			}

			return pos;
		}

		/* ITERATOR */
		class Circulator
		{
			private:
        	/* private data */
				Sequence<T>* sequence_;
				size_t pos_ = 0;

			public:
				explicit Circulator(Sequence<T>& sequence)
					: sequence_(&sequence)
				{}

				explicit Circulator(Sequence<T>& sequence, size_t pos)
					: sequence_(&sequence), pos_(pos)
				{}

				virtual ~Circulator() {}

				bool operator==(const Circulator toComp)
				{
					return pos_ == toComp.pos_;
				}
				bool operator!=(const Circulator toComp)
				{
					return pos_ != toComp.pos_;
				}

				Circulator& operator++()
				{
					pos_ < (sequence_->size() - 1) ? forward() : reset();
					return *this;
				}

				Circulator& operator--()
				{
					pos_ > 0 ? backward() : jump(sequence_->size() - 1);
					return *this;
				}

				Circulator operator+(const int inc)
				{
					Circulator buff = Circulator(*this);
					for(int i = 0; i < inc; i++)
					{
						++(buff);
					}

					return buff;
				}

				Circulator operator-(const int dec)
				{
					Circulator buff = Circulator(*this);
					for(int i = 0; i < dec; i++)
					{
						--(buff);
					}

					return buff;
				}


				T* operator->() { return &(sequence_->data()[pos_]); }
				T& operator*() const { return (*sequence_)[pos_]; }

				void forward() { pos_++; }
				void backward() { pos_--; }
				void reset() { pos_ = 0; }
				void jump(size_t pos) { pos_ = pos; }

				size_t pos() const { return pos_; }

		};

		Circulator* begin() { return Circulator(*this); }
		Circulator* end() { return Circulator(*this, size_); }
		Circulator circulator(const size_t pos)
		{
			return Circulator(*this, pos % capacity_);
		}
};

template <typename T>
std::ostream& operator<<(std::ostream& output, Sequence<T>& sequence)
{
	for(size_t i = 0; i < sequence.size(); i++)
	{
		output << sequence.data()[i] << "\n";
	}

	return output;
}

#endif /* end of include guard SEQUENCE_HPP */

