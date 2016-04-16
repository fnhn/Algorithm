
#include <iostream>
using namespace std;

struct ArcNode {
	int id;
	ArcNode *next;

};

struct Node {
	int degree;
	ArcNode *arc;
};

void print_arc(Node *nodes, int len) {
	int i;
	ArcNode *arc;
	for(i = 0; i < len; i++) {
		cout<<"Node "<<i<<":";
		arc = nodes[i].arc;
		while(arc != NULL) {
			cout<<arc->id<<" ";
			arc = arc->next;
		}
		cout<<endl;
	}
}

void print_array(int *array, int len) {
	for(int i = 0; i < len; i++) {
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

void init(Node *nodes, int len) {
	int i;
	for(i = 0; i < len; i++) {
		nodes[i].degree = 0;
	}
}

void insert_arc(Node *nodes, int a, int b) {
	ArcNode *arc = new ArcNode;
	arc->id = b;

	if(nodes[a].arc == NULL) {
		nodes[a].arc = arc;
		arc->next = NULL;
	}
	else {
		arc->next = nodes[a].arc;
		nodes[a].arc = arc;
	}

	nodes[a].degree++;

}

void create_table(Node *nodes) {
	int a, b;
	

	while(true) {
		cin>>a>>b;
		if(a == -1 && b == -1) {
			break;
		}

		insert_arc(nodes, a, b);
		insert_arc(nodes, b, a);
		
	}
}

void findKCore(Node *nodes, int len) {
	int *bin = new int[len - 1];
	int *vert = new int[len];
	int *core = new int[len];
	int *pos = new int[len];
	int i;
	int num;
	int degree;
	int start = 0;
	ArcNode *tmp;

	int v;
	int u;
	int w;
	int pu, pw;

	for(i = 0; i < len - 1; i++) {
		bin[i] = 0;
	}

	for(i = 0; i < len; i++) {
		bin[nodes[i].degree]++;
	}

	for(i = 0; i < len - 1; i++) {
		num = bin[i];
		bin[i] = start;
		start = start + num;
	}

	for(i = 0; i < len; i++) {
		degree = nodes[i].degree;
		pos[i] = bin[degree];
		vert[pos[i]] = i;
		bin[degree]++;
	}

	for(i = len - 1; i > 0; i--) {
		bin[i] = bin[i - 1];
	}


	i = 0;
	while(i < len) {
		int v = vert[i];
		core[v] = nodes[v].degree;
		tmp = nodes[v].arc;
		while(tmp != NULL) {
			u = tmp->id;
			if(nodes[u].degree > nodes[v].degree) {
				pw = bin[nodes[u].degree];
				pu = pos[u];
				w = vert[pw];

				if(u != w) {
					pos[u] = pw;
					pos[w] = pu;
					vert[pw] = u;
					vert[pu] = w;
				}

				bin[nodes[u].degree]++;
				nodes[u].degree--;

			}

			tmp = tmp->next;
		}
		i++;

	}

	cout<<"core array:";
	print_array(core, len);

}



int main() {
	int n;

	cin>>n;
	Node *nodes = new Node[n];
	create_table(nodes);
	findKCore(nodes, n);
	//print_arc(nodes, n);


	return 0;
}