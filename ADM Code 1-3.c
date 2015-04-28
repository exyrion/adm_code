/////////////////////////////////////////////////////////

// Chapter 1 - Introduction to Algorithm Design

/////////////////////////////////////////////////////////

// Insertion Sort
for(i = 1; i < n; i++) // iterate from 1 to n
{
	j = i;
	while ((j > 0) && (s[j] < s[j-1])) // iterate from i to the smallest element before i
	{
		swap(s[j], s[j-1]); // swapping until s[j] > s[j-1]
		j = j-1
	}
}
/////////////////////////////////////////////////////////

// Chapter 2 - Algorithm Analysis

/////////////////////////////////////////////////////////

// Selection Sort
int min;
for(i=0; i<n; i++) // iterate from 0 to n
{
	min = i; // current index is minimum index
	for(j=i+1; j<n; j++) // iterate from i+1 to n
	{
		if(s[j] < s[min]) // find the new minimum
		{
			min=j;
		}
		swap(s[i], s[min]); // swap i with new min, the smallest value is now at head of array
	}
}

/////////////////////////////////////////////////////////

// Find a substring in a string
int findmatch(char *p, char *t) // O(m^2)
{
	int i,j;
	int m,n;
	m = strlen(p);
	n = strlen(p);
	for(i=0; i <= (n-m); i++) // iterate from 0 to n-m (big string - substring)
	{
		j=0; // length counter
		while ((j<m) && (t[i+j]==p[j])) // while j < length of substring && the letters match at each index
		{
			j++; // increase the length counter 
		}
		if(j==m) // if the length counter and length of the substring match, return the index of first letter
			return i;
	}
	return -1; // else return -1
}

/////////////////////////////////////////////////////////

// Chapter 3 - Data Structures

/////////////////////////////////////////////////////////

// Searching through a linked list
list *search_list(list *l, item_type x)
{
	if (l == NULL) return NULL // if list is empty, return null

	if (l->item == x) return l; // if item is found, return the item
	
	else return(search_list(l->next, x)); // else, iterate to next item
}

/////////////////////////////////////////////////////////

// Inserting into head of a list
void insert_list(list **l, item_type x)
{
	list *p; // temp pointer

	p = malloc(sizeof(list)); // allocate memory for a new node
	p->item = x; // item of the node is x
	p->next = *l; // next of the node is head of the list
	*l = p; // head pointer now points to p
}

/////////////////////////////////////////////////////////

// Find predecessor of an item in a tree
list *predecessor_list(list *l, item_type x)
{
	if ( (l==NULL) || l->next==NULL) ) return NULL // if head of list is NULL, return null
	if ( (l->next)->item == x) return (l); // if node's next node's item is x, return the current node
	else return (predecessor_list(l->next, x)) // else iterate to next node, loop
}

// Delete item in a tree
delete_list(list **l, item_type x)
{
	list *p; // item pointer
	list *pred; // predecessor pointer
	list *search_list, *predecessor_list();
	p = search_list(*l, x) // search for x in the list, assign to p

	if(p != NULL)
	{
		pred = predcessor_list(*l, x); // find the predecessor to the node that contains x
		if(pred == NULL) *l = p->next; // if a predecessor does not exist, head pointer now points to the p->next
		else pred->next = p->next; // else, predecessor's next is now p->next
		free(p); // free memory
	}
}

/////////////////////////////////////////////////////////

// BST Search, takes O(h) time where h is the height of the tree
tree *search_tree(tree *l, item_type x)
{
	if (l==NULL) return NULL; // if tree is empty, return NULL
	if (l->item == x) return (l) // if current node contains item x, return l
	if (x < l->item) return (search_tree(l->left, x)); // if x < current node, go left
	else return (search_tree(l->right, x)); // else go right
}

// Find min/max item in tree
tree *find_min/max(tree *t)
{
	node *min;
	if(t==NULL) return (NULL);
	min = t; // minimum is root
	while (min->left != NULL) 
		min = min->left; // traverse all the way to the left of tree
	return (min);
}

// In-order traversal, pre-order will have process_item first, post will have it last
void traverse_tree( tree *l)
{
	if (l != NULL)
	{
		traverse_tree(l->left);
		process_item(l->item);
		traverse_tree(l->right);
	}
}

// Insertion in a tree, l is current node, x is the item, parent is the parent node containing l
insert_tree(tree **l, item_type x, tree *parent)
{
	tree *p; // temporary pointer
	if(*l == NULL) // if the current node is empty
	{
		p = malloc(sizeof(tree));
		p->item = x; // node is x
		p->left = p->right = NULL // children is NULL
		p->parent = parent; // parent of node is parent
		*l = p; // ???
		return;
	}
	if(x < (*l)->item)
		insert_tree(&((*l)->left), x, *l) // go left
	else
		insert_tree(&((*l)->right), x, *l) // go right
}

/////////////////////////////////////////////////////////
