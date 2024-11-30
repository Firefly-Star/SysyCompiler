int main() {
    const int x = 1 + 1, y = 10;
    int z = 10;
    z = z + 1;
    {
        int x = 10;
        int y = 20;
    }
    if (1)
    {
        return x;
    }
    else
    {
        return y; 
    }
    while(1)
    {
        return z; 123; 
    }
    return z;  
}