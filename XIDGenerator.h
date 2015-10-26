//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef _IDGENERATOR_H_
#define _IDGENERATOR_H_
#include "Array.h"

class CXIDGenerator
{
private:
	u32 mIdBlockBase;
	u32 mIdRangeSize;
	Array<u32> mPool;
	u32 mNextId;

	void reclaim();

public:
	CXIDGenerator(u32 base, u32 numIds)
	{
		//VECTOR_SET_ASSOCIATION(mPool);

		mIdBlockBase = base;
		mIdRangeSize = numIds;
		mNextId = mIdBlockBase;
	}

	void reset()
	{
		mPool.clear();
		mNextId = mIdBlockBase;
	}

	u32 alloc()
	{
		// fist check the pool:
		if(!mPool.empty())
		{
			u32 id = mPool.back();
			mPool.pop_back();
			reclaim();
			return id;
		}
		if(mIdRangeSize && mNextId >= mIdBlockBase + mIdRangeSize)
			return 0;

		return mNextId++;
	}

	void free(u32 id)
	{
		CXASSERT(id >= mIdBlockBase);
		if(id == mNextId - 1)
		{
			mNextId--;
			reclaim();
		}
		else
			mPool.push_back(id);
	}

	u32 numIdsUsed()
	{
		return mNextId - mIdBlockBase - mPool.size();
	}
};
inline void CXIDGenerator::reclaim()
{
	// attempt to keep the pool vector as small as possible by reclaiming
	// pool entries back into the nextIdBlock variable

	while (!mPool.empty() && (mPool.back() == (mNextId-1)) )
	{
		mNextId--;
		mPool.pop_back();
	}
}
#endif
