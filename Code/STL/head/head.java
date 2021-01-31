namespace Temp
{
    struct PointInt
    {
        public long X;

        public long Y;

        public PointInt(long x, long y)
            : this()
        {
            this.X = x;
            this.Y = y;
        }

        public PointInt(PointInt head)
            : this(head.X, head.Y)
        {
        }

        public static PointInt operator +(PointInt a, PointInt b)
        {
            return new PointInt(a.X + b.X, a.Y + b.Y);
        }

        public static PointInt operator -(PointInt a, PointInt b)
        {
            return new PointInt(a.X - b.X, a.Y - b.Y);
        }

        public static PointInt operator *(PointInt a, long k)
        {
            return new PointInt(k * a.X, k * a.Y);
        }

        public static PointInt operator *(long k, PointInt a)
        {
            return new PointInt(k * a.X, k * a.Y);
        }

        public bool IsInsideRectangle(long l, long b, long r, long t)
        {
            return (l <= X) && (X <= r) && (b <= Y) && (Y <= t);
        }
    }

    struct LineInt
    {
        public LineInt(PointInt a, PointInt b)
            : this()
        {
            A = a.Y - b.Y;
            B = b.X - a.X;
            C = a.X * b.Y - a.Y * b.X;
        }

        public long A, B, C;

        public bool ContainsPoint(PointInt p)
        {
            return A * p.X + B * p.Y + C == 0;
        }
    }

    class MatrixInt
    {
        private long[,] m_Matrix;

        public int Size
        {
            get
            {
                return m_Matrix.GetLength(0) - 1;
            }
        }

        public long Mod { get; private set; }

        public MatrixInt(int size, long mod = 0)
        {
            m_Matrix = new long[size + 1, size + 1];
            Mod = mod;
        }

        public MatrixInt(long[,] matrix, long mod = 0)
        {
            this.m_Matrix = matrix;
            Mod = mod;
        }

        public static MatrixInt GetIdentityMatrix(int size, long mod = 0)
        {
            long[,] matrix = new long[size + 1, size + 1];

            for (int i = 1; i <= size; i++)
            {
                matrix[i, i] = 1;
            }

            return new MatrixInt(matrix, mod);
        }

        public long this[int i, int j]
        {
            get
            {
                return m_Matrix[i, j];
            }

            set
            {
                m_Matrix[i, j] = value;
            }
        }

        public static MatrixInt operator +(MatrixInt a, MatrixInt b)
        {
            int n = a.Size;
            long mod = Math.Max(a.Mod, b.Mod);
            long[,] c = new long[n, n];
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    c[i, j] = a[i, j] + b[i, j];
                }
            }

            if (mod > 0)
            {
                for (int i = 1; i <= n; i++)
                {
                    for (int j = 1; j <= n; j++)
                    {
                        c[i, j] %= mod;
                    }
                }
            }

            return new MatrixInt(c, mod);
        }

        public static MatrixInt operator *(MatrixInt a, MatrixInt b)
        {
            int n = a.Size;
            long mod = Math.Max(a.Mod, b.Mod);

            long[,] c = new long[n, n];

            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    for (int k = 1; k <= n; k++)
                    {
                        c[i, j] += a[i, k] * b[k, j];
                        if (mod > 0)
                        {
                            c[i, j] %= mod;
                        }
                    }
                }
            }

            return new MatrixInt(c, mod);
        }
    }

    static class Algebra
    {
        public static long Phi(long n)
        {
            long result = n;
            for (long i = 2; i * i <= n; i++)
            {
                if (n % i == 0)
                {
                    while (n % i == 0)
                    {
                        n /= i;
                    }

                    result -= result / i;
                }
            }

            if (n > 1)
            {
                result -= result / n;
            }

            return result;
        }

        public static long BinPower(long a, long n, long mod)
        {
            long result = 1;

            while (n > 0)
            {
                if ((n & 1) != 0)
                {
                    result = (result * a) % mod;
                }

                a = (a * a) % mod;
                n >>= 1;
            }

            return result;
        }

        public static class Permutations
        {
            public static int[] GetRandomPermutation(int n)
            {
                int[] p = new int[n];
                for (int i = 0; i < n; i++)
                {
                    p[i] = i;
                }

                Random random = new Random();
                for (int i = n - 1; i > 0; i--)
                {
                    int j = random.Next(i + 1);
                    int tmp = p[i];
                    p[i] = p[j];
                    p[j] = tmp;
                }

                return p;
            }
        }

        public static T[] Shuffle<T>(this T[] array)
        {
            int length = array.Length;
            int[] p = Permutations.GetRandomPermutation(length);
            T[] result = new T[length];
            for (int i = 0; i < length; i++)
            {
                result[i] = array[p[i]];
            }

            return result;
        }

        public static MatrixInt MatrixBinPower(MatrixInt a, long n)
        {
            MatrixInt result = new MatrixInt(a.Size);

            while (n > 0)
            {
                if ((n & 1) != 0)
                {
                    result *= a;
                }

                a *= a;
                n >>= 1;
            }

            return result;
        }

        public static long Gcd(long a, long b)
        {
            return b == 0 ? a : Gcd(b, a % b);
        }

        public static long ExtendedGcd(long a, long b, out long x, out long y)
        {
            if (b == 0)
            {
                x = 1;
                y = 0;
                return a;
            }

            long x1;
            long y1;
            long d = ExtendedGcd(b, a % b, out x1, out y1);
            x = y1;
            y = x1 - (a / b) * y1;
            return d;
        }

        public static long Lcm(long a, long b)
        {
            return (a / Gcd(a, b)) * b;
        }

        public static bool[] GetPrimes(int n)
        {
            n = Math.Max(n, 2);
            bool[] prime = new bool[n + 1];
            for (int i = 2; i <= n; i++)
            {
                prime[i] = true;
            }

            for (int i = 2; i * i <= n; i++)
            {
                if (prime[i])
                {
                    if ((long)i * i <= n)
                    {
                        for (int j = i * i; j <= n; j += i)
                        {
                            prime[j] = false;
                        }
                    }
                }
            }

            return prime;
        }

        public static long GetFibonacciNumber(long n, long mod = 0)
        {
            long[,] matrix = new long[,] { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 1 } };

            MatrixInt result = MatrixBinPower(new MatrixInt(matrix, mod), n);

            return result[2, 2];
        }

        public static long[] GetFibonacciSequence(int n)
        {
            long[] result = new long[n];
            result[0] = result[1] = 1;

            for (int i = 2; i < n; i++)
            {
                result[i] = result[i - 1] + result[i - 2];
            }

            return result;
        }

        public static long GetInverseElement(long a, long mod)
        {
            long x, y;
            long g = ExtendedGcd(a, mod, out x, out y);

            if (g != 1)
            {
                return -1;
            }

            return ((x % mod) + mod) % mod;
        }

        public static long[] GetAllInverseElements(long mod)
        {
            long[] result = new long[mod];
            result[1] = 1;
            for (int i = 2; i < mod; i++)
            {
                result[i] = (mod - (((mod / i) * result[mod % i]) % mod)) % mod;
            }

            return result;
        }
    }

    internal static class Reader
    {
        public static void ReadInt(out int a)
        {
            int[] number = new int[1];
            ReadInt(number);
            a = number[0];
        }

        public static void ReadInt(out int a, out int b)
        {
            int[] numbers = new int[2];
            ReadInt(numbers);
            a = numbers[0];
            b = numbers[1];
        }

        public static void ReadInt(out int int1, out int int2, out int int3)
        {
            int[] numbers = new int[3];
            ReadInt(numbers);
            int1 = numbers[0];
            int2 = numbers[1];
            int3 = numbers[2];
        }

        public static void ReadInt(out int int1, out int int2, out int int3, out int int4)
        {
            int[] numbers = new int[4];
            ReadInt(numbers);
            int1 = numbers[0];
            int2 = numbers[1];
            int3 = numbers[2];
            int4 = numbers[3];
        }

        public static void ReadLong(out long a)
        {
            long[] number = new long[1];
            ReadLong(number);
            a = number[0];
        }

        public static void ReadLong(out long a, out long b)
        {
            long[] numbers = new long[2];
            ReadLong(numbers);
            a = numbers[0];
            b = numbers[1];
        }

        public static void ReadLong(out long int1, out long int2, out long int3)
        {
            long[] numbers = new long[3];
            ReadLong(numbers);
            int1 = numbers[0];
            int2 = numbers[1];
            int3 = numbers[2];
        }

        public static void ReadLong(out long int1, out long int2, out long int3, out long int4)
        {
            long[] numbers = new long[4];
            ReadLong(numbers);
            int1 = numbers[0];
            int2 = numbers[1];
            int3 = numbers[2];
            int4 = numbers[3];
        }

        public static void ReadInt(int[] numbers)
        {
            // ReSharper disable PossibleNullReferenceException
            var list = Console.ReadLine().Split();
            // ReSharper restore PossibleNullReferenceException

            int count = Math.Min(numbers.Length, list.Length);

            for (int i = 0; i < count; i++)
            {
                numbers[i] = int.Parse(list[i]);
            }
        }

        public static int[] ReadDigits()
        {
            // ReSharper disable AssignNullToNotNullAttribute
            return Console.ReadLine().Select(x => int.Parse(x.ToString())).ToArray();
            // ReSharper restore AssignNullToNotNullAttribute
        }

        public static void ReadLong(long[] numbers)
        {
            // ReSharper disable PossibleNullReferenceException
            var list = Console.ReadLine().Split();
            // ReSharper restore PossibleNullReferenceException

            int count = Math.Min(numbers.Length, list.Length);

            for (int i = 0; i < count; i++)
            {
                numbers[i] = long.Parse(list[i]);
            }
        }

        public static void ReadDouble(double[] numbers)
        {
            // ReSharper disable PossibleNullReferenceException
            var list = Console.ReadLine().Split();
            // ReSharper restore PossibleNullReferenceException

            int count = Math.Min(numbers.Length, list.Length);

            for (int i = 0; i < count; i++)
            {
                numbers[i] = double.Parse(list[i]);
            }
        }

        public static void ReadDouble(out double a, out double b)
        {
            double[] numbers = new double[2];
            ReadDouble(numbers);
            a = numbers[0];
            b = numbers[1];
        }

        public static void ReadDouble(out double int1, out double int2, out double int3)
        {
            double[] numbers = new double[3];
            ReadDouble(numbers);
            int1 = numbers[0];
            int2 = numbers[1];
            int3 = numbers[2];
        }

        public static string ReadLine()
        {
            return Console.ReadLine();
        }
    }

    static class MyMath
    {
        public static int GetMinimalPrimeDivisor(int n)
        {
            for (int i = 2; i * i <= n; i++)
            {
                if (n % i == 0)
                {
                    return i;
                }
            }

            return n;
        }

        public static long Sqr(long x)
        {
            return x * x;
        }
    }

    public interface IGraph
    {
        int Vertices { get; set; }

        IList<int> this[int i] { get; }

        void AddEdge(int u, int v);

        void AddOrientedEdge(int u, int v);
    }

    public class Graph : IGraph
    {
        private List<int>[] m_Edges;

        public int Vertices { get; set; }

        public IList<int> this[int i]
        {
            get
            {
                return this.m_Edges[i];
            }
        }

        public Graph(int vertices)
        {
            this.Vertices = vertices;

            this.m_Edges = new List<int>[vertices];

            for (int i = 0; i < vertices; i++)
            {
                this.m_Edges[i] = new List<int>();
            }
        }

        public void AddEdge(int u, int v)
        {
            this.AddOrientedEdge(u, v);
            this.AddOrientedEdge(v, u);
        }

        public void AddOrientedEdge(int first, int second)
        {
            this.m_Edges[first].Add(second);
        }

        public int[] Bfs(int start)
        {
            int[] d = new int[Vertices];
            for (int i = 0; i < Vertices; i++)
            {
                d[i] = -1;
            }

            Queue<int> queue = new Queue<int>();
            queue.Enqueue(start);
            d[start] = 0;

            while (queue.Count > 0)
            {
                int v = queue.Dequeue();
                foreach (int t in this.m_Edges[v].Where(t => d[t] == -1))
                {
                    queue.Enqueue(t);
                    d[t] = d[v] + 1;
                }
            }

            return d;
        }
    }

    class SimpleSumTable
    {
        private readonly int[,] m_Sum;

        public SimpleSumTable(int n, int m, int[,] table)
        {
            m_Sum = new int[n + 1, m + 1];

            for (int i = 1; i < n + 1; i++)
            {
                for (int j = 1; j < m + 1; j++)
                {
                    m_Sum[i, j] = m_Sum[i, j - 1] + m_Sum[i - 1, j] - m_Sum[i - 1, j - 1] + table[i, j];
                }
            }
        }

        public int GetSum(int l, int b, int r, int t)
        {
            return m_Sum[r, t] - m_Sum[r, b] - m_Sum[l, t] + m_Sum[l, b];
        }
    }

    class SegmentTreeSimpleInt<T>
    {
        public int Size { get; private set; }

        private readonly T[] m_Tree;

        private Func<T, T, T> m_Operation;

        private T m_Null;

        public SegmentTreeSimpleInt(int size, Func<T, T, T> operation, T nullElement, IList<T> array = null)
        {
            this.Size = size;
            this.m_Operation = operation;
            this.m_Null = nullElement;

            m_Tree = new T[4 * size];
            if (array != null)
            {
                this.Build(array, 1, 0, size - 1);
            }
        }

        private void Build(IList<T> array, int v, int tl, int tr)
        {
            if (tl == tr)
            {
                m_Tree[v] = array[tl];
            }
            else
            {
                int tm = (tl + tr) / 2;
                this.Build(array, 2 * v, tl, tm);
                this.Build(array, 2 * v + 1, tm + 1, tr);
                this.CalculateNode(v);
            }
        }

        public T GetSum(int l, int r)
        {
            return GetSum(1, 0, Size - 1, l, r);
        }

        private T GetSum(int v, int tl, int tr, int l, int r)
        {
            if (l > r)
            {
                return m_Null;
            }

            if (l == tl && r == tr)
            {
                return m_Tree[v];
            }

            int tm = (tl + tr) / 2;

            return this.m_Operation(GetSum(2 * v, tl, tm, l, Math.Min(r, tm)), GetSum(2 * v + 1, tm + 1, tr, Math.Max(l, tm + 1), r));
        }

        public void Update(int pos, T newValue)
        {
            Update(1, 0, Size - 1, pos, newValue);
        }

        private void Update(int v, int tl, int tr, int pos, T newValue)
        {
            if (tl == tr)
            {
                m_Tree[v] = newValue;
            }
            else
            {
                int tm = (tl + tr) / 2;
                if (pos <= tm)
                {
                    Update(2 * v, tl, tm, pos, newValue);
                }
                else
                {
                    Update(2 * v + 1, tm + 1, tr, pos, newValue);
                }
                this.CalculateNode(v);
            }
        }

        private void CalculateNode(int v)
        {
            m_Tree[v] = this.m_Operation(m_Tree[2 * v], m_Tree[2 * v + 1]);
        }
    }

    struct Pair<TFirst, TSecond>
    {
        public Pair(TFirst first, TSecond second)
            : this()
        {
            this.First = first;
            this.Second = second;
        }

        public TFirst First { set; get; }

        public TSecond Second { set; get; }
    }

    internal class FenwickTreeInt64
    {
        public FenwickTreeInt64(int size)
        {
            this.m_Size = size;
            m_Tree = new long[size];
        }

        public FenwickTreeInt64(int size, IList<long> tree)
            : this(size)
        {
            for (int i = 0; i < size; i++)
            {
                Inc(i, tree[i]);
            }
        }

        public long Sum(int r)
        {
            long res = 0;
            for (; r >= 0; r = (r & (r + 1)) - 1)
            {
                res += m_Tree[r];
            }
            return res;
        }

        public long Sum(int l, int r)
        {
            return Sum(r) - Sum(l - 1);
        }

        public void Inc(int i, long x)
        {
            for (; i < m_Size; i = i | (i + 1))
            {
                m_Tree[i] += x;
            }
        }

        public void Set(int i, long x)
        {
            Inc(i, x - Sum(i, i));
        }

        private int m_Size;
        private long[] m_Tree;
    }

    internal class AccumulativeDictionary<TKey> : Dictionary<TKey, int>
    {
        public new void Add(TKey key, int value = 1)
        {
            if (this.ContainsKey(key))
            {
                base[key] += value;
            }
            else
            {
                base.Add(key, value);
            }
        }

        public new int this[TKey key]
        {
            get
            {
                return this.ContainsKey(key) ? base[key] : 0;
            }
            set
            {
                this.Add(key, value);
            }
        }
    }

    class PriorityQueue<T>
    {
        public PriorityQueue(Comparison<T> comparison = null)
        {
            if (comparison == null)
            {
                if (typeof(T).GetInterfaces().Any(i => i == typeof(IComparable<T>)))
                {
                    m_Comparison = (a, b) => ((IComparable<T>)a).CompareTo(b);
                }
                else
                {
                    throw new ApplicationException("Add comparer");
                }
            }
            else
            {
                m_Comparison = comparison;
            }
        }

        public int Count { get; private set; }

        public void Enqueue(T item)
        {
            m_List.Add(item);
            m_Indexes.Add(item, this.Count);
            this.Count++;
            Up(this.Count);
        }

        public T Peek()
        {
            return m_List[0];
        }

        public T Dequeue()
        {
            if (this.Count > 0)
            {
                var result = m_List[0];

                Swap(0, this.Count - 1);
                m_Indexes.Remove(m_List[this.Count - 1]);
                m_List.RemoveAt(this.Count - 1);
                this.Count--;
                this.Down(1);

                return result;
            }
            throw new ApplicationException("Couldn't get element from empty queue");
        }

        public void Update(T item)
        {
            int index = m_Indexes[item];
            this.Up(index + 1);
        }

        private readonly List<T> m_List = new List<T>();

        private readonly Dictionary<T, int> m_Indexes = new Dictionary<T, int>();

        private readonly Comparison<T> m_Comparison;

        private void Up(int index)
        {
            while (index > 1 && m_Comparison.Invoke(m_List[index - 1], m_List[index / 2 - 1]) > 0)
            {
                this.Swap(index - 1, index / 2 - 1);

                index = index / 2;
            }
        }

        private void Down(int index)
        {
            while (2 * index <= this.Count && m_Comparison.Invoke(m_List[index - 1], m_List[2 * index - 1]) < 0 ||
                   2 * index + 1 <= this.Count && m_Comparison.Invoke(m_List[index - 1], m_List[2 * index]) < 0)
            {
                if (2 * index + 1 > this.Count || m_Comparison.Invoke(m_List[2 * index - 1], m_List[2 * index]) > 0)
                {
                    this.Swap(index - 1, 2 * index - 1);
                    index = 2 * index;
                }
                else
                {
                    this.Swap(index - 1, 2 * index);
                    index = 2 * index + 1;
                }
            }
        }

        private void Swap(int i, int j)
        {
            var tmp = m_List[i];
            m_List[i] = m_List[j];
            m_List[j] = tmp;

            m_Indexes[m_List[i]] = i;
            m_Indexes[m_List[j]] = j;
        }
    }

    class Program
    {
        private static StreamReader m_InputStream;

        private static StreamWriter m_OutStream;

        private static void OpenFiles()
        {
            m_InputStream = File.OpenText("input.txt");
            Console.SetIn(m_InputStream);

            m_OutStream = File.CreateText("output.txt");
            Console.SetOut(m_OutStream);
        }

        private static void CloseFiles()
        {
            m_OutStream.Flush();

            m_InputStream.Dispose();
            m_OutStream.Dispose();
        }

        static void Main()
        {
           // OpenFiles();

            new Solution().Solve();

          //  CloseFiles();
        }
    }

    internal class Solution
    {
        public void Solve()
        {
            /*for (int i = 0; i < 10; i++)
            {
                Console.Write("{0} ", this.S(i, 4));
            }
            Console.WriteLine();*/

            int n;
            Reader.ReadInt(out n);
            long[] a = new long[n];
            Reader.ReadLong(a);

            List<FenwickTreeInt64>[] f = new List<FenwickTreeInt64>[5];
            for (int k = 0; k < 5; k++)
            {
                f[k] = new List<FenwickTreeInt64>();

                int z = k + 2;
                int d = 2 * z - 2;
                for (int i = 0; i < d; i++)
                {
                    FenwickTreeInt64 tree = new FenwickTreeInt64(n);
                    for (int j = 0; j < n; j++)
                    {
                        var v = a[j] * this.S(j - i, z);
                        tree.Inc(j, v);
                    }
                    f[k].Add(tree);
                }
            }

            int m;
            Reader.ReadInt(out m);
            for (int i = 0; i < m; i++)
            {                
                var b = Console.ReadLine().Split().Select(long.Parse).ToArray();
                if (b[0] == 1)
                {
                    int p = (int)b[1] - 1;
                    long v = b[2];
                    for (int k = 0; k < 5; k++)
                    {
                        int z = k + 2;
                        int d = 2 * z - 2;
                        for (int j = 0; j < d; j++)
                        {                            
                            f[k][j].Set(p, v * S(p - j, z));
                        }
                    }
                }
                else
                {
                    int z = (int)b[3];
                    int l = (int)b[1] - 1;
                    int r = (int)b[2] - 1;
                    int t = (l + 2 * z - 2) % (2 * z - 2);
                    long res = f[z - 2][t].Sum(l, r);
                    Console.WriteLine(res);
                }
            }
        }

        private long S(int i, int z)
        {
            int m = (i + 1 + 2 * (z - 1)) % (2 * (z - 1));
            if (m == 0)
            {
                return 2;
            }
            if (m <= z)
            {
                return m;
            }
            return 2 * z - m;
        }
    }
}


