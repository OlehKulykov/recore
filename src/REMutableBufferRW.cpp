/*
 *   Copyright (c) 2012 - 2015 Kulykov Oleh <info@resident.name>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */


#include "../include/REMutableBufferRW.h"

#include <string.h>


RESizeT REMutableBufferRW::fileWrite(const void * bufferForWrite, const RESizeT dataSizeToWrite)
{
	if (bufferForWrite && dataSizeToWrite)
	{
		const RESizeT avaiableSize = _size - _offset;
		if (avaiableSize < dataSizeToWrite)
		{
			const RESizeT need = dataSizeToWrite - avaiableSize;
			if (!this->resize(_size + need, true)) return 0;
		}

		char * buff = (char *)_buff;
		if (buff && _size)
		{
			buff += _offset;
			memcpy(buff, bufferForWrite, dataSizeToWrite);
			_offset += dataSizeToWrite;
			return dataSizeToWrite;
		}

	}
	return 0;
}

RESizeT REMutableBufferRW::fileRead(void * bufferForReading, const RESizeT dataSizeToRead)
{
	if (_constCharBuffer && _size && bufferForReading && dataSizeToRead)
	{
		const char * buff = _constCharBuffer;
		RESizeT sizeToRead = dataSizeToRead;
		const RESizeT avaiableSize = _size - _offset;
		if (avaiableSize < sizeToRead)
		{
			sizeToRead = avaiableSize;
		}

		buff += _offset;
		memcpy(bufferForReading, buff, sizeToRead);
		_offset += sizeToRead;
		return sizeToRead;
	}
	return 0;
}

RESizeT REMutableBufferRW::fileTell()
{
	return _offset;
}

RESizeT REMutableBufferRW::fileSeek(const RESizeT fileOffset, int origin)
{
	RESizeT resultOffset = fileOffset;

	switch (origin)
	{
		case SEEK_CUR:
			resultOffset += _offset;
			break;

		case SEEK_END:
			if (_size < fileOffset)
			{
				return 2; // out of bounds
			}
			resultOffset = (_size - fileOffset);
			break;

		default:
			break;
	}

	if (resultOffset > _size) // common for SEEK_CUR && SEEK_SET
	{
		return 3; // out of bounds
	}

	_offset = resultOffset;
	return 0;
}

RESizeT REMutableBufferRW::fileSeekFromEndFile(const RESizeT fileOffset)
{
	return this->fileSeek(fileOffset, SEEK_END);
}

RESizeT REMutableBufferRW::fileSeekFromBeginFile(const RESizeT fileOffset)
{
	return this->fileSeek(fileOffset, SEEK_SET);
}

RESizeT REMutableBufferRW::fileSeekFromCurrentFilePos(const RESizeT fileOffset)
{
	return this->fileSeek(fileOffset, SEEK_CUR);
}

RESizeT REMutableBufferRW::fileFError()
{
	return 0;
}

RESizeT REMutableBufferRW::fileClose()
{
	return 0;
}

bool REMutableBufferRW::isEndOfFile()
{
	return (_size == _offset);
}

RESizeT REMutableBufferRW::offset() const
{
	return _offset;
}

REMutableBufferRW::REMutableBufferRW(const char * string) : REMutableBuffer(string),
	_offset(0)
{

}

REMutableBufferRW::REMutableBufferRW(const REMutableBuffer & buffer) : REMutableBuffer(buffer),
	_offset(0)
{

}

REMutableBufferRW::REMutableBufferRW(const REMutableBufferRW & buffer) : REMutableBuffer(buffer),
	_offset(0)
{

}

REMutableBufferRW::REMutableBufferRW(const REBuffer & buffer) : REMutableBuffer(buffer),
	_offset(0)
{

}

REMutableBufferRW::REMutableBufferRW(const REBufferR & buffer) : REMutableBuffer(buffer),
	_offset(0)
{

}

REMutableBufferRW::REMutableBufferRW(const void * memory, const RESizeT size) : REMutableBuffer(memory, size),
	_offset(0)
{

}

REMutableBufferRW::REMutableBufferRW(const RESizeT size) : REMutableBuffer(size),
	_offset(0)
{

}

REMutableBufferRW::REMutableBufferRW() : REMutableBuffer(),
	_offset(0)
{

}

REMutableBufferRW::~REMutableBufferRW()
{

}

