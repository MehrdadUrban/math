#include <iostream>
using namespace std;
class Fraction {
    public:
        int64_t num,denom;
        Fraction(int64_t num,int64_t denom) {
            this->num = num;
            this->denom = denom;
            this->simplify();
        }
        void simplify() {
            if (denom<0) {
                denom=-denom; num=-num;
            }
            int64_t n = abs(num);
            int64_t m = denom;
            int64_t a = std::max(n,m);
            int64_t b = std::min(n,m);
            while (b!=0) {
                int64_t r = (a%b);
                a=b;
                b=r;
            }
            num/=a;
            denom/=a;
        }
        Fraction operator+ (Fraction b){
            Fraction r(num*b.denom+denom*b.num,denom*b.denom);
            return r;
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

int64_t fact(int n) {
    int64_t r = 1;
    for(int i=1;i<=n;i++)
        r*=i;
    return r;
}

int64_t ffact(int p,int k) {
    int64_t r=1;
    for(int i=p-k+1;i<=p;i++)
        r*=i;
    return r;
}

Fraction p(int n,int k) {
    return Fraction(fact(n),fact(k)*fact(n-k));
}

Fraction bernoulli(int n) {
    Fraction r(1,1);
    for(int k=0;k<n;k++)
        r = r + p(n,k)*bernoulli(k)*Fraction(1,k-n-1);
    return r;
}

int main()
{
    int p=17;
    Fraction(1,p+1).print();
    printf("*n^%d+1/2*n^%d",p+1,p);
    for (int k=2;k<=p;k++){
        Fraction r = bernoulli(k)*Fraction(1,fact(k))*Fraction(ffact(p,k-1),1);
        if (!r.iszero()){
            r.print();
            printf("*n^%d",p-k+1);  
        }
        
    }
    return 0;
}
