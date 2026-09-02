int fact(int x){
    int result=1;

    for(int i=1; i<=x; i++)
        result = i*result;
    
    return result;
}