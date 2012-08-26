#ifndef _GEN_ARENA_H_INCLUDED_
#define _GEN_ARENA_H_INCLUDED_

#include <memory>
#include <vector>

// Define allocation alignments for various platforms
#ifdef WIN32
#define ALLOC_ALIGNMENT 8
#else
#error "Cog::Generics::Arena<> is not defined for this platform"
#endif

namespace Cog
{
	namespace Generics
	{
		template <size_t pageSize = 16384> class Arena
		{
			// Sanity-checking:
			static_assert((ALLOC_ALIGNMENT & (ALLOC_ALIGNMENT - 1)) == 0, "Size is not a power of two.");
			static_assert(pageSize >= ALLOC_ALIGNMENT, "Page size less than alignment size.");

		private:
			__declspec(align(ALLOC_ALIGNMENT)) class Page
			{
			public:
				unsigned char data[pageSize];
				size_t allocSize;

				Page()
				{
					allocSize = 0;
				}
			};

			std::vector<std::unique_ptr<Page>> pages;
			
		public:
			Arena()
			{
				// Generate initial page:
				pages.push_back(std::unique_ptr<Page>(new Page));
			}

		private:
			inline void* alignedAllocate(size_t alignedSize)
			{
				if(alignedSize > pageSize)
				{
					throw std::bad_alloc();
				}

				// Determine if there is enough space for the allocation on the current page:
				Page* p = pages.back().get();

				if((alignedSize + p->allocSize) > pageSize)
				{
					// Not enough space. Allocate new page:
					pages.push_back(std::unique_ptr<Page>(new Page));
					p = pages.back().get();
				}

				// Enough space. Allocate object:
				void* ptr = &p->data[p->allocSize];
				p->allocSize += alignedSize;

				return ptr;
			}

		public:
			inline void* Allocate(size_t size)
			{
				// Determine the actual size of the allocation, based on specified alignment
				size_t alignment = ALLOC_ALIGNMENT - 1;
				size_t alignment_mask = ~alignment;
				size = (size + alignment) & alignment_mask;

				return alignedAllocate(size);
			}
		};
	}
}

inline void* operator new(size_t size, Cog::Generics::Arena<>& s)
{
	return s.Allocate(size);
}

inline void operator delete(void* obj, Cog::Generics::Arena<>& s)
{
	// Does nothing. Memory is collected when the Arena object
	// is destroyed.
}

#endif // _GEN_ARENA_H_INCLUDED_
