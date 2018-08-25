#pragma once



namespace Core::Containers
{

template <typename T, unsigned int MaxElements = 256>
class BufferStream
{
	/// Physical stack buffer to place elements in
	T buffer [MaxElements];

	/// Index into the buffer to make insertions to
	unsigned int writeIndex;

public:

	using Type = T;
	static const unsigned int maxElements = MaxElements;

	BufferStream ();

	/// Temporarily non-copyable
	BufferStream (const BufferStream & copy) = delete;

	~BufferStream ();

	/// Temporarily non-copyable
	BufferStream & operator= (const BufferStream & rhs) = delete;

	/// Request a new object in the buffer
	inline T & Allocate ()
	{
		/// @todo Assert that writeIndex never exceeds MaxElements, or wrap writeIndex around to 0
		return buffer[writeIndex++];
	}

	/// const getter
	inline const T * Buffer () const { return buffer; }

	/// non-const getter
	inline T * Buffer () { return buffer; }

	/// Size of the buffer
	inline unsigned int Size () const { return writeIndex; }

	/// "Empties" the buffer by resetting the write index
	inline void Clear () { writeIndex = 0; }
};

}
