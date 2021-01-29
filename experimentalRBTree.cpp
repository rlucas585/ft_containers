#include <iostream>

// Basic type definitions
enum color_t { BLACK, RED };

struct Node {
	Node	*parent;
	Node	*left;
	Node	*right;
	enum color_t	color;
	int		key;
};

Node	*
