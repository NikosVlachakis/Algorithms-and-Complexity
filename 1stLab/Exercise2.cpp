
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SumStruct
{
    int sum;
    int leftPointer;
    int rightPointer;
};

static bool customCompare(const SumStruct &x, const SumStruct &y)
{
    return (x.sum < y.sum);
}

int main()
{
    int N, K;
    cin >> N;
    cin >> K;
    int people[N];
    for (int i = 0; i < N; i++)
    {
        cin >> people[i];
    }

    std::vector<SumStruct> subsumarray;

    int i, j;
    int tempSum;
    for (i = 0; i < N; i++)
    {
        tempSum = people[i];
        for (j = i; j < N; j++)
        {
            if (i == j)
            {
                if (people[i] == K)
                {
                    cout << 1 << endl;
                    return 0;
                }
                else if (people[i] < K)
                {
                    SumStruct sstruct = {people[i], i, j};
                    subsumarray.push_back(sstruct);
                }
                else
                {
                    break;
                }
            }
            else
            {
                tempSum += people[j];
                if (tempSum <= K)
                {
                    SumStruct sstruct = {tempSum, i, j};
                    subsumarray.push_back(sstruct);
                }
                else
                {
                    break;
                }
            }
        }
    }
    sort(subsumarray.begin(), subsumarray.end(), customCompare);
    int l = 0, r = subsumarray.size() - 1, result = -1;
    int leftSetSum, rightSetSum, SetSum;


    while (l < r)
    {
        if (subsumarray[l].sum == K)
        {
            SetSum = subsumarray[l].rightPointer - subsumarray[l].leftPointer + 1;
            if (SetSum < result || result == -1)
            {
                result = SetSum;
            }
            l += 1;
        }
        else if (subsumarray[r].sum == K)
        {
            SetSum = subsumarray[r].rightPointer - subsumarray[r].leftPointer + 1;
            if (SetSum < result || result == -1)
            {
                result = SetSum;
            }
            r -= 1;
        }
        else if ((subsumarray[l].sum + subsumarray[r].sum) > K)
        {
            r -= 1;
        }
        else if ((subsumarray[l].sum + subsumarray[r].sum) < K)
        {
            l += 1;
        }
        else
        {
            if (subsumarray[l].leftPointer > subsumarray[r].rightPointer || subsumarray[l].rightPointer < subsumarray[r].leftPointer)
            {
                // den uparxei epikalucu
                leftSetSum = subsumarray[l].rightPointer - subsumarray[l].leftPointer + 1;
                rightSetSum = subsumarray[r].rightPointer - subsumarray[r].leftPointer + 1;
                if (leftSetSum + rightSetSum < result || result == -1)
                {
                    result = leftSetSum + rightSetSum;
                }
            }

            int r_backup = r, l_backup = l;

            while (subsumarray[l].sum + subsumarray[r - 1].sum == K && l < r - 1)
            {
                r--;
                // If conditions are met update value, else dont
                if (subsumarray[l].leftPointer > subsumarray[r].rightPointer || subsumarray[l].rightPointer < subsumarray[r].leftPointer)
                {
                    // den uparxei epikalucu
                    leftSetSum = subsumarray[l].rightPointer - subsumarray[l].leftPointer + 1;
                    rightSetSum = subsumarray[r].rightPointer - subsumarray[r].leftPointer + 1;
                    if (leftSetSum + rightSetSum < result || result == -1)
                    {
                        result = leftSetSum + rightSetSum;
                    }
                }
            }
            r = r_backup;

            while (subsumarray[l + 1].sum + subsumarray[r].sum == K && l + 1 < r)
            {
                l++;
                // If conditions are met update value, else dont
                if (subsumarray[l].leftPointer > subsumarray[r].rightPointer || subsumarray[l].rightPointer < subsumarray[r].leftPointer)
                {
                    // den uparxei epikalucu
                    leftSetSum = subsumarray[l].rightPointer - subsumarray[l].leftPointer + 1;
                    rightSetSum = subsumarray[r].rightPointer - subsumarray[r].leftPointer + 1;
                    if (leftSetSum + rightSetSum < result || result == -1)
                    {
                        result = leftSetSum + rightSetSum;
                    }
                }
            }
            l = l_backup;

            r--;
            l++;
        }
    }
    cout << result << endl;
    return 0;
}
