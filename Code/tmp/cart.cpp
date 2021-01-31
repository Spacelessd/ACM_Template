void array_multiplication(int A[], int OUTPUT[], int n) 
{
 int left = 1;
 int right = 1;
  for (int i = 0; i < n; i++)
  OUTPUT[i] = 1;
  for (int i = 0; i < n; i++) {
    OUTPUT[i] *= left;
    OUTPUT[n - 1 - i] *= right;
    left *= A[i];
    right *= A[n - 1 - i];
  }
}
