//Final Project(Food delivery system)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *fp1,*fp2;
struct item{
	int item_id;
	char item_nm[200],des[200];
	float price;	
}itm;
struct customer{
	char nm[50],addr[200],pass[50],phno[20];	
}cust;
struct order{
	char phno[20];
	int item_id,no_of_item,status;
}ord;
void viewitems();
void cancel_cust_order(char phno1[])
{
	int itid1,f=0;
	printf("\nEnter item id to cancel:");
	fflush(stdin);
	scanf("%d",&itid1);
	fp1=fopen("order.dat","r");
	fp2=fopen("order1.dat","a");
	 while(fread((char*)&ord,sizeof(ord),1,fp1))
	 {
	 	if(strcmp(ord.phno,phno1)==0)
	 	{
		 
	 		if(ord.item_id==itid1 && ord.status==0)
	 		{
	 			ord.status=2;
	 			f=1;
		 	}
	     }
		 fwrite((char*)&ord,sizeof(ord),1,fp2);
	 }
	 fclose(fp1);
	 fclose(fp2);
	 remove("order.dat");
	 rename("order1.dat","order.dat");
	 if(f==1)
	   printf("Order canceled successfully");
	 else
	    printf("Ordered can not canceled");
}
void view_cust_order(char phno1[])
{
    fp1=fopen("order.dat","r");
    char status1[20];
	while(fread((char*)&ord,sizeof(ord),1,fp1))
	{
	      if(strcmp(ord.phno,phno1)==0)	
	      {
	      	if(ord.status==0)
	      	strcpy(status1,"unprocessed");
	      	else if(ord.status==1)
	      	strcpy(status1,"processed");
	      	else if(ord.status==2)
	      	strcpy(status1,"canceled");
	      	printf("\n%d\t%d\t%s",ord.item_id,ord.no_of_item,status1);
		  }
	}	
	fclose(fp1);
}
void process_order()
{
	char phno1[20];
	int itid1;
	printf("Enter phno:");
	fflush(stdin);
	gets(phno1);
	printf("\nEnter itemid:");
	fflush(stdin);
	scanf("%d",&itid1);
	fp1=fopen("order.dat","r");
	fp2=fopen("order1.dat","a");
	while(fread((char*)&ord,sizeof(ord),1,fp1))
	{
		if(strcmp(ord.phno,phno1)==0 && ord.item_id==itid1)
		{
			ord.status=1;
		}
		fwrite((char*)&ord,sizeof(ord),1,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	remove("order.dat");
	rename("order1.dat","order.dat");
	printf("\nItem processed successfully");
}
void view_order()
{
	fp1=fopen("order.dat","r");
	while(fread((char*)&ord,sizeof(ord),1,fp1))
	{
		if(ord.status==0)
		{
			printf("\n%s\t%d\t%d",ord.phno,ord.item_id,ord.no_of_item);
		}
	}
    fclose(fp1);
}
void cust_order(char phno[])
{
	char ch;
	float tot_price=0;
	viewitems();
	fp1=fopen("order.dat","a");
	do{
	strcpy(ord.phno,phno);
	printf("\nEnter itemid:");
	fflush(stdin);
	scanf("%d",&ord.item_id);
	printf("\nEnter enter no of items:");
	fflush(stdin);
	scanf("%d",&ord.no_of_item);
	ord.status=0;
	fwrite((char*)&ord,sizeof(ord),1,fp1);
	
	fp2=fopen("item.dat","r");
	while(fread((char*)&itm,sizeof(itm),1,fp2))
	{
		if(itm.item_id==ord.item_id)
		{
			tot_price=tot_price+ord.no_of_item*itm.price;
		}
	}
	fclose(fp2);
	printf("\nTotal Price %.2f",tot_price);
	printf("\nDo you want to order another item(y/n):");
	fflush(stdin);
	scanf("%c",&ch);
     }while(ch=='y');
	fclose(fp1);
}
void cust_menu(char phno[],char nm[])
{
	int ch;
	while(1)
	{
		printf("\nWelcome %s",nm);
		printf("\n1 for order \n2 view order\n3 for cancel\n4 for exit");
		printf("\nEnter your choice");
		fflush(stdin);
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:cust_order(phno);break;
			case 2:view_cust_order(phno);break;
			case 3:cancel_cust_order(phno);break;
			case 4:exit(0);
		}
		
	}
}
void cust_login()
{
	int f=0;
	char phno1[20],pass1[50];
	printf("\nEnter phno:");
	fflush(stdin);
	gets(phno1);
	printf("\nEnter password:");
	fflush(stdin);
	gets(pass1);
	fp1=fopen("cust.dat","r");
	while(fread((char*)&cust,sizeof(cust),1,fp1))
	{
		if(strcmp(cust.phno,phno1)==0 && strcmp(cust.pass,pass1)==0)
		 {
		 	f=1;break;
		 }
	}
	if(f==1)
	  cust_menu(phno1,cust.nm);
	else
	  printf("\nInvalid phno or password");
	
}
void cust_registration()
{
	printf("\nEnter phno:");
	fflush(stdin);
	gets(cust.phno);
	printf("\nEnter name:");
	fflush(stdin);
	gets(cust.nm);
	printf("\nEnter address");
	fflush(stdin);
	gets(cust.addr);
	printf("\nEnter password:");
	fflush(stdin);
	gets(cust.pass);
	fp1=fopen("cust.dat","a");
	fwrite((char*)&cust,sizeof(cust),1,fp1);
	fclose(fp1);
	printf("\nRegistration successfully");
}
void cust_initial_menu()
{
	int ch;
	while(1)
	{
		printf("\n1 for login\n2 for registration \n0 for exit");
		printf("\nEnter your choice:");
		fflush(stdin);
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:cust_login();break;
			case 2:cust_registration();break;
			case 0:exit(0);
		}
	}
}
void modifyitem()
{
	int itid,ch;
	printf("\nEnter itemid to modify:");
	fflush(stdin);
	scanf("%d",&itid);
	fp1=fopen("item.dat","r");
	fp2=fopen("item1.dat","a");
	while(fread((char*)&itm,sizeof(itm),1,fp1))
	{
		if(itm.item_id==itid)
		{
			printf("1 for change item name\n2 for change description");
			printf("\n3 for price\n enter your choice");
			scanf("%d",&ch);
			switch(ch)
			{
			case 1:
				printf("\nEnter item name:");
				fflush(stdin);
				gets(itm.item_nm);
				break;
			case 2:
				printf("\nEnter description");
				fflush(stdin);
				gets(itm.des);
				break;
			case 3:
				printf("\nEnter price");
				fflush(stdin);
				scanf("%f",&itm.price);
				break;
		  }
		}
		fwrite((char*)&itm,sizeof(itm),1,fp2);
		
	}
	fclose(fp1);
	fclose(fp2);
	remove("item.dat");
	rename("item1.dat","item.dat");
	printf("\nItem modified successfully");

}
void delitem()
{
	int itid;
	printf("Enter item id to delete:");
	fflush(stdin);
	scanf("%d",&itid);
	fp1=fopen("item.dat","r");
	fp2=fopen("item1.dat","a");
	while(fread((char*)&itm,sizeof(itm),1,fp1))
	{
		if(itm.item_id!=itid)
		{
		     fwrite((char*)&itm,sizeof(itm),1,fp2);	
		}
	}
	fclose(fp1);
	fclose(fp2);
	remove("item.dat");
	rename("item1.dat","item.dat");
	printf("Item deleted successfully");
	
}
void viewitems()
{
	fp1=fopen("item.dat","r");
	while(fread((char*)&itm,sizeof(itm),1,fp1))	
	{
		printf("\n%d\t%s\t%s\t%.2f",itm.item_id,itm.item_nm,itm.des,itm.price);
		
	}
	fclose(fp1);
}
void additem()
{
	printf("Enter item id:");
	fflush(stdin);
	scanf("%d",&itm.item_id);
	printf("Enter Item Name:");
	fflush(stdin);
	gets(itm.item_nm);
	printf("Enter Item description:");
	fflush(stdin);
	gets(itm.des);
	printf("Enter price:");
	fflush(stdin);
	scanf("%f",&itm.price);
	fp1=fopen("item.dat","a");
	fwrite((char*)&itm,sizeof(itm),1,fp1);//write into a file
	printf("\nItem added successfully\n");
	fclose(fp1);
	
}
void adminmenu()
{
	int ch;
	while(1){
		printf("\n1 for Add Item:");
		printf("\n2 for view items");
		printf("\n3 for del item:");
		printf("\n4 for modify item: ");
		printf("\n5 view unprocessed order:");
		printf("\n6 order processed");
		printf("\n0 for exit");
		printf("\nEnter your choice:");
		fflush(stdin);
		scanf("%d",&ch);
		switch(ch){
			case 1:additem();break;
			case 2:viewitems();break;
			case 3:delitem();break;
			case 4:modifyitem();break;
			case 5:view_order();break;
			case 6:process_order();break;
			case 0:exit(0);
		}
				
	}
}

void admin_validate()
{
	char uid[100],pass[100];
	printf("\nEnter userid:");
	fflush(stdin);
	gets(uid);
	printf("\nEnter password:");
	gets(pass);
	if(strcmp(uid,"admin123")==0 && strcmp(pass,"123456")==0)
	{
		printf("\nWelcome Admin:");
		adminmenu();
	}
	else
	  printf("Try again");
	
}

main()
{
	int ch;
	while(1)
	{
		printf("\n\n==FOOD DEL  SYSTEM==\n");
		printf("\n1 for admin");
		printf("\n2 for Customer");
		printf("\n3 for exit");
		printf("\nEnter your choice:");
		fflush(stdin);
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:admin_validate();break;
			case 2:cust_initial_menu();break;
			case 3:exit(0);
		}
	}
}
