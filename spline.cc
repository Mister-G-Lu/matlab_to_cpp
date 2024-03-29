#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

using vec = vector<double>;

struct SplineSet{
    double a;
    double b;
    double c;
    double d;
    double x;
};

/**
 * Implement Spline from the math algorithm (equal idea to Matlab Spline)
 * 
 * Returns coefficients where S(X) = a + b(x-xj)+ c(x-xj)^2 + d(x-xj)^3
 */
vector<SplineSet> spline(vec &x, vec &y)
{
    int n = x.size()-1;
    vec a;
    a.insert(a.begin(), y.begin(), y.end());
    vec b(n);
    vec d(n);
    vec h;

    for(int i = 0; i < n; ++i)
        h.push_back(x[i+1]-x[i]);

    vec alpha;
    alpha.push_back(0);
    for(int i = 1; i < n; ++i)
        alpha.push_back( 3*(a[i+1]-a[i])/h[i] - 3*(a[i]-a[i-1])/h[i-1]  );

    vec c(n+1);
    vec l(n+1);
    vec mu(n+1);
    vec z(n+1);
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for(int i = 1; i < n; ++i)
    {
        l[i] = 2 *(x[i+1]-x[i-1])-h[i-1]*mu[i-1];
        mu[i] = h[i]/l[i];
        z[i] = (alpha[i]-h[i-1]*z[i-1])/l[i];
    }

    l[n] = 1;
    z[n] = 0;
    c[n] = 0;

    for(int j = n-1; j >= 0; --j)
    {
        c[j] = z [j] - mu[j] * c[j+1];
        b[j] = (a[j+1]-a[j])/h[j]-h[j]*(c[j+1]+2*c[j])/3;
        d[j] = (c[j+1]-c[j])/3/h[j];
    }

    vector<SplineSet> output_set(n);
    for(int i = 0; i < n; ++i)
    {
        output_set[i].a = a[i];
        output_set[i].b = b[i];
        output_set[i].c = c[i];
        output_set[i].d = d[i];
        output_set[i].x = x[i];
    }
    return output_set;
}

/* calculate every result of X within S(X) = a + b(x-xj)+ c(x-xj)^2 + d(x-xj)^3,
* given the spline Set
* assumes an interval of 1
*/
vector<double> ppval(vector<SplineSet> cs, vector<double> x){
    vector<double> answer;
    for (double temp: x){
        if (temp<0 || temp>cs.size(){
            cout<< "X " << temp << " outside of spline set!";
            continue;
        }
        
        SplineSet bestSpline = cs.at((int)temp);
    
        // to be updated
    }
    return answer;
}

int main()
{
    vec x(11);
    vec y(11);
    for(int i = 0; i < x.size(); ++i)
    {
        x[i] = i;
        y[i] = sin(i);
    }

    vector<SplineSet> cs = spline(x, y);
    for(int i = 0; i < cs.size(); ++i)
        cout << cs[i].d << "\t" << cs[i].c << "\t" << cs[i].b << "\t" << cs[i].a << endl;
}
