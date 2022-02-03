#define NUM_ALPHABET 26

typedef struct trieRecord
{
	int val;
	struct trieRecord **nodes;
} node;

typedef node* Nptr;

Nptr CreateTrieNode()
{
	Nptr p = new node;
	p->nodes = new node*[NUM_ALPHABET];
	
	for(int i = 0; i < NUM_ALPHABET; i++) p->nodes[i] = NULL;
	return p;
}
