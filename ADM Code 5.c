/////////////////////////////////////////////////////////

// Chapter 5 - Graph Traversal

/////////////////////////////////////////////////////////

typedef struct 
{
	int y; // adjacency info, AN INT IS A NODE'S IDENTIFIER
	int weight; // edge weight, if any
	struct edgenode *next; // next edge in the list
} edgenode;

typedef struct 
{
	edgenode *edges[MAXV]; // adjacency info, AN INT IS A NODE'S IDENTIFIER
	int degree[MAXV]; // outdegree of each vertex
	int nvertices; // number of vertices in graph
	int nedges; //number of edges in graph
	bool directed; // is the graph directed?
} graph;

// Initializing the graph
initialize_graph(graph*g, bool directed);
{
	int i;
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for(i=1; i<=MAXV; i++) g->degrees[i] = 0; // for each node in the graph, set the degree to 0
	for(i=1; i<=MAXV; i++) g->edges[i] = NULL; // for each node in the graph, set them to have no adjacent nodes
}

// Insert edge into graph where y is in x's adjacency list
insert_edge(graph*g, int x, int y, bool directed)
{
	edgenode *p; // temporary pointer
	p = malloc(sizeof(edgenode)); // allocate edgenode
	p->weight = NULL; // no weight for this vertex
	p->y = y; // current vertex is y
	p->next = g->edges[x] // link current vertex's next pointer to head of adjacency list
	g->edges[x] = p; // head of adjacency list is now current vertex
	g->degree[x]++; // increase the degree of x
	if(directed == false) insert_edge(g,y,x,TRUE); // if undirected edge, insert x into y's adjacency graph to represent an undirected edge
	else g->nedges++; // else, increase number of edges in g by 1
}

// Breadth first search
bfs(graph *g, int start)
{
	queue q; // queue of vertices to visit
	int v; // current vertex
	int y; // successor vertex
	edgenode *p; // temporary pointer
	init_queue(&q) // initialize queue
	enqueue(&q, start); // put starting vertex at head of the queue
	discovered[start] = TRUE; // set starting vertex to be discovered
	while(empty_queue(&q) == FALSE) // while queue is not empty
	{
		v = dequeue(&q); // take the oldest element in the queue and assign it to v (current vertex)
		processed[v] = TRUE; // set vertex v's state to processed
		p = g->edges[v]; // p is now the first vertex in v's adjacency list
		while(p!=NULL) // this loop will iterate through all vertexes adjacent to current vertex v
		{
			y = p->y;
			if((processed[y]==FALSE) || g->directed) // PROCESSED check, usually not needed
				process_edge(v,y);
			if(discovered[y] = FALSE)
			{
				enqueue(&q, y); // enqueue vertex y (a vertex in v's adjacency list)
				discovered[y] = TRUE; // set discovered to true
				parent[y] = v; // v is y's parent
			}
			p=p->next; // advance v to v's next adjacent vertex
		}		
	}
}

// Depth first search, implemented recursively
dfs(graph *g, int v)
{
	edgenode *p; // temporary pointer
	int y; // successor vertex
	if(finished) return; // base case of recursion to allow for termination
	discvered[v] = TRUE; // this iteration of recursion will set the current vertex to discovered
	// time = time + 1;
	// entry_time[v] = time;
	// process_vertex_early(v);
	p = g->edges[v]; // p is now the first vertex in v's adjacency list
	while(p!=NULL)
	{
		y = p->y;
		if(discovered[y] == FALSE) // if vertex y is not discovered
		{
			parent[y] = v; // vertex v is vertex y's parent
			process_edge(v,y); // process if desired
			dfs(g,y); // perform depth first search recursively on vertex v's sucessors (vertex y)
		}
		else if((!processed[y] && (parent[v] !=y)) || (g->directed)) // (if y is not processed and y is not v's parent) or (graph is directed)
			process_edge(v,y); // process if desired
		if(finished) return; // return if finish processing descendents
		p=p->next // advance v to v's next adjacent vertex
	}
	// process_vertex_late(v);
	// time = time + 1; 
	// exit_time[v] = time; 
}

// process_edge for dfs to find back edge (edges whose other endpoint is an ancestor of those being expanded)
process_edge(int x, int y)
{
	if (discovered[y] && parent[x] != y)) // if y is discovered and y is not a parent of x
		finished = true; // exit dfs on this vertex
}

