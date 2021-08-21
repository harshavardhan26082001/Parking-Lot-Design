#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 15
#define A_MAX 4


//details of car
typedef struct vehicle vehicle_details;
struct vehicle
{
	char wing[MAX];
	int floor_no;
	int flat_no;
	int vehicle_number;
	int vehicle_type;
	char parking_wing[MAX];
	int parking_type;
	int parking_slot;
	struct vehicle *left;
	struct vehicle *right;
};

//details of guest vehicle
typedef struct guest_details guest;
struct guest_details
{
	int vehicle_number;
	int vehicle_type;
	int no_of_visitors;
	char parking_wing[MAX];
	int parking_type;
	int parking_slot;
	char date[MAX];
	char time[MAX];
	struct guest_details *left;
	struct guest_details *right;
};

//making node of vehicle_details
vehicle_details* makenode(char wing[],int floor_no,int flat_no,int vehicle_number,int vehicle_type,char parking_wing[], int parking_type,int parking_slot)
{	vehicle_details* node;
	node = (vehicle_details *)malloc(sizeof(vehicle_details));
	node->vehicle_number = vehicle_number;
	node->vehicle_type = vehicle_type;
	node->flat_no = flat_no;
	node->floor_no = floor_no;
	strcpy(node->wing,wing);
	strcpy(node->parking_wing,parking_wing);
	node->parking_type = parking_type;
	node->parking_slot = parking_slot;
	node->left = NULL;
	node->right = NULL;
	return node;
}

//inserting node into tree
vehicle_details* insert(vehicle_details* root,char wing[],int floor_no,int flat_no,int vehicle_number,int vehicle_type,char parking_wing[],int parking_type,int parking_slot)
{

	vehicle_details *p = root;
	int flag = 0;
	while((p != NULL)&&(flag ==0))
	{
			if(vehicle_number < p->vehicle_number)
		{
			if(p->left != NULL)
			{
					p = p->left;
			}
			else
			{
				p->left = makenode(wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot);
				flag = 1;
			}
		}
		else if(vehicle_number > p->vehicle_number)
		{
			if(p->right != NULL)
			{
					p = p->right;
			}
			else
			{
				p->right = makenode(wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot);
				flag = 1;
			}
		}
		else
		{
		
			flag = 1;
		}
	}
	if((root == NULL)&&(flag == 0))
	{
		root = makenode(wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot);
	}
	return root;
}

//search function
vehicle_details* search(vehicle_details* root, int vehicle_number) 
{ 
    if (root == NULL || root->vehicle_number == vehicle_number) 
    {	
    	if (root != NULL)
    	{	printf("Wing Parking_type Parking_slot\n");
    		printf("%s %d %d\n",root->parking_wing,root->parking_type,root->parking_slot);
    	}
       return root; 
     }
    if (root->vehicle_number < vehicle_number) 
       return search(root->right, vehicle_number); 
  
    return search(root->left, vehicle_number); 
} 
 

//makenodeguest function
guest* makenodeguest(int vehicle_number,int vehicle_type,int no_of_visitors,char parking_wing[],int parking_type,int parking_slot,char date[],char time[])
{	guest *node;
	node = (guest *)malloc(sizeof(guest));
	node->vehicle_number = vehicle_number;
	node->vehicle_type = vehicle_type;
	node->no_of_visitors = no_of_visitors;
	strcpy(node->parking_wing,parking_wing);
	node->parking_slot = parking_slot;
	node->parking_type = parking_type;
	strcpy(node->time,time);
	strcpy(node->date,date);
	node->left = NULL;
	node->right = NULL;
	return node;
}

//insert function of guest
guest* insertguest(guest *node,int vehicle_number,int vehicle_type,int no_of_visitors,char parking_wing[],int parking_type,int parking_slot,char date[],char time[]) 
{	char P[] = "NOT";
	if(strcmp(parking_wing,P)!=0)
 	{	if(node == NULL) return makenodeguest(vehicle_number,vehicle_type,no_of_visitors,parking_wing,parking_type,parking_slot,date,time); 
  
    	if (strcmp(node->date,date)<0)    
        {
        	node->left  = insertguest(node->left, vehicle_number,vehicle_type,no_of_visitors,parking_wing,parking_type,parking_slot,date,time); 
        }
    	else if (strcmp(node->date,date)>0) 
     	{  
     		node->right = insertguest(node->right, vehicle_number,vehicle_type,no_of_visitors,parking_wing,parking_type,parking_slot,date,time);    
  		}
    }
    return node;
}

 guest* searchguest(guest* root,char date[])
 {

 	if ((root == NULL)||strcmp(root->date,date)== 0)
 	{
 		return root;
 	}
 	if (strcmp(root->date,date)<0)
 	{
 		return searchguest(root->left,date);
 	}
 	return searchguest(root->right,date); 

 }

int find(int a1[],int a2[],int a3[],int A1[],int A2[],int A3[],int vehicle_number,int vehicle_type)
{
	int ret_val;
	int found;
	found = 0;
	while(found==0)
	{	
		for (int i = 0; (i < A_MAX)&&(found  == 0); ++i)
		{
			if((vehicle_type == 0)&&(a1[i] == 0))
			{ 
				a1[i] = vehicle_number;
				found = 1;
				ret_val = 10 +i;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a1[i]==0)&&(a1[i+1]==0))
			{
				a1[i]  = vehicle_number;
				a1[i+1] = vehicle_number;
				found = 1;
				ret_val = 10+i;
				
			}
		}
		for (int i = 0;( i < A_MAX)&&(found == 0); ++i)
		{
			if(A1[i] == 0)
			{
				A1[i] = vehicle_number;
				found = 1;
				ret_val = 40+i;
				
			}
		}
		
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if((vehicle_type == 0)&&(a2[i] == 0))
			{
				a2[i] = vehicle_number;
				found = 1;
				ret_val = 20+i;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a2[i]==0)&&(a2[i+1]==0))
			{
				a2[i]  = vehicle_number;
				a2[i+1] = vehicle_number;
				found = 1;
				ret_val = 20 + i;
				
			}
		}
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if(A2[i] == 0)
			{
				A2[i] = vehicle_number;
				found = 1;
				ret_val = 50+i;
				
			}
		}
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if((vehicle_type == 0)&&(a3[i] == 0))
			{
				a3[i] = vehicle_number;
				found = 1;
				ret_val = 30+i;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a3[i]==0)&&(a3[i+1]==0))
			{
				a3[i]  = vehicle_number;
				a3[i+1] = vehicle_number;
				found = 1;
				ret_val = 30+i;
				
			}
		}
		
		for (int i = 0;( i < A_MAX)&&(found == 0); ++i)
		{
			if(A3[i] == 0)
			{
				A3[i] = vehicle_number;
				found = 1;
				ret_val = 60+i;
				
			}
		}
	}
	if(found == 0)
	{
		ret_val = -1;
	}
	return ret_val;
}
int findB(int a1[],int a2[],int a3[],int A1[],int A2[],int A3[],int vehicle_number,int vehicle_type)
{
	int ret_val;
	int found;
	found = 0;
	while(found==0)
	{	
		for (int i = 0; (i < A_MAX)&&(found  == 0); ++i)
		{
			if((vehicle_type == 0)&&(a2[i] == 0))
			{ 
				a2[i] = vehicle_number;
				found = 1;
				ret_val = 20 +i;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a2[i]==0)&&(a2[i+1]==0))
			{
				a2[i]  = vehicle_number;
				a2[i+1] = vehicle_number;
				found = 1;
				ret_val = 20+i;
				
			}
		}
		for (int i = 0;( i < A_MAX)&&(found == 0); ++i)
		{
			if(A2[i] == 0)
			{
				A1[i] = vehicle_number;
				found = 1;
				ret_val = 50+i;
				
			}
		}
		
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if((vehicle_type == 0)&&(a3[i] == 0))
			{
				a3[i] = vehicle_number;
				found = 1;
				ret_val = 30+i;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a3[i]==0)&&(a3[i+1]==0))
			{
				a3[i]  = vehicle_number;
				a3[i+1] = vehicle_number;
				found = 1;
				ret_val = 30 + i;
				
			}
		}
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if(A3[i] == 0)
			{
				A3[i] = vehicle_number;
				found = 1;
				ret_val = 60+i;
				
			}
		}
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if((vehicle_type == 0)&&(a1[i] == 0))
			{
				a1[i] = vehicle_number;
				found = 1;
				ret_val = 10+i;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a1[i]==0)&&(a1[i+1]==0))
			{
				a1[i]  = vehicle_number;
				a1[i+1] = vehicle_number;
				found = 1;
				ret_val = 10+i;
				
			}
		}
		
		for (int i = 0;( i < A_MAX)&&(found == 0); ++i)
		{
			if(A1[i] == 0)
			{
				A1[i] = vehicle_number;
				found = 1;
				ret_val = 40+i;
				
			}
		}
	}
	if(found == 0)
	{
		ret_val = -1;
	}
	return ret_val;
}
int findC(int a1[],int a2[],int a3[],int A1[],int A2[],int A3[],int vehicle_number,int vehicle_type)
{
	int ret_val;
	int found;
	found = 0;
	while(found==0)
	{	
		for (int i = 0; (i < A_MAX)&&(found  == 0); ++i)
		{
			if((vehicle_type == 0)&&(a3[i] == 0))
			{ 
				a3[i] = vehicle_number;
				found = 1;
				ret_val = 30 +i;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a3[i]==0)&&(a3[i+1]==0))
			{
				a3[i]  = vehicle_number;
				a3[i+1] = vehicle_number;
				found = 1;
				ret_val = 30+i;
				
			}
		}
		for (int i = 0;( i < A_MAX)&&(found == 0); ++i)
		{
			if(A3[i] == 0)
			{
				A3[i] = vehicle_number;
				found = 1;
				ret_val = 60+i;
				
			}
		}
		
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if((vehicle_type == 0)&&(a1[i] == 0))
			{
				a1[i] = vehicle_number;
				found = 1;
				ret_val = 10+i;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a1[i]==0)&&(a1[i+1]==0))
			{
				a1[i]  = vehicle_number;
				a1[i+1] = vehicle_number;
				found = 1;
				ret_val = 10 + i;
				
			}
		}
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if(A1[i] == 0)
			{
				A1[i] = vehicle_number;
				found = 1;
				ret_val = 40+i;
				
			}
		}
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if((vehicle_type == 0)&&(a2[i] == 0))
			{
				a2[i] = vehicle_number;
				found = 1;
				ret_val = 20+i;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a2[i]==0)&&(a2[i+1]==0))
			{
				a2[i]  = vehicle_number;
				a2[i+1] = vehicle_number;
				found = 1;
				ret_val = 20+i;
				
			}
		}
		
		for (int i = 0;( i < A_MAX)&&(found == 0); ++i)
		{
			if(A2[i] == 0)
			{
				A2[i] = vehicle_number;
				found = 1;
				ret_val = 50+i;
				
			}
		}
	}
	if(found == 0)
	{
		ret_val = -1;
	}
	return ret_val;
}

//modify the array
void modify(int a1[],int a2[],int a3[],int A1[],int A2[],int A3[],int vehicle_number,int vehicle_type)
{
	int found;
	found = 0;
	while(found==0)
	{	
		for (int i = 0; (i < A_MAX)&&(found  == 0); ++i)
		{
			if((vehicle_type == 0)&&(a1[i] == vehicle_number))
			{ 
				a1[i] = 0;
				found = 1;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a1[i]==vehicle_number)&&(a1[i+1]==vehicle_number))
			{
				a1[i]  = 0;
				a1[i+1] = 0;
				found = 1;
				
			}
		}
		for (int i = 0;( i < A_MAX)&&(found == 0); ++i)
		{
			if(A1[i] == vehicle_number)
			{
				A1[i] = 0;
				found = 1;
				
			}
		}
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if((vehicle_type == 0)&&(a2[i] == vehicle_number))
			{
				a2[i] = 0;
				found = 1;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a2[i]==vehicle_number)&&(a2[i+1]==vehicle_number))
			{
				a2[i]  = 0;
				a2[i+1] = 0;
				found = 1;
				
			}
		}
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if(A2[i] == vehicle_number)
			{
				A2[i] = 0;
				found = 1;
				
			}
		}
		for (int i = 0; (i < A_MAX)&&(found == 0); ++i)
		{
			if((vehicle_type == 0)&&(a3[i] == vehicle_number))
			{
				a3[i] = 0;
				found = 1;
				
			}
		}	
		for(int i = 0; (i <A_MAX-1)&&(found == 0);++i)
		{
			if((vehicle_type == 1)&&(a3[i]==vehicle_number)&&(a3[i+1]==vehicle_number))
			{
				a3[i]  = 0;
				a3[i+1] = 0;
				found = 1;
				
			}
		}
		
		for (int i = 0;( i < A_MAX)&&(found == 0); ++i)
		{
			if(A3[i] == vehicle_number)
			{
				A3[i] = 0;
				found = 1;
			}
		}
	}
}

//printing of array
void print(int a[])
 {
 	for(int i = 0;i <A_MAX ;i++)
 	{
 		printf("%d ",a[i]);
 	}
 }

 void parking_status(int a1[],int a2[],int a3[],int A1[],int A2[],int A3[])
{
	printf("CompactSlots of WingA\n");
	print(a1);
	printf("\n");
	printf("CompactSlots of WingB\n");
	print(a2);
	printf("\n");
	printf("CompactSlots of WingC\n");
	print(a3);
	printf("\n");
	printf("LargeSlots of WingA\n");
	print(A1);
	printf("\n");
	printf("LargeSlots of WingB\n");
	print(A2);
	printf("\n");
	printf("LargeSlots of WingC\n");
	print(A3);
	printf("\n");
}

//minvalue function
vehicle_details* minvaluenode(vehicle_details*allvehicles)
{
	vehicle_details *current;
	current = allvehicles;
	while(current && current->left != NULL)
	{
		current = current->left;
	}
	return current;
}
//remove the vehicle
vehicle_details* delete(vehicle_details *allvehicles,int vehicle_number)
{
	vehicle_details *temp;
	temp = NULL;
	if(allvehicles == NULL)
	{
		return allvehicles;
	}	
	else
	{	
	if(vehicle_number  < allvehicles->vehicle_number)
	{
		allvehicles->left = delete(allvehicles->left,vehicle_number);
	}	
	else if(vehicle_number > allvehicles->vehicle_number)
	{
		allvehicles->right = delete(allvehicles->right,vehicle_number);
	}
	else
	{
		if(allvehicles->left == NULL)
		{
			temp = allvehicles->right;
			free(allvehicles);
			return  temp;
		}
		else if(allvehicles->right == NULL)
		{
			temp = allvehicles->left;
			free(allvehicles);
			return temp;
		}
		else
		{	
			temp = minvaluenode(allvehicles->right);
			allvehicles->vehicle_number = temp->vehicle_number;
			allvehicles->right = delete(allvehicles->right,temp->vehicle_number);
		}
	}
	}
	return allvehicles;
}

//printing details of all vehicles
void printInorder(vehicle_details * root)
{ 

     if (root == NULL)
          return;
     printInorder(root->left);
     printf("%s %d %d %d %d %s %d %d\n",root->wing,root->floor_no,root->flat_no,root->vehicle_number,root->vehicle_type,root->parking_wing,root->parking_type,root->parking_slot);
     printInorder(root->right);
}

//printing details of guest vehicles
void printInorderguest(guest* node)
{
    if (node == NULL)
        return;
    printInorderguest(node->left);     
    printf("%d %d %d %s %d %d %s %s\n",node->vehicle_number,node->vehicle_type,node->no_of_visitors,node->parking_wing,node->parking_type,node->parking_slot,node->date,node->time);      
    printInorderguest(node->right);    
}

int main()
{
	char wing[MAX];
	int floor_no;
	int flat_no;
	int no_of_two_wheelers;
	int no_of_four_wheelers;
	int vehicle_number;
	int vehicle_type;
	char parking_wing[MAX];
	int parking_type;
	int parking_slot;
	int compactA[A_MAX];
	int largeA[A_MAX];
	int compactB[A_MAX];
	int largeB[A_MAX];
	int compactC[A_MAX];
	int largeC[A_MAX];
	int no_of_visitors;
	char date[MAX];
	char time[MAX];
	vehicle_details *allvehicles = NULL;
	vehicle_details *allvehicles1 = NULL;
	guest *allguests;
	allguests = NULL;
	FILE *fp;
	int x;
	fp = fopen("C:\\Users\\Harsha\\Desktop\\data1.txt","r");

  	while(x != -1)
	{
		x = fscanf(fp,"%s %d %d %d %d  %s %d %d",wing,&floor_no,&flat_no,&vehicle_number,&vehicle_type,parking_wing,&parking_type,&parking_slot);
		allvehicles = insert(allvehicles,wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot);
	}
	fclose(fp);
	x = 0;
	fp = fopen("C:\\Users\\Harsha\\Desktop\\data2.txt","r");
	while(x != -1)
	{
		x = fscanf(fp,"%d %d %d %d %d %d %d %d",&compactA[0],&compactA[1],&compactA[2],&compactA[3],&largeA[0],&largeA[1],&largeA[2],&largeA[3]);
	}	
	fclose(fp);
	x = 0;
	fp = fopen("C:\\Users\\Harsha\\Desktop\\data3.txt","r");
	while(x != -1)
	{
		x = fscanf(fp,"%d %d %d %d %d %d %d %d",&compactB[0],&compactB[1],&compactB[2],&compactB[3],&largeB[0],&largeB[1],&largeB[2],&largeB[3]);
	}	
	fclose(fp);
	x = 0;
	fp = fopen("C:\\Users\\Harsha\\Desktop\\data4.txt","r");
	while(x != -1)
	{
		x = fscanf(fp,"%d %d %d %d %d %d %d %d",&compactC[0],&compactC[1],&compactC[2],&compactC[3],&largeC[0],&largeC[1],&largeC[2],&largeC[3]);
	}	
	fclose(fp);
	x = 0;
	fp = fopen("C:\\Users\\Harsha\\Desktop\\data5.txt","r");
	while(x != -1)
	{
			x = fscanf(fp,"%d %d %d %s %s",&vehicle_number,&vehicle_type,&no_of_visitors,date,time);	
			if(x != -1)
			{
			int f ;
			f = find(compactA,compactB,compactC,largeA,largeB,largeC,vehicle_number,vehicle_type);
			int r ,q;
			r = f%10;
			q = f/10;
			parking_type = 0;
			parking_slot = r;
			if((q == 1)||(q == 4))
			{
				char A[] = "A";
				strcpy(parking_wing,A);
				if(q == 4)
				{
					parking_type = 1;
				}
			}
			else if((q == 2)||(q == 5))
			{
				char B[] = "B";
				strcpy(parking_wing,B);
				if(q == 5)
				{
					parking_type = 1;
				}
			}
			else if((q == 3)||(q == 6))
			{
				char C[] = "C";
				strcpy(parking_wing,C);
				if(q == 6)
				{
					parking_type = 1;
				}
			}
			else
			{
				char D[] = "NOT";
				strcpy(parking_wing ,D);
			}
			allguests = insertguest(allguests,vehicle_number,vehicle_type,no_of_visitors,parking_wing,parking_type,parking_slot,date,time);
			modify(compactA,compactB,compactC,largeA,largeB,largeC,vehicle_number,vehicle_type);
			}
	}
	fclose(fp);
	
	printf("------------WELCOME-------------\n");
	int choice;
	int flag = 0;
	while(flag == 0)
	{
	printf("1.Add a vehicle\n");
	printf("2.Park vehicle\n");
	printf("3.Remove vehicle\n");
	printf("4.Display visitors\n");
	printf("5.parking_status\n");
	printf("0.To exit\n");
	printf("Enter your choice..\n");
	scanf("%d",&choice);
	if(choice == 1)
	{
		printf("Enter details in the order\n");
		printf("wing,floor_no,flat_no,vehicle_number,vehicle_type\n");
		scanf("%s %d %d %d %d",wing,&floor_no,&flat_no,&vehicle_number,&vehicle_type);
			if (strcmp(wing,"A")==0)
			{
			int f ;
			f = find(compactA,compactB,compactC,largeA,largeB,largeC,vehicle_number,vehicle_type);
			int r ,q;
			r = f%10;
			q = f/10;
			parking_type = 0;
			parking_slot = r;
			if((q == 1)||(q == 4))
			{
				char A[] = "A";
				strcpy(parking_wing,A);
				if((vehicle_type==1)&&(q == 1))
				{
					compactA[r]=vehicle_number;
					compactA[r+1]= vehicle_number;
				}
				if ((vehicle_type==0)&&(q==1))
				{	compactA[r]=vehicle_number;
				}	
				if(q == 4)
				{
					parking_type = 1;
					largeA[r]=vehicle_number;
				}
			}
			else if((q == 2)||(q == 5))
			{
				char B[] = "B";
				strcpy(parking_wing,B);
				if((vehicle_type==1)&&(q==2))
				{
					compactB[r]=vehicle_number;
					compactB[r+1]= vehicle_number;
				}
				if ((vehicle_type==0)&&(q==2))
				{
					compactB[r]=vehicle_number;
				}
				if(q == 5)
				{
					largeB[r]= vehicle_number;
					parking_type = 1;
				}
			}
			else if((q == 3)||(q == 6))
			{
				char C[] = "C";
				strcpy(parking_wing,C);
				if((vehicle_type==1)&&(q==3))
				{
					compactC[r]=vehicle_number;
					compactC[r+1]= vehicle_number;
				}
				if ((vehicle_type==0)&&(q==3))
				{
					compactC[r]= vehicle_number;
				}
				if(q == 6)
				{
					largeC[r]=vehicle_number;
					parking_type = 1;
				}
			}
			else
			{
				char D[] = "NOT";
				strcpy(parking_wing ,D);
				printf("Cannot find a parking slot\n");
			}
			allvehicles = insert(allvehicles,wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot);
			printf("wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot\n");
			printInorder(allvehicles);	
			}
			else if (strcmp(wing,"B")==0)
			{
				int f ;
			f = findB(compactA,compactB,compactC,largeA,largeB,largeC,vehicle_number,vehicle_type);
			int r ,q;
			r = f%10;
			q = f/10;
			parking_type = 0;
			parking_slot = r;
			if((q == 1)||(q == 4))
			{
				char A[] = "A";
				strcpy(parking_wing,A);
				if((vehicle_type==1)&&(q == 1))
				{
					compactA[r]=vehicle_number;
					compactA[r+1]= vehicle_number;
				}
				if ((vehicle_type==0)&&(q==1))
				{	compactA[r]=vehicle_number;
				}	
				if(q == 4)
				{
					parking_type = 1;
					largeA[r]=vehicle_number;
				}
			}
			else if((q == 2)||(q == 5))
			{
				char B[] = "B";
				strcpy(parking_wing,B);
				if((vehicle_type==1)&&(q==2))
				{
					compactB[r]=vehicle_number;
					compactB[r+1]= vehicle_number;
				}
				if ((vehicle_type==0)&&(q==2))
				{
					compactB[r]=vehicle_number;
				}
				if(q == 5)
				{
					largeB[r]= vehicle_number;
					parking_type = 1;
				}
			}
			else if((q == 3)||(q == 6))
			{
				char C[] = "C";
				strcpy(parking_wing,C);
				if((vehicle_type==1)&&(q==3))
				{
					compactC[r]=vehicle_number;
					compactC[r+1]= vehicle_number;
				}
				if ((vehicle_type==0)&&(q==3))
				{
					compactC[r]= vehicle_number;
				}
				if(q == 6)
				{
					largeC[r]=vehicle_number;
					parking_type = 1;
				}
			}
			else
			{
				char D[] = "NOT";
				strcpy(parking_wing ,D);
				printf("Cannot find a parking slot\n");
			}
			allvehicles = insert(allvehicles,wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot);
			printf("wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot\n");
			printInorder(allvehicles);	
			}	
			else if (strcmp(wing,"C")==0)
			{
				int f ;
			f = findC(compactA,compactB,compactC,largeA,largeB,largeC,vehicle_number,vehicle_type);
			int r ,q;
			r = f%10;
			q = f/10;
			parking_type = 0;
			parking_slot = r;
			if((q == 1)||(q == 4))
			{
				char A[] = "A";
				strcpy(parking_wing,A);
				if((vehicle_type==1)&&(q == 1))
				{
					compactA[r]=vehicle_number;
					compactA[r+1]= vehicle_number;
				}
				if ((vehicle_type==0)&&(q==1))
				{	compactA[r]=vehicle_number;
				}	
				if(q == 4)
				{
					parking_type = 1;
					largeA[r]=vehicle_number;
				}
			}
			else if((q == 2)||(q == 5))
			{
				char B[] = "B";
				strcpy(parking_wing,B);
				if((vehicle_type==1)&&(q==2))
				{
					compactB[r]=vehicle_number;
					compactB[r+1]= vehicle_number;
				}
				if ((vehicle_type==0)&&(q==2))
				{
					compactB[r]=vehicle_number;
				}
				if(q == 5)
				{
					largeB[r]= vehicle_number;
					parking_type = 1;
				}
			}
			else if((q == 3)||(q == 6))
			{
				char C[] = "C";
				strcpy(parking_wing,C);
				if((vehicle_type==1)&&(q==3))
				{
					compactC[r]=vehicle_number;
					compactC[r+1]= vehicle_number;
				}
				if ((vehicle_type==0)&&(q==3))
				{
					compactC[r]= vehicle_number;
				}
				if(q == 6)
				{
					largeC[r]=vehicle_number;
					parking_type = 1;
				}
			}
			else
			{
				char D[] = "NOT";
				strcpy(parking_wing ,D);
				printf("Cannot find a parking slot\n");
			}
			allvehicles = insert(allvehicles,wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot);
			printf("wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot\n");
			printInorder(allvehicles);	
			}	
	}
	else if(choice == 2)
	{
		printf("Enter the vehicle_number\n");
		scanf("%d",&vehicle_number);
		allvehicles1 = search(allvehicles,vehicle_number);
		if(allvehicles1 == NULL)
		{
			printf("Futher details are needed to park you as guest\n");
			printf("Enter vehicle_type,no_of_visitors,date,time\n");
			scanf("%d %d %s %s",&vehicle_type,&no_of_visitors,date,time);
			int f ;
			f = find(compactA,compactB,compactC,largeA,largeB,largeC,vehicle_number,vehicle_type);
			int r ,q;
			r = f%10;
			q = f/10;
			parking_type = 0;
			parking_slot = r;
			if((q == 1)||(q == 4))
			{
				char A[] = "A";
				strcpy(parking_wing,A);
				if(q == 4)
				{
					parking_type = 1;
				}
			}
			else if((q == 2)||(q == 5))
			{
				char B[] = "B";
				strcpy(parking_wing,B);
				if(q == 5)
				{
					parking_type = 1;
				}
			}
			else if((q == 3)||(q == 6))
			{
				char C[] = "C";
				strcpy(parking_wing,C);
				if(q == 6)
				{
					parking_type = 1;
				}
			}
			else
			{
				char D[] = "NOT";
				strcpy(parking_wing ,D);
			}
			allguests = insertguest(allguests,vehicle_number,vehicle_type,no_of_visitors,parking_wing,parking_type,parking_slot,date,time);
			printf("vehicle_number,vehicle_type,no_of_visitors,parking_wing,parking_type,parking_slot,date,time\n");
			printInorderguest(allguests);
			modify(compactA,compactB,compactC,largeA,largeB,largeC,vehicle_number,vehicle_type);
		}

	}
	else if(choice == 3)
	{	printf("wing,floor_no,flat_no,vehicle_number,vehicle_type,parking_wing,parking_type,parking_slot\n");
		printInorder(allvehicles);
		printf("Enter the vehicle number and vehicle type you want to remove\n");
		scanf("%d %d",&vehicle_number,&vehicle_type);
		allvehicles = delete(allvehicles,vehicle_number);
		modify(compactA,compactB,compactC,largeA,largeB,largeC,vehicle_number,vehicle_type);
		parking_status(compactA,compactB,compactC,largeA,largeB,largeC);
	}
	else if (choice == 4)
	{	printf("vehicle_number,vehicle_type,no_of_visitors,parking_wing,parking_type,parking_slot,date,time\n");
		printInorderguest(allguests);
		printf("Enter the date to search the guests\n");
		scanf("%s",date);
		guest *allguests1;
		allguests1 = searchguest(allguests,date);
		if (allguests1 != NULL)
		{
		printf("%d %d %d %s %d %d %s %s\n",allguests1->vehicle_number,allguests1->vehicle_type,allguests1->no_of_visitors,allguests1->parking_wing,allguests1->parking_type,allguests1->parking_slot,allguests1->date,allguests1->time );
		}
		else
		{
			printf("No guests on that particular date\n");
		}
	}

	else if(choice == 5)
	{
		parking_status(compactA,compactB,compactC,largeA,largeB,largeC);
	}
	else if (choice == 0)
	{
		flag = 1;
	}
	else
	{
		printf("enter a valid choice\n");
	}
	}
	return 0;
}
