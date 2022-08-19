#include <stdio.h>
#include <cstdlib>

class Matrix {
    private:
        double *data;
        int n;
    public:
        Matrix(int m) {
            n = m;
            data = new double[n*n]();
        }
        ~Matrix() {  delete[] data; }
        double& operator() (int i,int j) { return data[j*n+i]; }
        Matrix eliminate(int i,int j) {
            Matrix r(n-1);
            for (int ii=0;ii<n;ii++)
                for (int jj=0;jj<n;jj++) {
                    if ((ii==i)||(jj==j))
                        continue;
                    int p = (ii<i)?ii:ii-1;
                    int q = (jj<j)?jj:jj-1;
                    r(p,q) = (*this)(ii,jj);
                }
            return r;
        }
        double determinant() {
            if (n==1)
                return (*this)(0,0);
            double s = 0;
            int i = 0;
            for(int j=0;j<n;j++)
                s+= evenodd(i+j)*(*this)(i,j)*eliminate(i,j).determinant();
            return s;
        }
        Matrix inverse() {
            Matrix r(n);
            double det = determinant();
            for (int i=0;i<n;i++)
                for (int j=0;j<n;j++) 
                    r(j,i) = evenodd(i+j)*eliminate(i,j).determinant()/det;
            return r;
        }
        void print() {
            for (int i=0;i<n;i++){
                for (int j=0;j<n;j++)
                    printf("%f%c\t",(*this)(i,j),j==(n-1)?';':',');
                printf("\n");
            }
        }
        Matrix mult (Matrix& b){
            Matrix r(n);
            for (int i=0;i<n;i++)
                for (int j=0;j<n;j++){
                    double s=0;
                    for(int k=0;k<n;k++)
                        s+=(*this)(i,k)*b(k,j);
                    r(i,j) = s;
                }
            return r;
        }
        static int evenodd(int p) {
            if (p%2==0)
                return 1;
            else
                return -1;
        }
};

int main()
{
    int n=7;
    Matrix mat(n);
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            mat(i,j) = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    Matrix inv = mat.inverse();
    printf("The inverse of Matrix:\n"); mat.print();
    printf("is:\n"); inv.print();
    printf("Inverse*Matrix is:\n"); inv.mult(mat).print();
    return 0;
}
