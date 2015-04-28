/////////////////////////////////////////////////////////

// Chapter 4 - Sorting and Searching

/////////////////////////////////////////////////////////

// Priority queue structure
typedef struct 
{
	item_type q[PQ_SIZE+1]; // body of queue
	int n; // number of queue elements
};

// Find parent index
pq_parent(int n)
{
	if (n = 1) return -1;
	else return ((int) n/2); // return the parent node (implictly floor(n/2))
}

// Find youngest child (leftmost element in the level below it)
pq_young_child(int n)
{
	return (2*n); 
}

// Insert into a priority queue, omits overflow checking
pq_insert(priority_queue *q, item_type x)
{
	q->n = (q->n)+1 // increase the number of queue elements
	q->q[q->n] = x; // insert the new item into the end of the array
	bubble_up(q, q->n); // bubble up into the appropriate spot in hierarchy
}

// Bubble up in a min heap
bubble_up(priority_queue *q, int p)
{
	if (pq_parent(p) == -1) return; // at the root of the heap, no parent
	if (q->q[pq_parent(p)] > q->q[p]) // if parent of the current element is greater than current element
	{
		pq_swap(q,p,pq_parent(p)); // swap the element with the parent
		bubble_up(q, pq_parent(p)); // recursively bubble up again, this time with the parent of the current element
	}
}

// Make the heap
make_heap(priority_queue *q, item_type s[], int n)
{
	q->n = 0; // set the current number of elements in the heap to be 0
	for(i = 0; i < n; i++) // for all the elements in the array
		pq_insert(q,s[i]); // insert the elements into the heap
}
//-------------------------------------------------------------
// Extract the minimum in the heap
item_type extract_min(priority_queue *q)
{
	int min = -1; // temporary minimum value
	if(q->n <= 0) return; // priority queue empty
	else
	{
		min = q->q[1]; // minimum is the root
		q->q[1] = q->[q->n]; // root is now replaced with the last element in the heap
		q->n = q->n - 1; // number of elements in queue - 1
		bubble_down(q,1);
	}
}

bubble_down(priority_queue *q, int p)
{
	int c; // child index
	int i; // counter
	int min_index // index of smallest child
	c = pq_young_child(p);
	min_index = p;
	for(i = 0; i <= 1; i++) // iterates only twice
	{
		if ((c+i) <= q->n) // if child index + current counter <= number of elements in queue
			if(q->q[min_index] > q->q[c+i]) // if current node is greater than any of the children 
				min_index = c+i; // set min_index to index of smaller child
	}
	if(min_index != p) // if min_index is not p
	{
		pq_swap(q,p,min_index); // swap current node and smallest child
		bubble_down(q,min_index); // smallest child is now current node, bubble down the smallest child if necessary recursively
	}
}

// Actually Sorting

heapsort(item_type s[], int n)
{
	int i; // counter
	priority_queue q; // heap
	make_heap(&q, s, n); // make the heap with the array
	for(i = 0; i < n; i++)
	{
		s[i] = extract_min(&q); // extract minimum from heap and put it into the array, eventually sorting it
	}
}

/////////////////////////////////////////////////////////

// low is index of smallest element, high is index of largest element
mergesort(item_type s[], int low, int high)
{
	int middle // index of middle element
	if(low < high)
	{
		middle = (low+high)/2;
		mergesort(s,low,middle);
		mergesort(s,middle+1,high);
		merge(s, low, middle, high);
	}
}

// merging
merge(item_type s[], int low, int middle, int high)
{
	int i; // counter
	queue buffer1, buffer2; // queues to hold elements from merging (FIFO)
	for(i=low; i<= middle; i++) enqueue(&buffer1,s[i]); // for the first half of the array, put each element into queue1
	for(i=middle+1; i<= high; i++) enqueue(&buffer2,s[i]); // for the second half of the array, put each element into queue2

	i = low; // set i back to lowest index
	while(!(empty_queue(&buffer1) || empty_queue(&buffer2))) // while queue 1 is not empty and queue 2 is not empty
	{
		if(headq(&buffer1) <= headq(&buffer2)) s[i++] = dequeue(&buffer1); // if head of queue1 < head of queue 2, dequeue head of queue1
		else s[i++] = dequeue(&buffer2); // else dequeue head of queue2
	}

	// dequeue remaining items in queue (in the case of one queue being larger than the other)
	while(!empty_queue(&buffer1)) s[i++] = dequeue(&buffer1);
	while(!empty_queue(&buffer2)) s[i++] = dequeue(&buffer2);
}

/////////////////////////////////////////////////////////

