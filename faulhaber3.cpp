#include <iostream>

void minmax(int64_t& a,int64_t& b) {
    if (a<b) return;
    int64_t r=a;
    a=b;
    b=r;
}

class Permute {
    private:
        int64_t** data;
        int n;
    public:
        Permute(int n) {
            this->n = n;
            data = new int64_t* [n+1];
            for(int i=0;i<=n;i++){
                data[i] = new int64_t[i+1];
                data[i][0] = 1;
                data[i][i] = 1;
                for(int j=1;j<i;j++)
                    data[i][j] = data[i-1][j-1] + data[i-1][j]; 
            }
                
        }
        ~Permute(){
            for(int i=0;i<=n;i++)
                delete[] data[i];
            delete[] data;  
        }
        int64_t operator() (int n,int p){
            return data[n][p];
        }
};

class Fraction {
    private:
        int64_t num,denom;
    public:
        Fraction(int64_t num,int64_t denom) {
            this->num = num;
            this->denom = denom;
            this->simplify();
        }
        void simplify() {
            if (denom<0) {
                denom=-denom; num=-num;
            }
            int64_t n = (num>0)?num:-num;
            int64_t m = denom;
            minmax(n,m);
            while (n!=0) {
                int64_t r = (m%n);
                m=n;
                n=r;
            }
            num/=m;
            denom/=m;
        }
        Fraction& operator+= (Fraction b){
            num = num*b.denom+denom*b.num;
            denom = denom*b.denom;
            simplify();
            return *this;
        }
        Fraction operator* (Fraction b) {
            Fraction r(num*b.num,denom*b.denom);
            return r;
        }
        void print(){
            printf("%+ld/%ld",num,denom);
        }
        bool iszero(){
            return (num==0);
        }
};

class Bernoulli {
    private:
        Fraction** bernoulli;
    public:
        Bernoulli(int p,Permute& permute) {
            bernoulli = new Fraction*[p+1];
            for (int n=0;n<=p;n++) {
                bernoulli[n] = new Fraction(1,1);
                for(int k=0;k<n;k++)
                    (*this)(n) += (*this)(k) *Fraction(permute(n,k),k-n-1);
            }
        }
        ~Bernoulli(){
            delete[] bernoulli;
        }
        Fraction& operator() (int n) {
            return *bernoulli[n];
        }
};

int main()
{
    int p=35;
    Permute permute(p);
    Bernoulli bernoulli(p,permute);
    Fraction(1,p+1).print(); printf("*n^%d+1/2*n^%d",p+1,p);
    for (int n=2;n<=p;n++) {
        Fraction r = bernoulli(n)*Fraction(permute(p,n),p-n+1);
        if (!r.iszero()){
            r.print(); printf("*n^%d",p-n+1);  
        }
    }
    return 0;
}
