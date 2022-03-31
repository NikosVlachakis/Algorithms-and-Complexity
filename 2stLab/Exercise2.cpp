#include <vector>
#include <iostream>

using namespace std;

#define INTMAX 100000000000
int N, M, A;
unsigned long long  P;
vector<pair<int, unsigned long long> > suggestions[4][4];
vector<unsigned long long> optimal[4][4];
unsigned long long int kf_[1501][5001];

int kf(int merch, int obj)
{
    int I = suggestions[merch][obj].size();
    int J = N;
    for (int j = 1; j <= J; j++)
    {
        kf_[0][j] = INTMAX;
    }

    for (int i = 0; i <= I; i++)
    {
        kf_[i][0] = 0;
    }

    for (int i = 1; i <= I; i++)
    {
        int amount = suggestions[merch][obj][i - 1].first;
        int cost = suggestions[merch][obj][i - 1].second;
        for (int j = 1; j <= J; j++)
        {
            kf_[i][j] = min(kf_[i - 1][max(0, j - amount)] + cost, kf_[i - 1][j]);
        }
    }
    for (int j = 0; j <= J; j++)
    {
        optimal[merch][obj].push_back(kf_[I][j]);
    }
    return 1;
}

int main()
{
    cin>>N>>M;
    for (int i = 0; i < M; i++)
    {
        int merch, obj;
        cin>>merch;
        char equipment = getchar();
        if (equipment == 'A')
        {
            obj = 1;
        }

        else if (equipment == 'B')
        {
            obj = 2;
        }

        else
        {
            obj = 3;
        }

        cin>>A>>P;
        suggestions[merch][obj].push_back(make_pair(A, P));
    }
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            kf(i, j);
        }
    }

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            optimal[i][1][j] += optimal[i][2][j] + optimal[i][3][j];
        }
    }

    unsigned long long result = INTMAX;
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            int shortcut = N - i - j;
            if (shortcut >= 0)
                result = min(result, optimal[1][1][i] + optimal[2][1][j] + optimal[3][1][shortcut]);
            else
                result = min(result, optimal[1][1][i] + optimal[2][1][j]);
        }
    }

    if (result == INTMAX) cout<<-1<<endl;
    else cout<<result<<endl;
}