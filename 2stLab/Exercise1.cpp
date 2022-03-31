#include <iostream>

using namespace std;

struct Subsequence
{
    int length, lastIndex;
    Subsequence(int lengthArg, int lastIndexArg)
    {
        length = lengthArg;
        lastIndex = lastIndexArg;
    }
};

int N, K;

Subsequence *fourth;
Subsequence *fourthChanges;
Subsequence *back;
Subsequence *backChanges;

int FloorIndexBinary(int *v, int l, int r, int key)
{
    while (r - l > 1)
    {
        int m = l + (r - l) / 2;
        if (v[m] <= key)
            r = m;
        else
            l = m;
    }

    return r;
}

void Lds(int *v)
{
    int helperArray[N];
    int length = 1;

    helperArray[0] = v[N - 1];
    back[0] = Subsequence(1, v[N - 1]);
    backChanges[0] = Subsequence(1, v[N - 1]);

    for (int i = N - 2; i >= 0; i--)
    {
        if (v[i] > helperArray[0])
        {
            helperArray[0] = v[i];
            if (length > 1)
                back[N - 1 - i] = back[N - 1 - i - 1];
            else
                back[N - 1 - i] = Subsequence(1, v[i]);

            backChanges[N - 1 - i] = Subsequence(1, v[i]);
        }
        else if (v[i] < helperArray[length - 1])
        {
            helperArray[length++] = v[i];
            back[N - 1 - i] = Subsequence(length, v[i]);
            backChanges[N - 1 - i] = Subsequence(length, v[i]);
        }
        else
        {
            int index = FloorIndexBinary(helperArray, -1, length - 1, v[i]);
            helperArray[index] = v[i];
            if (index + 1 == length)
                back[N - 1 - i] = Subsequence(length, v[i]);
            else
                back[N - 1 - i] = back[N - 1 - i - 1];

            backChanges[N - 1 - i] = Subsequence(index + 1, v[i]);
        }
    }
}

int CeilIndexBinary(int *v, int l, int r, int key)
{
    while (r - l > 1)
    {
        int m = l + (r - l) / 2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}

void Lis(int *v)
{
    int helperArray[N];

    int length = 1;

    helperArray[0] = v[0];
    fourth[0] = Subsequence(1, v[0]);
    fourthChanges[0] = Subsequence(1, v[0]);

    for (int i = 1; i < N; i++)
    {
        if (v[i] < helperArray[0])
        {
            helperArray[0] = v[i];
            if (length > 1)
                fourth[i] = fourth[i - 1];
            else
                fourth[i] = Subsequence(1, v[i]);

            fourthChanges[i] = Subsequence(1, v[i]);
        }
        else if (v[i] > helperArray[length - 1])
        {
            helperArray[length++] = v[i];
            fourth[i] = Subsequence(length, v[i]);
            fourthChanges[i] = Subsequence(length, v[i]);
        }
        else
        {
            int index = CeilIndexBinary(helperArray, -1, length - 1, v[i]);
            helperArray[index] = v[i];

            if (index + 1 == length)
                fourth[i] = Subsequence(length, v[i]);
            else
                fourth[i] = fourth[i - 1];

            fourthChanges[i] = Subsequence(index + 1, v[i]);
        }
    }
}

int main()
{

    cin >> N >> K;
    int array[N], arrayPlusK[N];
    int x, result;
    for (int i = 0; i < N; i++)
    {
        cin >> x;
        array[i] = x;
        arrayPlusK[i] = x + K;
    }

    fourth = (Subsequence *)malloc(N * sizeof(Subsequence));
    fourthChanges = (Subsequence *)malloc(N * sizeof(Subsequence));
    back = (Subsequence *)malloc(N * sizeof(Subsequence));
    backChanges = (Subsequence *)malloc(N * sizeof(Subsequence));

    Lds(arrayPlusK);
    Lis(array);

    result = 0;
    for (int i = 0; i < N - 1; i++)
    {
        int maximum = 0;
        if (fourth[i].lastIndex < back[N - i - 2].lastIndex)
        {
            if (fourth[i].length + back[N - i - 2].length > maximum)
                maximum = fourth[i].length + back[N - i - 2].length;
        }
        if (fourth[i].lastIndex < backChanges[N - i - 2].lastIndex)
        {
            if (fourth[i].length + backChanges[N - i - 2].length > maximum)
                maximum = fourth[i].length + backChanges[N - i - 2].length;
        }
        if (fourthChanges[i].lastIndex < back[N - i - 2].lastIndex)
        {
            if (fourthChanges[i].length + back[N - i - 2].length > maximum)
                maximum = fourthChanges[i].length + back[N - i - 2].length;
        }
        if (fourthChanges[i].lastIndex < backChanges[N - i - 2].lastIndex)
        {
            if (fourthChanges[i].length + backChanges[N - i - 2].length > maximum)
                maximum = fourthChanges[i].length + backChanges[N - i - 2].length;
        }

        if (maximum > result)
            result = maximum;
    }

    cout << result << endl;
}
