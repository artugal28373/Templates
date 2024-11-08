/*
Primitive root modulo  
n  exists if and only if:

 
n  is 1, 2, 4, or
 
n  is power of an odd prime number  
(n = p^k) , or
 
n  is twice power of an odd prime number  
(n = 2 * p^k) .
*/


/*

In modular arithmetic, a number  
g  is called a primitive root modulo n if every number coprime to n  is congruent to a power of  g  modulo  n .
Mathematically, g  is a primitive root modulo n if and only if for any integer  a  such that  gcd(a, n) = 1 , there exists an integer k  such that:
g^k = a mod n .
k is then called the index or discrete logarithm of a  to the base g  modulo  n.  
g  is also called the generator of the multiplicative group of integers modulo n .
In particular, for the case where n  is a prime, the powers of primitive root runs through all numbers from  1 to  n-1 .

*/

/*
Now we have a complete algorithm for finding the primitive root:
First, find  phi(n)  and factorize it.
Then iterate through all numbers  g in [1, n] , and for each number, to check if it is primitive root, we do the following:
Calculate all  
 g ^ { phi (n)\ p_i} mod n .
If all the calculated values are different from  1 , then  g  is a primitive root.
Running time of this algorithm is  
$O(Ans \cdot \log \phi (n) \cdot \log n)$  (assume that  
$\phi (n)$  has  
$\log \phi (n)$  divisors).

Shoup (1990, 1992) proved, assuming the generalized Riemann hypothesis, that  
$g$  is  
$O(\log^6 p)$ .
*/




https://cp-algorithms.com/algebra/primitive-root.html
int generator (int p) {
    vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= powmod (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}
