long tree[max_xy][max_xy];

void update(long x , long y , long val){
    long y1;
    while (x <= max_xy){
        y1 = y;
        while (y1 <= max_xy){
            tree[x][y1] += val;
            y1 += (y1 & -y1); 
        }
        x += (x & -x);
    }
}

long long read(long x,long y){ // return sum from 1,1 to x,y.
   long long sum= 0;         
     while(x){
          long y1 = y;
         while(y1){
             sum += tree[x][y1];
               y1 -= y1 & -y1;
        }
        x -= x & -x;
    }
  	return sum;
}

int main()
{
	long long suma = read(x2+1,y2+1) + read(x1,y1) - read(x2+1,y1) - read(x1,y2+1); //suma de rango entre x1,y1 y x2,y2
	update(x+1,y+1, num ); //aumenta en num
}