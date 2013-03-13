#pragma once

#include "types.h"
#include <cassert>

class ReferenceCounter
{
private:
	mutable s32 ref;

public:
	ReferenceCounter() : ref(1) {}
	virtual ~ReferenceCounter() {}		// for delete this

	void attach() const
	{
		++ref;
	}

	bool detach() const
	{
		// someone is doing bad reference counting
		assert(ref > 0 && "<ReferenceCounter> counting error");

		if (--ref == 0)
		{
			delete this;
			return true;
		}

		return false;
	}

	s32 getReferenceCount() const
	{
		return ref;
	}
};
