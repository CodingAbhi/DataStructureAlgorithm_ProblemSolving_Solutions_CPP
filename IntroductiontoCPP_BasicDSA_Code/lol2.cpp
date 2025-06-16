#include <iostream>
#include <cstdlib>

int *processQueries(int N, int Q, int A[], int Queries[][2], int *out_n)
{
    int *out = static_cast<int *>(malloc(Q * sizeof(int)));
    *out_n = 0;

    for (int i = 0; i < Q; i++)
    {
        int indx = Queries[i][0];
        int val = Queries[i][1];
        int I = indx;

        if (indx <= N)
        {
            int OR = A[indx - 1];
            while (I <= N)
            {
                OR = OR | A[I - 1];
                if (OR >= val)
                {
                    break;
                }
                I++;
            }
        }

        if (I > N)
        {
            I = -1;
        }

        out[i] = I;
        (*out_n)++;
    }

    return out;
}

int main()
{
    // Example usage:
    int N = 5;
    int Q = 3;
    int A[] = {1, 2, 3, 4, 5};
    int Queries[][2] = {{2, 3}, {4, 8}, {1, 7}};
    int out_n;

    int *result = processQueries(N, Q, A, Queries, &out_n);

    // Display the results
    std::cout << "Output Array: ";
    for (int i = 0; i < Q; i++)
    {
        std::cout << result[i] << " ";
    }
    std::cout << "\nNumber of elements in output array: " << out_n << std::endl;

    // Don't forget to free the allocated memory
    free(result);

    return 0;
}
