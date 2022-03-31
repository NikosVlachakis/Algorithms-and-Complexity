
#include <iostream>
#include <algorithm>

using namespace std;

int *parent;
int *size;

int find_set(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void make_set(int v)
{
    parent[v] = v;
    size[v] = 1;
}

void union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}

struct portals
{
    int first;
    int last;
    int width;
};

bool comparePortalsWidth(portals s1, portals s2)
{
    return (s1.width < s2.width);
}

int main()
{
    int N, M;
    cin >> N;
    cin >> M;
    int universe[N];
    portals *portalsArray;
    portalsArray = (portals *)malloc(M * sizeof(portals));
    parent = (int *)malloc(N * sizeof(int));
    size = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
    {
        cin >> universe[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> portalsArray[i].first;
        cin >> portalsArray[i].last;
        cin >> portalsArray[i].width;
    }

    for (int i = 0; i < N; i++)
    {
        universe[i] -= 1;
    }
    for (int i = 0; i < M; i++)
    {
        portalsArray[i].first -= 1;
        portalsArray[i].last -= 1;
    }

    sort(portalsArray, portalsArray + M, comparePortalsWidth);

    for (int i = 0; i < N; i++)
    {
        make_set(i);
    }

    int low = 0, high = M-1;

    while (low < high)
    {
        int mid = low + (high - low + 1) / 2;

        for (int l = mid; l <= M-1; l++)
        {
            union_sets(portalsArray[l].first, portalsArray[l].last);
        }

        bool flag = true;
        for (int j = 0; j < N; j++)
        {
            if (universe[j] != j)
            {
                if (find_set(universe[j]) != find_set(j))
                {
                    flag = false;
                    break;
                }
            }
        }

        if (flag == true)
        {
            low = mid;
        }
        else
        {
            high = mid-1;
        }

        for (int i = 0; i < N; i++)
        {
            make_set(i);
        }
    }
    cout << portalsArray[low].width << endl;

    return 0;
}