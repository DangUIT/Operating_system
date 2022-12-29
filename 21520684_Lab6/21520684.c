#include <stdio.h>
int pre[100];
int numOfPageFault = 1;
int checkInPre(int value, int num_frames)
{
    for (int i = 0; i < num_frames; i++)
        if (value == pre[i])
            return i;
    return -1;
}
int predict_farest(int referenced[], int size_string, int num_frames, int pos_current)
{
    int max1 = 0;
    int max2 = 0;
    int frame = 0;
    int flag;
    for (int i = 0; i < num_frames; i++)
    {
        flag = 0;
        for (int j = pos_current + 1; j < size_string; j++)
        {
            if (referenced[j] == pre[i])
            {
                max1 = j;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            frame = i;
            break;
        }
        if (max1 > max2)
        {
            max2 = max1;
            frame = i;
        }
    }
    return frame;
}
int least_recently(int referenced[], int size_string, int num_frames, int pos_current)
{
    int min1 = 0;
    int min2 = pos_current;
    int frame = 0;
    for (int i = 0; i < num_frames; i++)
    {
        for (int j = pos_current; j >= 0; j--)
        {
            if (referenced[j] == pre[i])
            {
                min1 = j;
                break;
            }
        }
        if (min1 < min2)
        {
            min2 = min1;
            frame = i;
        }
    }
    return frame;
}
void print(int referenced[], int page[][100], int page_fault[], int size_string, int num_frames)
{
    for (int i = 0; i < size_string; i++)
    {
        printf("%d ", referenced[i]);
    }
    printf("\n");
    for (int i = 0; i < num_frames; i++)
    {
        for (int j = 0; j < size_string; j++)
        {
            if (page[i][j] == -1)
                printf("  ");
            else
                printf("%d ", page[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < size_string; i++)
    {
        if (page_fault[i] == 1)
            printf("*");
        else
            printf(" ");
        printf(" ");
    }
    printf("\nNumber of Page Fault: %d", numOfPageFault);
    numOfPageFault = 1;
}
void FIFO(int referenced[], int size_string, int num_frames)
{
    int page[20][100];
    int page_fault[100];
    int current_page = 0;
    page_fault[0] = 1;
    page[0][0] = referenced[0];
    for (int i = 1; i < num_frames; i++)
        page[i][0] = -1;
    for (int i = 1; i < size_string; i++)
    {
        for (int j = 0; j < num_frames; j++)
        {
            page[j][i] = page[j][i - 1];
            pre[j] = page[j][i - 1];
        }
        if (checkInPre(referenced[i], num_frames) != -1)
            page_fault[i] = -1;
        else
        {
            current_page++;
            if (current_page == num_frames)
                current_page = 0;
            page[current_page][i] = referenced[i];
            page_fault[i] = 1;
            numOfPageFault++;
        }
    }

    print(referenced, page, page_fault, size_string, num_frames);
}
void OPT(int referenced[], int size_string, int num_frames)
{
    int page[20][100];
    int page_fault[100];
    int current_page = 0;
    page_fault[0] = 1;
    page[0][0] = referenced[0];
    for (int i = 1; i < num_frames; i++)
        page[i][0] = -1;
    for (int i = 1; i < size_string; i++)
    {
        for (int j = 0; j < num_frames; j++)
        {
            page[j][i] = page[j][i - 1];
            pre[j] = page[j][i - 1];
        }
        if (checkInPre(referenced[i], num_frames) != -1)
            page_fault[i] = -1;
        else
        {
            if (i < num_frames)
            {
                current_page++;
                page[i][current_page] = referenced[i];
            }
            else
            {
                int res = predict_farest(referenced, size_string, num_frames, i);
                page[res][i] = referenced[i];
            }
            page_fault[i] = 1;
            numOfPageFault++;
        }
    }

    print(referenced, page, page_fault, size_string, num_frames);
}
void LRU(int referenced[], int size_string, int num_frames)
{
    int page[20][100];
    int page_fault[100];
    int current_page = 0;
    page_fault[0] = 1;
    page[0][0] = referenced[0];
    for (int i = 1; i < num_frames; i++)
        page[i][0] = -1;
    for (int i = 1; i < size_string; i++)
    {
        for (int j = 0; j < num_frames; j++)
        {
            page[j][i] = page[j][i - 1];
            pre[j] = page[j][i - 1];
        }
        if (checkInPre(referenced[i], num_frames) != -1)
            page_fault[i] = -1;
        else
        {
            if (i < num_frames)
            {
                current_page++;
                page[i][current_page] = referenced[i];
            }
            else
            {
                int res = least_recently(referenced, size_string, num_frames, i);
                page[res][i] = referenced[i];
            }
            page_fault[i] = 1;
            numOfPageFault++;
        }
    }

    print(referenced, page, page_fault, size_string, num_frames);
}
int main()
{
    int n, size_string;
    int referenced[100];
    int num_frames;
    int default_referenced_sequence[] = {2, 1, 5, 2, 0, 6, 8, 4, 0, 0, 7};

    printf("--- Page Replacement algorithm ---");
    printf("\n1. Default referenced sequence");
    printf("\n2. Manual input sequence\n");
    scanf("%d", &n);
    if (n == 1)
    {
        size_string = 11;
        for (int i = 0; i < size_string; i++)
        {
            referenced[i] = default_referenced_sequence[i];
        }
    }
    if (n == 2)
    {
        printf("Nhap do dai chuoi: ");
        scanf("%d", &size_string);
        for (int i = 0; i < size_string; i++)
        {
            scanf("%d", &referenced[i]);
        }
    }
    printf("\n--- Page Replacement algorithm ---");
    printf("\nInput page frames: ");
    scanf("%d", &num_frames);
    printf("\n--- Page Replacement algorithm ---");
    printf("\n1. FIFO algorithm");
    printf("\n2. OPT algorithm");
    printf("\n3. LRU algorithm");
    printf("\n4. All algorithm\n");
    scanf("%d", &n);
    printf("\n--- Page Replacement algorithm ---\n");
    if (n == 1)
    {
        FIFO(referenced, size_string, num_frames);
    }
    if (n == 2)
    {
        OPT(referenced, size_string, num_frames);
    }
    if (n == 3)
    {
        LRU(referenced, size_string, num_frames);
    }
    if (n == 4)
    {
        printf("\n   FIFO algorithm\n");
        FIFO(referenced, size_string, num_frames);
        printf("\n\n\n   OPT algorithm\n");
        OPT(referenced, size_string, num_frames);
        printf("\n\n\n   LRU algorithm\n");
        LRU(referenced, size_string, num_frames);
    }
    return 0;
}