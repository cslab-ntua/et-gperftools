#ifndef TCMALLOC_MEMFS_ALLOC_H_
#define TCMALLOC_MEMFS_ALLOC_H_

// Hugetlbfs based allocator for tcmalloc
class HugetlbSysAllocator: public SysAllocator {
public:
  explicit HugetlbSysAllocator(SysAllocator* fallback)
    : failed_(true),  // To disable allocator until Initialize() is called.
      big_page_size_(0),
      hugetlb_fd_(-1),
      hugetlb_base_(0),
      fallback_(fallback) {
  }

  void* Alloc(size_t size, size_t *actual_size, size_t alignment);
  bool Initialize(char *memfs_path, int memfs_path_len);

  bool failed_;          // Whether failed to allocate memory.

private:
  void* AllocInternal(size_t size, size_t *actual_size, size_t alignment);

  int64 big_page_size_;
  int hugetlb_fd_;       // file descriptor for hugetlb
  off_t hugetlb_base_;

  SysAllocator* fallback_;  // Default system allocator to fall back to.
};
static union {
  char buf[sizeof(HugetlbSysAllocator)];
  void *ptr;
} hugetlb_space;
#endif
