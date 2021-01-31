#include<cstdio>
#include<string>

#define CH                    27
#define STARTCHAR          'a'
#define SPECIALCHAR     ('z'+1)
#define ERROR               -1
#define TYPE1               1
#define TYPE2               2
#define LEAF               1
#define NOTLEAF               2

struct node {
     int start, end;
     node * next[CH],* link,* father;
     int flag;
     int length;
};
void print(node *x){
	if (x==NULL)return;
	printf("%d %d %d %d\n",x->start,x->end,x->length,x->flag);
	for (int i=0;i<CH;++i)print(x->next[i]);
}

char str[100005]="aabcaaa", buf[100005];
node head;
node*P, *G, *U, *V, *q;
int W[3], len, len2;

void CreateNode(node * & Node) {
    int i;
    Node = (node * ) malloc(sizeof(node));
    Node -> start = Node -> end = Node -> length = ERROR;
    for (i = 0; i < CH; i++) Node -> next[i] = NULL;
    Node -> link = Node -> father = NULL;
    Node -> flag = LEAF;
}

void Init(node & h, char s[]) {
    int i;
    h.start = h.end = ERROR;
    for (i = 0; i < CH; i++) h.next[i] = NULL;
    h.link = & h;
    h.father = NULL;
    h.flag = LEAF;
    h.length = 0;
     
    len = strlen(s);
    s[len] = SPECIALCHAR;
    s[len + 1] = '\0';
    len++;
}

int FindV(char s[]) {
    int old;
    node * t, * newt;
    t = U -> next[s[W[0]] - STARTCHAR];
     
    old = 0;
    while (W[2] > (t -> end) - (t -> start) + 1 + old) {
        old += (t -> end - t -> start + 1);
        t = t -> next[s[W[0] + old] - STARTCHAR];
    }
    if (W[2] == (t -> end) - (t -> start) + 1 + old) {
        V = t;
        P -> link = V;
        return TYPE1;
    } else {
        CreateNode(newt);
        newt -> start = t -> start;
        newt -> end = t -> start + W[2] - old - 1;
        newt -> father = t -> father;
        newt ->
               length = newt -> father -> length + newt -> end - newt ->
               start + 1;
        t -> father -> next[s[t -> start] - STARTCHAR] = newt;
        t -> start = newt -> end + 1;
        newt -> next[s[t -> start] - STARTCHAR] = t;
        t -> father = newt;
        V = newt;
        P -> link = V;
        return TYPE2;
    }
}

int Insert(node * Node, int start, char s[]) {
    int i, posbegin, posend;
    node * t;
    if (Node -> next[s[start] - STARTCHAR] == NULL) {
        CreateNode(Node -> next[s[start] - STARTCHAR]);
        Node -> next[s[start] - STARTCHAR] -> start = start;
        Node -> next[s[start] - STARTCHAR] -> end = len - 1;
        Node -> next[s[start] - STARTCHAR] -> father = Node;
        Node -> next[s[start] - STARTCHAR] ->
               length = Node -> length + len - start;
        Node -> flag = NOTLEAF;
        P = Node;
        return TYPE1;
    } else {
        posbegin = Node -> next[s[start] - STARTCHAR] -> start;
        posend = Node -> next[s[start] - STARTCHAR] -> end;
        for (i = posbegin; i <= posend; i++) {
            if (s[i] != s[start + i - posbegin]) break;
        }
        if (i == posend + 1) {
            return Insert(Node -> next[s[start] - STARTCHAR], start + i - posbegin, s);
        } else {
            CreateNode(t);
            t -> start = posbegin;
            t -> end = i - 1;
            t -> flag = NOTLEAF;
            Node -> next[s[start] - STARTCHAR] -> start = i;
            t -> next[s[i] - STARTCHAR] = Node -> next[s[start] - STARTCHAR];
            t -> next[s[i] - STARTCHAR] -> father = t;
            Node -> next[s[start] - STARTCHAR] = t;
            t -> father = Node;
            t -> length = Node -> length + t -> end - t -> start + 1;
            Insert(t, start + i - posbegin, s);
            G = Node;
            P = t;
            return TYPE2;
        }
    }
}

int Select(int start, char s[], int type) {
    int result1, result2, result;
    if (type == TYPE1) {
        U = P -> link;
        result = Insert(U, start + U -> length, s);
    } else {
        U = G -> link;
        if (G -> link == G) {
            W[0] = P -> start + 1;
            W[1] = P -> end;
            W[2] = P -> end - P -> start;
        } else {
            W[0] = P -> start;
            W[1] = P -> end;
            W[2] = P -> end - P -> start + 1;
        }
        if (W[2] == 0) {
            V = G;
            P -> link = V;
            result = Insert(V, start, s);
        } else {
            result1 = FindV(s);
            result2 = Insert(V, start + V -> length, s);
            if (result1 == TYPE2) {
                G = P -> father;
                result = result1;
            } else result = result2;
        }
    }
    return result;
}

void Buildnode(node & h, char s[]) {
    int i;
    int type;

    CreateNode(h.next[s[0] - STARTCHAR]);
    h.next[s[0] - STARTCHAR] -> start = 0;
    h.next[s[0] - STARTCHAR] -> end = len - 1;
    h.next[s[0] - STARTCHAR] -> father = & h;
    h.next[s[0] - STARTCHAR] -> length = h.length + h.next[s[0] - STARTCHAR] -> end - h.next[s[0] - STARTCHAR] -> start + 1;
    h.flag = NOTLEAF;
    type = TYPE1;
    P = & h;
     
    for (i = 1; i < len; i++) type = Select(i, s, type);
}

int FindString(int start, char s[]) {
    int result;
    int i;
    int temp;
    node * x;
    x = P -> next[s[start] - STARTCHAR];
    result = P -> length;
    if (x == NULL) {
        P = P -> link;
        return result;
    }
    temp = 0;
    for (i = start; i < len2; i++) {
        if (x -> start + i - start - temp > x -> end) {
            temp = i - start;
            P = x;
            x = x -> next[s[start + temp] - STARTCHAR];
            if (x == NULL) break;
        }
        if (s[i] != str[x -> start + i - start - temp]) break;
        result++;
    }
    P = P -> link;
    return result;
}

int Search(node & h, char s[]) {
    int result;
    int i;
    int temp;
    len2 = strlen(s);
    result = 0;
    P = & head;
    for (i = 0; i < len2; i++) {
        temp = FindString(i + P -> length, s);
        if (result < temp) result = temp;
        if (result >= len2 - i) break;
    }
    return result;
}

int main(){
	//freopen("1.in","r",stdin);
    int result;
    //scanf("%s", str);
	Init(head, str);
    Buildnode(head, str);
    printf("start\n");print(&head);printf("end\n");
    system("pause");for (;;);
}
