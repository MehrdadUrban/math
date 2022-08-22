#include <iostream>

void minmax(int64_t& a,int64_t& b) {
    if (a<b) return;
    int64_t r=a;
    a=b;
    b=r;
}

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

int64_t fact(int64_t p,int64_t k) {
    int64_t r=1;
    for(int i=k+1;i<=p;i++)
        r*=i;
    return r;
}

int64_t permute(int64_t n,int64_t k) {
    int64_t l = n-k;
    int64_t m = k;
    minmax(m,l);
    return fact(n,l)/fact(m,0);
}

int main()
{
    int p=18;
    
    Fraction** bernoulli = new Fraction*[p+1];
    for (int n=0;n<=p;n++) {
        bernoulli[n] = new Fraction(1,1);
        for(int k=0;k<n;k++)
            *bernoulli[n] += *bernoulli[k] *Fraction(permute(n,k),k-n-1);
    }
        
    Fraction(1,p+1).print(); printf("*n^%d+1/2*n^%d",p+1,p);
    for (int n=2;n<=p;n++) {
        Fraction r = *bernoulli[n]*Fraction(permute(p,n),p-n+1);
        if (!r.iszero()){
            r.print(); printf("*n^%d",p-n+1);  
        }
    }
    for (int n=0;n<=p;n++)
        delete bernoulli[n];
    delete[] bernoulli;
    return 0;
}
