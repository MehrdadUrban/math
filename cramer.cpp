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
        double& element (int i,int j) { return data[j*n+i]; }
        Matrix eliminate(int i,int j) {
            Matrix r(n-1);
            for (int ii=0;ii<n;ii++)
                for (int jj=0;jj<n;jj++) {
                    if ((ii==i)||(jj==j))
                        continue;
                    int p = (ii<i)?ii:ii-1;
                    int q = (jj<j)?jj:jj-1;
                    r.element(p,q) = element(ii,jj);
                }
            return r;
        }
        double determinant() {
            if (n==1)
                return element(0,0);
            double s = 0;
            int i = 0;
            for(int j=0;j<n;j++){
                double r = element(i,j)*eliminate(i,j).determinant();
                if ((i+j)%2==0)
                    s+=r;
                else
                    s-=r;
            }
            return s;
        }
        Matrix inverse() {
            Matrix r(n);
            double det = determinant();
            for (int i=0;i<n;i++)
                for (int j=0;j<n;j++) {
                    double p = eliminate(i,j).determinant()/det;
                    if ((i+j)%2==1)
                        p = -p;
                    r.element(j,i) = p;
                }
            return r;
        }
        void print() {
            for (int i=0;i<n;i++){
                for (int j=0;j<n;j++) {
                    printf("%f\t,",element(i,j));
                }
                printf("\n");
            }
        }
        Matrix mult (Matrix& b){
            Matrix r(n);
            for (int i=0;i<n;i++)
                for (int j=0;j<n;j++){
                    double s=0;
                    for(int k=0;k<n;k++)
                        s+=element(i,k)*b.element(k,j);
                    r.element(i,j) = s;
                }
            return r;
        }
};

int main()
{
    int n=7;
    Matrix mat(n);
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            mat.element(i,j) = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    //mat.print();
    mat.inverse().mult(mat).print();
    return 0;
}
