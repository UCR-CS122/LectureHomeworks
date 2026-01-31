/************ t.c file of Program C2.3 ***********/
int g; // un-initialized global

extern int sum(int, int, int, int, int, int);

int main() {
    int a, b, c, d, e, f; // local variables
    a = b = c =d =e = f = 1; // values do not matter
    g = sum(a,b,c,d,e,f); // call sum(), passing a,b,c,d,e,f
}