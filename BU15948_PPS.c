#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


#define FILE_NAME "D:\\BU15948_stocks.csv"
void crt();
void add(){
	char id[10], name[100];
	int quantity, price;
	printf("Enter Product id :");
	scanf("%s", &id);
	printf("Enter Name :"); 
	scanf("%s", &name);
	printf("Enter Quantity :");
	scanf("%d", &quantity);
	printf("Enter Price :");
	scanf("%d", &price);
	
	FILE* fp = fopen(FILE_NAME, "a+");
	
	fprintf(fp, "%s, %s, %d, %d\n", id, name, quantity, price);
	fclose(fp);
}

void read(int *qn, int *pr, char *pd_nm, char *pd_id)
{
        FILE* fp = fopen(FILE_NAME, "r"); 
        char buffer[1024], Prod_name[100][100] = {'\0'}, Prod_id[100][100] = {'\0'}, Qun[100][5], Pri[100][5];
        int i, j, k;
        
        int row = 0;
        int column = 0;
  
        while (fgets(buffer,1024, fp)) {
            column = 0;
            row++;
  
            if (row == 1)
                continue;

            char* value = strtok(buffer, ",");
            while(value){
            	char buf1[100];
            	if(column == 0){
            		strcpy(Prod_id[row-2], value);
				}
				if(column == 1)
					strcpy(Prod_name[row-2], value);
				
				if(column == 2)
					strcpy(Qun[row-2], value);
					
				if(column == 3)
					strcpy(Pri[row-2], value);
					
            	value = strtok(NULL, ", ");
            	column++;
			}column++;
		}
		
    	fclose(fp);
    	
    	char *pd_nm_buf = Prod_name;
		char *pd_nm_buf1 = Prod_id ;

    	for(i=0; i<row-1; i++){
    		//puts(Qun[i]);
    		*qn = atoi(Qun[i]);
    		qn++;
    		*pr = atoi(Pri[i]);
    		pr++;
		}
		int a = (row-1)*100;
		while( a-- ){
			*pd_nm++ = *pd_nm_buf++;
		}
		a = (row-1)*100;
		while( a-- )
			*pd_id++ = *pd_nm_buf1++;
	
	fclose(fp);
}

void edit(int ind){
	int Qun[10] = {0}, Price[10] = {0}, i=0;
	char Prod_name[100][100] = {'\0'}, Prod_id[100][100] = {'\0'};
	read(Qun, Price, Prod_name, Prod_id);
	
	Qun[ind]--;
	
	FILE* fp = fopen(FILE_NAME, "w");
	
	fprintf(fp, "Prod_id, Prod_name, Qun, Price\n");
	
	for(i=0; i<100; i++){
		if(Qun[i] == 0)
			break;
		fprintf(fp, "%s, %s, %d, %d\n", Prod_id[i], Prod_name[i], Qun[i], Price[i]);
	}
	fclose(fp);
}

void Bill(){
	
	system("cls");
	printf("\t\t\tSTOCK_MANAGEMENT_AND_BILLING \n\t\t\t\tBU15948 \n\n");
	
	char a[10];
	gets(a);
	
	char id[10][100] = {'\0'}, Prod_name[100][100] = {'\0'}, Prod_id[100][100] = {'\0'};
	int row = 0, Quan[100] = {0}, Price[100] = {0}, i,j ,ind[100] = {-1};
	int *ptr_ind = ind;
	for(i=0; i<100; i++)
		ind[i] = -1;
	read(Quan, Price, Prod_name, Prod_id);
	
	while(1){
		char buf[100];
		printf("Enter Product id : ");
		gets(buf);
		if(buf[0] == '\0'){
			printf("EXIT");
			break;
		}
		
		for(i=0; i<100; i++){
			if(strcmp(Prod_id[i], buf)==0){
				printf("ok\n");
				*ptr_ind = i;
				ptr_ind++;
				
			}
		}
	}
	system("cls");
	
	int k=0, tot=0;
	printf("\t\t SHOP NAME \n\n");
	printf("%10s  %10s  %10s  %s", "Prod_ID", "| Prod_name", "| Quantity", "| Price\n");
	while(ind[k] != -1){
		printf("%10s  %10s  %10d  %10d\n", Prod_id[ind[k]], Prod_name[ind[k]], 1, Price[ind[k]] );
		tot += Price[ind[k]];
		edit(ind[k]);
		k++;
	}
	printf("\tTotal Price = %d\n", tot);
	printf("\tPAID ? (yes/no):\n");
	char d = '\0';
	while(1){
		scanf("%c", &d);
		if(d == 'y'){
			system("cls");
			break;
		}
	}
	system("cls");
	printf("Continue (yes/no) ? ");
	char C = getch();
	if(C == 'y'){
		system("cls");
		Bill();
	}
}

void crt(){
	int Qun[100] = {0}, Price[100] = {0}, i;
	char Prod_name[100][100] = {'\0'}, Prod_id[100][100];
	read(Qun, Price, Prod_name, Prod_id);
	
	FILE* fp = fopen(FILE_NAME, "w");
	fprintf(fp, "%s, %s, %s, %s\n", "Prod_id", "Prod_name", "Quantity", "Price");
	
	for(i=0; i<100; i++){
		if(Qun[i] == 0)
			continue;
			
		fprintf(fp, "%s, %s, %d, %d\n", Prod_id[i], Prod_name[i], Qun[i], Price[i]);
	}
	fclose(fp); 
}

void Dis(){
	
	printf(" LeftOut Stocks : \n");
	int Qun[100] = {0}, Price[100] = {0}, i;
	char Prod_name[100][100] = {'\0'}, Prod_id[100][100];
	read(Qun, Price, Prod_name, Prod_id);
	
	printf("%10s  %10s  %10s  %s", "Prod_ID", "| Prod_name", "| Quantity", "| Price\n");
	int k=0;
	while(Qun[k] != 0){
		printf("%10s  %10s  %10d  %10d\n", Prod_id[k], Prod_name[k], Qun[k], Price[k] );
		k++;
	}
	getch();
}

int main(){
	int m;
	
	while(1){
	system("cls");
	crt();
	printf("\t\t\tSTOCK_MANAGEMENT_AND_BILLING \n\t\t\t\tBU15948 ");
	printf("\n\tMENU\n 1.BILLING\n 2.ADD STOCKS\n 3.VIEW STOCKS\n 4.EXIT\n");
	scanf("%d", &m);
	if(m == 2){
		system("cls");
		printf("\t\t\tSTOCK_MANAGEMENT_AND_BILLING \n\t\t\t\tBU15948 \n\n");
		add();
	}
	else if(m == 1){
		
		Bill();
	}
	else if(m == 3){
		system("cls");
		printf("\t\t\tSTOCK_MANAGEMENT_AND_BILLING \n\t\t\t\tBU15948 \n\n");
		Dis();
	}
	else
		break;
}
	return 0;
}







