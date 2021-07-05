/// Double value
double lo = 0, hi = 1e9;
for(int i = 0; i < 200; i++) {
   double midl = lo + (hi-lo)/3.0;
   double midr = midl + (hi-lo)/3.0;
   if(f(midl) < f(midr)) hi = midr;
   else lo = midl;
}
printf("%.15lf\n", f(lo));

/// Integer Value
int lo = INT_MIN, hi = INT_MAX;
while(hi - lo > 2) {
    int midl = lo + (hi - lo) / 3;
    int midr = midl + (hi - lo) / 3;
    if(f(midl) < f(midr)) hi = midr;
    else lo = midl;
}
cout <<  min(f(lo), min(f(lo+1), f(min(hi, lo+2)))) << "\n";
