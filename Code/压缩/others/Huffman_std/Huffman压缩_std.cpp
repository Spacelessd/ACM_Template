#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define n 305
#define m 2*n-1
//#define char unsigned char
typedef struct
{
    int weight;
    int lchild, rchild, parent;
} HuffmanTree;
typedef HuffmanTree HTree[m];

typedef struct
{
    char ch;
    int start;
    char bits[n+1];
} HuffmanCode;
typedef HuffmanCode HCode[n];

int FileRead(int count[], char s[], char filename[])
{
    int i = 0, N = 0, k = 0, temp[n];
    char c;
    FILE *rf;
    rf = fopen(filename, "r");
    if (rf == NULL)
    {
        printf("cannot open file\n");
        exit(0);
    }
    for (i = 0; i < n; i++)
    {
        temp[i] = 0;
        count[i] = 0;
    }
    while (!feof(rf))
    {
        c = fgetc(rf);
        k = c;
        temp[k]++;
        i++;
    }
    fclose(rf);
    for (i = 0; i < n; i++)
    {
        if (temp[i] != 0)
        {
            s[N] = i;
            count[N] = temp[i];
            N++;
        }
    }
    return N;
}

void CreateHuffmanTree(HTree T, int N, int count[], char s[])
{
    int i, j, p1 = 0, p2 = 0, l1, l2;
    for (i = 0; i < 2 * N - 1; i++)
    {
        T[i].lchild = 0;
        T[i].rchild = 0;
        T[i].parent = 0;
    }
    for (i = 0; i < N; i++)
        T[i].weight = count[i];
    for (i = N; i < 2 * N - 1; i++)
    {
        l1 = l2 = 1000000;
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

void HuffmanCoding(HTree T, HCode H, int N, char s[])
{
    int c, p, i, start;
    char cd[n+1];
    for (int i=0;i<=n;++i)cd[i]='A';
    cd[N+1] = '\0';
    for (i = 0; i < N; i++)
    {
        H[i].ch = s[i];
        start = N;
        c = i;
        p = T[c].parent;
        while (p)
        {
            if (T[p].lchild == c) cd[--start] = '0';
            else cd[--start] = '1';
            c = p;
            p = T[p].parent;
            H[i].start = start;
        }
        strcpy(H[i].bits, cd);
    }
}

void FilePrint(HTree T, HCode H, int N)
{
    int i, j = 0;
    FILE *rf, *fp, *rp;
    rf = fopen("HuffmanCode.txt", "w");
    fp = fopen("Char.txt", "w");
    rp = fopen("Weight.txt", "w");
    while (j < N)
    {
        for (i = H[j].start; i < N; i++) fprintf(rf, "%c", H[j].bits[i]);
        fprintf(rf, "\n");
        j++;
    }
    for (i = 0; i < N; i++) fputc(H[i].ch, fp);
    for (i = 0; i < N; i++) fprintf(rp, "%d\n", T[i].weight);
    fclose(rf);
    fclose(fp);
    fclose(rp);
}

void FileWrite(HCode H, int N, char filename[])
{
    int i, k, p = 0;
    char c;
    FILE *rf, *fp;
    rf = fopen(filename, "r");
    fp = fopen("File.txt", "w");
    if (rf == NULL)
    {
        printf("       cannot open file\n\n       ");
        exit(0);
    }
    while (!feof(rf))
    {
        c = fgetc(rf);
        for (i = 0; i < N; i++)
        {
            if (H[i].ch == c)
            {
                for (k = H[i].start; k < N; k++)
                {
                    fputc(H[i].bits[k], fp);
                    p++;
                    if (p == 8)
                    {
                        fprintf(fp, " ");
                        p = 0;
                    }
                }
            }
        }
    }
    fclose(rf);
    fclose(fp);
}

void FileConvert(void)
{
    int i = 0, k = 0, temp = 0, l;
    char st[10];
    FILE *rf, *fp, *rp;
    rf = fopen("File.txt", "r");
    fp = fopen("Code.txt", "wb");
    rp = fopen("Tail.txt", "w");
    if (rf == NULL)
    {
        printf("       cannot open file\n\n       ");
        exit(0);
    }
    while (!feof(rf))
    {
        st[i] = fgetc(rf);
        switch(st[i])
        {
        case'0':
            k = 2 * k + 0;
            i++;
            break;
        case'1':
            k = 2 * k + 1;
            i++;
            break;
        case' ':
            fwrite(&k, 1, 1, fp);
            temp++;
            k = 0;
            i = 0;
            break;
        default:
            fprintf(rp, "%d ", temp);
            for (k = 0; k < i; k++) fprintf(rp, "%c", st[k]);
            break;
        }
    }
    fclose(rf);
    fclose(fp);
    fclose(rp);
    //l = remove("File.txt");
}

int main()
{
    HTree T;
    static HCode H;
    int N;
    int count[n];
    char s[n], filename[10];;
    printf("\n");
    printf("Input Filename\n");
    scanf("%s", filename);
    printf("\n");
    printf("Encoding..........\n");
    N = FileRead(count, s, filename);
    printf("CharacterIn 'Char.txt'\n");
    printf("CharacterWeight In 'Weight.txt'\n");
    CreateHuffmanTree(T, N, count, s);
    HuffmanCoding(T, H, N, s);
    FilePrint(T, H, N);
    printf("Huffman Code In 'HuffmanCode.txt'\n");
    FileWrite(H, N, filename);
    FileConvert();
    printf("Code File  In 'Code.txt'\n");
    printf("Tail File  In 'Tail.txt'\n");
    system("pause");
    return 0;
}


