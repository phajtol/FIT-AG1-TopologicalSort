#include <iostream>

using namespace std;

/*
 * VECTOR IMPLEMENTATION
 * */
template <class T>
class vektor {
public:

    vektor(int size = 0, int capacity = 4)
    {
        ptr = new vektor_inside(size, capacity);
    }

    vektor(const vektor<T>& src)
    {
        addRef(src);
    }

    ~vektor()
    {
        delRef();
    }

    vektor<T>& operator= (const vektor<T>& other)
    {
        delRef();
        addRef(other);
        return *this;
    }

    void push_back(const T& item)
    {
        if (ptr->refCnt > 1) {
            deepCopy();
        }
        if (ptr->size >= ptr->capacity) {
            ptr->resize();
        }

        ptr->data[ptr->size++] = item;
    }

    bool empty() const
    {
        return ptr->size == 0;
    }

    T& operator[] (int i)
    {
        if (ptr->refCnt > 1) {
            deepCopy();
        }
        if (i < 0 || i >= ptr->size) {
            throw "out_of_bound";
        }

        return ptr->data[i];
    }

    const T& operator[] (int i) const
    {
        if (i < 0 || i >= ptr->size) {
            throw "out_of_bound";
        }

        return ptr->data[i];
    }

    int size() const
    {
        return ptr->size;
    }

    friend ostream& operator<<(ostream& os, const vektor<T>& vec)
    {
        os << "(" << vec.ptr->refCnt << ")(";

        for (int i = 0; i < vec.size(); ++i) {
            os << vec.ptr->data[i];
            if (i != vec.size() - 1) {
                os << ", ";
            }
        }

        return os << ")";
    }

private:

    void deepCopy()
    {
        vektor_inside* tmp = ptr;

        delRef();

        ptr = new vektor_inside(tmp->size, tmp->capacity);

        for (int i = 0; i < ptr->size; ++i) {
            ptr->data[i] = tmp->data[i];
        }
    }

    void addRef(const vektor& src)
    {
        ptr = src.ptr;
        ptr->refCnt++;
    }

    void delRef()
    {
        if(--ptr->refCnt == 0)
            delete ptr;
    }


    struct vektor_inside {
        vektor_inside(int size, int capacity) : size(size), capacity(capacity)
        {
            data = new T [capacity];
            refCnt = 1;
        }

        void resize()
        {
            capacity *= 2;
            T* newdata = new T [capacity];

            for (int i = 0; i < size; ++i) {
                newdata[i] = data[i];
            }
            
            delete [] data;
            data = newdata;
        }

        ~vektor_inside()
        {
            delete [] data;
        }

        T* data;
        int size;
        int capacity;
        int refCnt;
    };

    vektor_inside* ptr;

};


/*
 * LINKED LIST IMPLEMENTATION
 */

template <class T>
class linkedlist {
public:
    linkedlist()
    {
        head = tail = nullptr;
    }

    ~linkedlist()
    {
        linkedlist_node *del, *tmp = head;

        while (tmp) {
            del = tmp;
            tmp = tmp->next;
            delete del;
        }

        head = tail = nullptr;
    }

    void push_back(const T& item)
    {
        linkedlist_node* tmp = new linkedlist_node;
        tmp->value = item;

        if (!tail) {
            head = tail = tmp;
            tmp->next = tmp->prev = nullptr;
        } else {
            tail->next = tmp;
            tmp->prev = tail;
            tail = tmp;
        }
    }

    void push_front(const T& item)
    {
        linkedlist_node* tmp = new linkedlist_node;
        tmp->value = item;

        if (!head) {
            head = tail = tmp;
            tmp->next = tmp->prev = nullptr;
        } else {
            head->prev = tmp;
            tmp->next = head;
            head = tmp;
        }
    }

    void pop_front()
    {
        if (head == nullptr) {
            return;
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }

        linkedlist_node *del = head;
        head = head->next;
        head->prev = nullptr;
        
        delete del;
    }

    void pop_back()
    {
        if (tail == nullptr) {
            return;
        }
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
            return;
        }

        linkedlist_node *del = tail;
        tail = tail->prev;
        tail->next = nullptr;
        
        delete del;
    }

    const T& front() const
    {
        if (head) {
            return head->value;
        } else {
            throw "empty_list";
        }
    }

    const T& back() const
    {
        if (tail) {
            return tail->value;
        } else {
            throw "empty_list";
        }
    }

    bool empty() const {
        return !head;
    }

    friend ostream& operator<< (ostream& os, const linkedlist& list)
    {
        linkedlist_node* tmp = list.head;

        while (tmp) {
            os << tmp->value;
            if (tmp->next) {
                os << " <-> ";
            }
            tmp = tmp->next;
        }

        return os << "\n";
    }

    struct linkedlist_node {
        T value;
        linkedlist_node* next;
        linkedlist_node* prev;
    };

    linkedlist_node *head, *tail;

};





class Graph
{
    public:


    int vertices;
    vektor<int> *neighbors;
    vektor<int> *neighborsReverse;
    vektor<unsigned long> timeToComplete;
    vektor<unsigned long> startingTime;
    vektor<unsigned long> completeTime;


    Graph(int vertices)
    {
        this->vertices = vertices;
        neighbors = new vektor<int>[vertices];
        neighborsReverse = new vektor<int>[vertices];
        for(int i = 0; i < vertices; ++i) {
            startingTime.push_back(0);
        }
    }


    ~Graph()
    {
        delete[] neighbors;
        delete[] neighborsReverse;
    }


    void addEdge(int start, int end)
    {
        neighbors[start].push_back(end);
        neighborsReverse[end].push_back(start);
    }


    void topologicalSortRecursive(int v, bool visited[], linkedlist<int>& stack)
    {
        //current vertex has been visited
        visited[v] = true;

        //recursive call this function on all yet unvisited vertices adjacent to current vertex 
        int i;
        for (i = 0; i != neighbors[v].size(); ++i) {
            if (!visited[neighbors[v][i]]) {
                topologicalSortRecursive(neighbors[v][i], visited, stack);
            }
        }

        stack.push_front(v);
    }
    
    
    vektor<int> topologicalSort()
    {
        linkedlist<int> stack;

        //create array of bool, which represent which vertices have already been visited
        bool *visited = new bool[vertices];
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        
        //call topological sort on all vertices
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                topologicalSortRecursive(i, visited, stack);
            }
        }
        
        //create result vector
        vektor<int> result;
        
        //transfer stack content to result vector
        while (!stack.empty()) {
            result.push_back(stack.front());
            stack.pop_front();
        }
        
        delete[] visited;
        return result;
    }


    bool containsCycleRecursive(int v, bool visited[], bool* recursiveArray)
    {
        if (!visited[v]) {
            //mark current node as visited
            visited[v] = true;
            recursiveArray[v] = true;

            //do this for all vertices adjacent to this vertex
            for (int i = 0; i < neighbors[v].size(); ++i)
            {
                if ( !visited[neighbors[v][i]] && containsCycleRecursive(neighbors[v][i], visited, recursiveArray) ) {
                    return true;
                } else if (recursiveArray[neighbors[v][i]]) {
                    return true;
                }
            }

        }

        recursiveArray[v] = false;
        return false;
    }

    
    bool containsCycle()
    {
        //mark all vertices as not visited
        bool* visited = new bool[vertices];
        bool* recursiveArray = new bool[vertices];
        
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
            recursiveArray[i] = false;
        }

        //call recursive function on all vertices
        for (int i = 0; i < vertices; i++) {
            if (containsCycleRecursive(i, visited, recursiveArray)) {
                return true;
            }
        }

        return false;
    }
};


int main()
{
    //input loading
    unsigned long vertices,timeToComplete, numberOfEdges, edgeStart;
    

    //load number of vertices
    cin >> vertices;
    Graph g(vertices);

    
    //load time to complete for each vertex
    for (unsigned long i = 0; i < vertices; ++i) {
        cin >> timeToComplete;
        g.timeToComplete.push_back(timeToComplete);
    }

    
    //load edges
    for (unsigned long i = 0; i < vertices; ++i){
        cin >> numberOfEdges;
        for (unsigned long j = 0; j < numberOfEdges; ++j){
            cin >> edgeStart;
            g.addEdge(edgeStart,i);
        }
    }
    
    //if a graph is cyclic, problem has no solution
    if (g.containsCycle()) {
        cout << "No solution." << endl;
    } else {
        unsigned long max = 0;
        
        vektor<int> topsortresult = g.topologicalSort();
        
        
        //find starting time for each part as sum of starting time of its predecessors and time required to complete said predecessor
        for (int i = 0; i < topsortresult.size(); ++i) {
            if (!g.neighborsReverse[topsortresult[i]].empty()) {
                for (int j = 0; j < g.neighborsReverse[topsortresult[i]].size(); ++j) {
                    if ( (g.startingTime[g.neighborsReverse[topsortresult[i]][j]] + g.timeToComplete[g.neighborsReverse[topsortresult[i]][j]]) > g.startingTime[topsortresult[i]]) {
                        g.startingTime[topsortresult[i]] = g.startingTime[g.neighborsReverse[topsortresult[i]][j]] + g.timeToComplete[g.neighborsReverse[topsortresult[i]][j]];
                    }
                }
            }
        }
        
        //calculate when is every part done
        for (unsigned long i = 0; i < vertices; ++i) {
            g.completeTime.push_back(g.startingTime[i] + g.timeToComplete[i]);
        }
        
        //find max time when part is complete
        for (unsigned long i = 0; i < vertices; ++i) {
            if (g.completeTime[i] > max) {
                max = g.completeTime[i];
            }
        }
        
        //output max time
        cout << max << endl;
        
        //output time for each part
        for (unsigned long i = 0; i < vertices; ++i) {
            cout << g.startingTime[i];
            if (i != vertices - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}


