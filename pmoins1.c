#include <stdio.h>
#include <stdlib.h>
#include "pmoins1.h"




int pair(long long a){
	return !(a&1LL);	
}


/*renvoie la plus grande puissance de p tq p^res<n*/
long power_premier(long long n, int p){
	long res=0;
	long long pp=p;
	if(p>n){
		return 0;
	}
	while(pp<n){
		pp*=p;
		res++;
	}
	return res;
}

long long pgcd(long long a, long long b){
	long long  d=0LL;
	while(pair(a)&&pair(b)){
		if(pair(a)&&pair(b)){
			d++;
			a>>=(1LL);
			b>>=(1LL);
		}
		else if(pair(a)){
			a>>=(1LL);
		}
		else if(pair(b)){
			b>>=(1LL);
		}
	}
	while(a!=b){
		if(a>b){
			a-=b;
		}
		else{
			b-=a;
		}
	}
	return a<<d;
}

long long mulmod(long long unsigned a, long long unsigned b, long long unsigned m){
	long long res=0;
	a%=m;
	b%=m;
	while(b){
		if(b&1){
			res+=a; if(res>=m) res-=m;}
			a+=a; if(a>=m) a-=m;
			b>>=1;
	}
	return res;
}

long long unsigned expmod(long long unsigned a, long long unsigned n, long long unsigned m){
	long long i=n;
	long long res=1LL;
	long long temp =a;
	
	while(i>0LL){
		if(i&1!=0){
			res=mulmod(res, temp, m);			
		}
			temp=mulmod(temp, temp, m);
			i>>=1;
		
	}
	return res;
}

	


void facto(long long n, long long temoin){
	long long power;
	int i=0;
	long long gcd;
	long long temp=temoin;
	long long temp_lisse;
	int j=0;
	int k=1;
	int l;
	long long friabilite=premier[j];
	long long lisse=premier[k];
	
	while(1){
		while(temp<n){
			power=power_premier(n, premier[i]);      // on recupere la plus petite puissance de nombre premier tq premier^power<n
			if(power==0){
				return;
			}
			temp=expmod(temp,expmod(premier[i], power,n),n);           // calcul du temoin^(premier^power) mod n
			gcd=pgcd(temp-1LL ,n);                                     // calcul du pgcd 
			if(gcd!=1LL){
				printf("%llu est un facteur de %llu\n", gcd, n);
				printf("La division de %llu par %llu est %llu\n", n, gcd, (long)n/gcd);
				return;
			}
			for(l=j+1; l<=k; l++){
				temp_lisse=expmod(temp, premier[l], n);
				gcd=pgcd(temp_lisse-1LL,n);
				if(gcd!=1LL){
					printf("%llu est un facteur de %llu\n", gcd, n);
					printf("La division de %llu par %llu est %llu\n", n, gcd, (long)n/gcd);
					return;
				}
			}
			
			j++;
			k=2*k;
			friabilite=premier[j];
			printf("La friabilite a ete augmente a %llu\n", friabilite);
			i++;
		}
	}
	return;
}


int main(){

	long long n;
	long long temoin;
	long long B;
	printf("Entrez un entier a factoriser \n");
	scanf("%llu", &n);
	printf("Entrez un temoin pour le test\n");
	scanf("%llu", &temoin);
//	printf("Entrez la base de friabilite\n");
	//scanf("%llu", &B);
	facto(n, temoin);
	return 0;
}


