#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE 30000005
#define n 305
#define m 2*n-1

typedef struct
{
    char ch;
    int weight;
    int lchild, rchild, parent;
} HuffmanTree;
typedef HuffmanTree HTree[m];

typedef struct
{
    char ch;
    char bits[n+1];
} HuffmanCode;
typedef HuffmanCode HCode[n];

int FileRead(HTree T, HCode H)
{
    int i = 0, j = 0, N = 0;
    char c, *p;
    static char str[MAX_SIZE];
    FILE *rf, *fp, *rp;
    rf = fopen("Char.txt", "r");
    fp = fopen("HuffmanCode.txt", "r");
    rp = fopen("Weight.txt", "r");
    if (rf == NULL)
    {
        printf("cannot open file\n");
        exit(0);
    }
    if (fp == NULL)
    {
        printf("cannot open file\n");
        exit(0);
    }
    if (rp == NULL)
    {
        printf("cannot open file\n");
        exit(0);
    }
    while (!feof(rf))
    {
        H[N].ch = fgetc(rf);
        T[N].ch = H[N].ch;
        N++;
    }
    while (!feof(fp))
    {
        c = fgetc(fp);
        switch(c)
        {
        case'\n':
            i++;
            j = 0;
            break;
        default:
            H[i].bits[j] = c;
            j++;
            H[i].bits[j] = '\0';
            break;
        }
    }
    for (i = 0; i < N; i++)
        T[i].weight = 0;
    i = 0;
    j = 0;
    while (!feof(rp))
    {
        c = fgetc(rp);
        switch(c)
        {
        case'\n':
            for (p = str; *p != '\0'; p++) T[i].weight = T[i].weight * 10 + *p - 48;
            i++;
            j = 0;
            break;
        default:
            str[j] = c;
            j++;
            str[j] = '\0';
            break;
        }
    }
    fclose(rf);
    fclose(fp);
    fclose(rp);
    return N - 1;
}

void CreateHuffmanTree(HTree &T, int N)
{
    int i, j, p1 = 0, p2 = 0, l1, l2;
    for (i = 0; i < 2 * N - 1; i++)
    {
        T[i].lchild = 0;
        T[i].rchild = 0;
        T[i].parent = 0;
    }
    for (i = N; i < 2 * N - 1; i++)
    {
        l1 = l2 = 100000000;
        for (j = 0; j < i; j++)
        {
            if (T[j].parent == 0)
            {
                if (T[j].weight < l1)
                {
                    l1 = T[j].weight;
                    p1 = j;
                }
            }
        }
        for (j = 0; j < i; j++)
        {
            if (T[j].parent == 0)
            {
                if ((T[j].weight < l2) && (j != p1))
                {
                    l2 = T[j].weight;
                    p2 = j;
                }
            }
        }
        T[p1].parent = i;
        T[p2].parent = i;
        T[i].lchild = p1;
        T[i].rchild = p2;
        T[i].weight = T[p1].weight + T[p2].weight;
    }
    T[2*N-2].parent = 0;
}

int FileExtract(void)
{
    int i, j = 0, k = 0, t, temp = 0;
    unsigned char c;
    char s[8];
    FILE *rf, *fp, *rp;
    rf = fopen("Tail.txt", "r");
    fp = fopen("File00.txt", "w");
    rp = fopen("File00.txt", "a");
    if (rf == NULL)
    {
        printf("cannot open file\n");
        exit(0);
    }
    fscanf(rf, "%d %s", &temp, s);
    fclose(rf);
    rf = fopen("Code.txt", "rb");
    if (rf == NULL)
    {
        printf("cannot open file\n");
        exit(0);
    }
    while (j < temp)
    {
        j++;
        c = fgetc(rf);
        for (i = 7; i >= 0; i--)
        {
            t = c;
            t >>= i;
            t &= 1;
            if (k == 0 && t == 1)
                k = 1;
            if (k == 1)
                fprintf(fp, "%d", t);
        }
        fprintf(fp, " ");
    }
    fclose(rf);
    fclose(fp);
    for (i = 0; s[i] != '\0'; i++) fprintf(rp, "%c", s[i]);
    fclose(rf);
    fclose(rp);
    return temp;
}

float FileTrans(HTree &T, HCode &H, int N)
{
    int i = 2 * N - 2, l;
    float temp = 0.0;
    char c;
    FILE *rf, *fp;
    rf = fopen("File00.txt", "r");
    fp = fopen("Translated File.txt", "w");
    if (rf == NULL)
    {
        printf("cannot open file\n");
        exit(0);
    }
    while(!feof(rf))
    {
        c = fgetc(rf);
        if (T[i].lchild || T[i].rchild)
        {
            if (c == '0') i = T[i].lchild;
            else if (c == '1') i = T[i].rchild;
        }
        else
        {
            fputc(T[i].ch, fp);
            temp++;
            i = 2 * N - 2;
            if (c == '0') i = T[i].lchild;
            else if (c == '1') i = T[i].rchild;
        }
    }
    fclose(rf);
    fclose(fp);
    l = remove("File00.txt");
    return temp;
}
int main()
{
    static HTree T;
    static HCode H;
    int N, temp01;
    float temp02;
    N = FileRead(T, H);
    printf("decoding......\n");
    CreateHuffmanTree(T, N);
    temp01 = FileExtract();
    temp02 = FileTrans(T, H, N);
    printf("Translated File In Translated File.txt\n");
    printf("percent=%6f%%\n ", temp01 / temp02 * 100);
    system("pause");
    return 0;
}


