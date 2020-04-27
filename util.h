#define wmalloc(p)\ do { if (!malloc(p)) { print("wmalloc: OOM\n"); } }
