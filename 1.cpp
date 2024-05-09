#include <bits/stdc++.h>
using namespace std;
class graph
{
    int vertices;
    int n;
    unordered_map<int, vector<int>> adjlist;
    unordered_map<string, int> city_map;

public:
    graph()
    {
        vertices = 0;
    }
    void addedge(int i, int j)
    {
        adjlist[i].push_back(j);
        adjlist[j].push_back(i);
    }

    /*****util functions*/
    void input()
    {
        cout << "Enter a number of vertices :- ";
        cin >> n;
        vertices = n;
        cout << "Input" << endl;
        for (int i = 0; i < vertices; i++)
        {
            string city;
            cout << "Enter a city name :- ";
            cin >> city;
            city_map[city] = i;
        }
        cout << "Enter number of edges :- ";
        int edges;
        cin >> edges;
        for (int i = 0; i < edges; i++)
        {
            string city1, city2;
            cout << "Enter city1 and city2 :- ";
            cin >> city1 >> city2;
            addedge(city_map[city1], city_map[city2]);
        }
    }

    string getCityName(int val)
    {
        for (auto i : city_map)
        {
            if (i.second == val)
            {
                return i.first;
            }
        }
        return "";
    }
    /*********************Recursive BFS*********************************************/
    void bfs_recursive(string cityname)
    {
        int st = city_map[cityname];
        vector<int> vis(vertices, 0);
        vector<vector<string>> bfs;
        queue<int> q;
        vector<string> level;
        q.push(st);
        q.push(-1);
        vis[st] = 1;
        solve(vis, bfs, q, level);
        cout << "BFS Recursive:-";
        for (auto level : bfs)
        {
            cout << "Level:- ";
            for (auto node : level)
            {
                cout << node << " ";
            }
            cout << endl;
        }

        cout << (bfs.size());
    }

    void solve(vector<int> &vis, vector<vector<string>> &bfs, queue<int> &q, vector<string> &level)
    {
        if (q.empty())
        {
            return;
        }
        int t = q.front();
        q.pop();
        if (t == -1)
        {
            bfs.push_back(level);
            level.clear();
            if (!q.empty())
            {
                q.push(-1);
            }
        }
        else
        {
            vis[t] = 1;
            level.push_back(getCityName(t));
            for (auto i : adjlist[t])
            {
                if (vis[i] == 0)
                {
                    vis[i] = 1;
                    q.push(i);
                }
            }
        }
        solve(vis, bfs, q, level); // Move the recursive call here
    }
    /*********************Iterative BFS*********************************************/
    void bfs(string city_name)
    {
        cout << "BFS:- " << endl;
        int st = city_map[city_name];
        vector<int> vis(vertices, 0);
        vector<vector<int>> bfs;
        queue<int> q;
        vector<int> level;

        q.push(st);
        q.push(-1);
        vis[st] = 1;
        level.push_back(st);

        while (!q.empty())
        {
            int t = q.front();
            q.pop();
            if (t == -1)
            {

                bfs.push_back(level);
                level.clear();
                if (!q.empty())
                    q.push(-1);
            }
            else
            {
                level.push_back(t);
                for (auto j : adjlist[t])
                {
                    if (!vis[j])
                    {
                        vis[j] = 1;
                        q.push(j);
                    }
                }
            }
        }

        for (auto level : bfs)
        {
            cout << "Level wise:- ";

            for (auto i : level)
                cout << getCityName(i) << " ";
        }

        cout << endl;
    }

    /*********************Recursive DFS*********************************************/
    void dfs_recursive(string cityname)
    {
        int source = city_map[cityname];
        vector<int> vis(vertices, 0);
        vector<int> dfsVector;
        vis[source] = 1;
        solveDFS(source, dfsVector, vis);
        cout << "DFS Recursive:-" << endl;
        for (auto i : dfsVector)
        {
            cout << getCityName(i) << " ";
        }
        cout << endl;
    }

    void solveDFS(int v, vector<int> &ans, vector<int> &vis)
    {
        vis[v] = 1;
        ans.push_back(v);
        for (auto i : adjlist[v])
        {
            if (!vis[i])
            {
                solveDFS(i, ans, vis);
            }
        }
    }
    /*********************Iterative DFS*********************************************/
    void dfs(string city_name)
    {

        int st = city_map[city_name];
        vector<int> vis(vertices, 0);
        vector<int> dfs;
        stack<int> s;
        vector<int> level;
        s.push(st);
        vis[st] = 1;
        level.push_back(st);
        int levelcnt = 0;

        while (!s.empty())
        {
            int t = s.top();
            s.pop();
            dfs.push_back(t);
            for (auto j : adjlist[t])
            {
                if (!vis[j])
                {
                    vis[j] = 1;
                    s.push(j);
                }
            }
        }
        cout << "DFS:- " << endl;
        for (auto i : dfs)
        {
            cout << getCityName(i) << " ";
        }

        cout << endl;
    }
};
int main()
{
    graph g;

    int choice;

    char c = 'y';

    while (c == 'y')
    {
        cout << "========MENU==========\n1.Create\n2.BFS\n3.DFS\n4.Exit." << endl;
        cout << "Enter a choice :- ";
        cin >> choice;

        if (choice == 1)
        {
            g.input();
        }

        else if (choice == 2)
        {

            string st;
            cout << "Enter a start node :- ";
            cin >> st;
            g.bfs(st);
            g.bfs_recursive(st);
        }

        else if (choice == 3)
        {
            string st;
            cout << "Enter a start node :- ";
            cin >> st;
            g.dfs(st);
            g.dfs_recursive(st);
        }

        else
            break;

        cout << "Do you want to continue :- ";
        cin >> c;
    }

    return 0;
}