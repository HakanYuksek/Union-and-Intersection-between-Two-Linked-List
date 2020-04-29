#include <stdio.h>
#include <stdlib.h>


struct list{
	int value;
	struct list *next;
};

void oku(struct list*,int);
void ekle(struct list*,int);
void goster(struct list*);
struct list* kesisim(struct list*,struct list*);
struct list* birlesim(struct list*,struct list*);


int main(){
	struct list *A,*B;//A ve B dizileri
	struct list *C,*D;//C=KESÝSÝM DÝZÝSÝ,D ÝSE BÝRLESÝM DÝZÝSÝ
	int val,i;
	int sizeA,sizeB;//A ve B dizilerinin boyutlarýný tutacaklar
	A=(struct list*)malloc(sizeof(struct list));
	B=(struct list*)malloc(sizeof(struct list));
	A->next=NULL;
	B->next=NULL;
	printf("DIKKAT!!!\n");
	printf("A ve B dizileri kullanici tarafindan sirali bir sekilde girilmelidir...\n");
	printf("C dizisi kesisim D dizisi ise birlesim dizileridir...\n");
	printf("A dizisinin boyutu:");
	scanf("%d",&sizeA);
	printf("sizden oncelikle A dizisinin elemanlarini girmeniz isteniyor\n");
	printf("1 inci eleman:");
	scanf("%d",&val);	
	A->value=val;
	oku(A,sizeA);// A dizisinin elemanlari okundu
	printf("B dizisinin boyutunu giriniz:");
	scanf("%d",&sizeB);
	printf("\n");
	printf("simdide B dizisinin elemanlarini giriniz:\n");
	printf("1 inci eleman:");
	scanf("%d",&val);
	B->value=val;
	oku(B,sizeB);//B dizisinin elemanlari okundu
	printf("A dizisi:\t");
	goster(A);
	printf("B dizisi:\t");
	goster(B);
	printf("C dizisi:\t");
	if(sizeA<=sizeB){//hangisinin eleman sayisi kucukse onun elemanlarini tek tek digerinde aramaliyiz
		C=kesisim(A,B);
	}else{
		C=kesisim(B,A);
	}
	goster(C);	
	D=birlesim(A,B);
	printf("D dizisi:\t");
	goster(D);
	//kullanilan kaynaklari serbest birakma vakti
	free(A);
	free(B);
	free(C);
	free(D);
	getch();
	return 0;
}

void oku(struct list *A,int size){//bu fonksiyon kendisine gonderilen dizinin elemanlarini okur
	int i,val;
	for(i=1;i<size;i++){
		printf("%d inci eleman:",i+1);
		scanf("%d",&val);
		ekle(A,val);
	}
	
}

void ekle(struct list *head,int v){//head ve bir deger alir ve alinan degerin adresini linkli listeye ekleriz
	
	struct list *tmp;
	tmp=(struct list*)malloc(sizeof(struct list));
	if(tmp==NULL){
		printf("yetersiz bellek!\n");
		exit(0);
	}
	tmp=head;//head in degeri bozulmasin diye tmp gecici degiskenini kullandim
	while(tmp->next!=NULL){
		tmp=tmp->next;
	}//son elemani bulduk
	tmp->next=(struct list*)malloc(sizeof(struct list));//son eleman null i gosteriyordu,bu yuzden malloc ile dinamik hafiza da yer actik
	if(tmp->next==NULL){
		printf("yetersiz bellek!\n");
		exit(0);
	}
	tmp->next->value=v;//ve yeni degerimizi linkli listeye ekledik
	tmp->next->next=NULL;//artik sona yeni bir eleman ekledigimiz icin son elemanimiz yeni ekledigimiz eleman oldu,bu yuzden kendisinden sonra null gelmeli

}
void goster(struct list* head){//kendisine gonderilen head e gore linkli listeyi ekrana yazdiran fonksiyon
	struct list *tmp;
	tmp=(struct list*)malloc(sizeof(struct list));
	if(tmp==NULL){
		printf("yetersiz bellek!\n");
		exit(0);
	}
	tmp=head;
	while(tmp!=NULL){
		printf("%d\t",tmp->value);
		tmp=tmp->next;
	}
	printf("\n");
}

struct list *kesisim(struct list *A,struct list *B){
	struct list *C,*t1,*t2;
	int k=0;//C dizisinin ilk elemani olup olmadigini kontrol ederiz
	C=(struct list*)malloc(sizeof(struct list));
	t1=A;
	C->next=NULL;
	while(t1!=NULL){//A dizisini son elemani bitene kadar , her bir elemani B nin elemanlari ile kiyaslanmali
		t2=B;
		while(t2->next!=NULL && t1->value>t2->value){//eger A nin elemani B nin herhangi bir elemanindan kucukse donguden cikilmali cunku diziler
			t2=t2->next;			//kucukten buyuge sirali ve A nin elemaninin burada olmadigi anlasilir
		}
		
		if(t2->value==t1->value){//donguden esitlik durumundan dolayi mi cikildigi kontrol edilir
			if(k==0){//eger k==0 sa C nin simdiye kadar elemani yok demektir bu yuzden bir tane head eklememiz lazim
				C->value=t1->value;
				k=1;
			}else{
				ekle(C,t1->value);//C nin zaten bir head i var ve bunu ekle fonksiyonu cagirilarak yeni elemani sona ekleriz
			}
		}

		t1=t1->next;
	}
	return C;
}
struct list* birlesim(struct list *A,struct list *B){
	struct list *D,*t1,*t2;
	D=(struct list*)malloc(sizeof(struct list));
	D->next=NULL;
	t1=A;
	t2=B;
	if(t1->value>t2->value){//birlesim dizisinin ilk elemanini belirlemek icin yapilan kontrol
		D->value=t2->value;
		t2=t2->next;
	}else if(t1->value<t2->value){
		D->value=t1->value;
		t1=t1->next;
	}else{//eger esitse bir tanesini yeni diziye eklemek yeterli,ikisi ayni anda eklenmemeli 
		D->value=t1->value;
		t1=t1->next;
		t2=t2->next;
	}
	while(t2!=NULL && t1!=NULL){//iki dizinin her seferinde en kucuk elemanlarini bulup sirali sekilde D dizisine ekleyelim
		if(t1->value>t2->value){
			ekle(D,t2->value);
			t2=t2->next;
		}else if(t1->value<t2->value){
			ekle(D,t1->value);
			t1=t1->next;
		}else{
			ekle(D,t1->value);
			t1=t1->next;
			t2=t2->next;
		}
		
	}
	if(t1!=NULL || t2!=NULL){//eger iki dizinin boyutlari esit degilse,bir tanesinin hala yeni diziye eklenmemis elemanlari var demektir
							//Bu yuzden hangisi oldugunu bulup geriye kalan elemanlarini yeni dizinin sonuna eklemeliyiz
		if(t2==NULL){
			while(t1!=NULL){
				ekle(D,t1->value);
				t1=t1->next;
			}
		}else if(t1==NULL){
			while(t2!=NULL){
				ekle(D,t2->value);
				t2=t2->next;
			}
		
		}
	}
	
	return D;
	
	
}



