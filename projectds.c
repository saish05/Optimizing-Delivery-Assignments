#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
struct node 
{
	float x,y;
	int orders;
	struct node * link;
};
struct header 
{
	struct header * down;
	struct node * next;
	char name[50];
	int trips,id;
	float loc1,loc2;
};
void *maiin();
void *location();
void display(struct header *,int);
float * find_dis(struct header * headd);
struct header * deletion(struct header *headd);
struct header * deletion_1(struct header **,int);
struct header * status(int,int,struct header *);
struct header * search(int,struct header *,struct header **);
struct header * creation(int num,struct header **,struct header **);
struct header * deletion(struct header *headd);
struct node * insertion(float,float,struct header *);
struct node * insertion_1(float,float,struct node *);
struct node * insertione(struct node * ,struct header *,float,float);
struct node * find_loc(float,float,struct header *,struct header **);
void update(struct header * temp,float prev);
float distance(float,float,float,float);
struct header * head=NULL;
struct header * tail=NULL;
struct header * gar=NULL;
int persons=0,choice=0;
void main()
{
	
	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1,NULL,&location,NULL);
	pthread_create(&t2,NULL,&maiin,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_exit(NULL);
	
}
void * maiin()
{
	int num=0,temp=0;
	int option=0,option1=0,inp=0;
	float abs=0,ord=0;
	struct node * add=NULL;
	struct header * tempp=NULL,* top=NULL,*headd=NULL;
	struct node * target=NULL;
	printf("****************** WELCOME TO THE DELIVERY CORPORATION****************\n");
	printf("Enter the No.of delivery boys present at the office\t");
	scanf("%d",&num);
	while(num<=0)
	{
		if(num<=0)
		{
			printf("Invalid input\nPlease enter a positive number\t");
			scanf("%d",&num);	
		}
	}
	struct header * check=creation(num,&head,&tail);
	if(check==NULL)
	return NULL;
	printf("Delivery boys are added successfully\nWe have %d delivery boys in the office\n",persons);
	struct header * teem=NULL;
	while(choice!=8)
	{
		add=NULL,tempp=NULL,top=NULL,target=NULL;
		printf("-----------------------------------------------------\n");
		printf("\n1)Add delivery boy to the list\n2)Delete delivery boy from the list\n3)Status of all delivery boys\n4)Status of particular dlivery boy\n5)Assigning a request\n6)Display series of active deliveries of a delivery boy\n7)To print the completed deliveries\n8)Exit from the application\n\n");
		printf("-----------------------------------------------------\n");
		printf("Enter your choice\t\t");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			printf("Enter the no.of delivery boys you wanted to add\t");
			scanf("%d",&temp);
			creation(temp,&head,&tail);
			printf("Delivery boys are added successfully\nWe have %d delivery boys in the records\n",persons);
			headd=head;
			for(int i=0;i<persons;i++)
			{
				display(headd,0);
				headd=headd->down;
			}
			headd=head;
			break;
			case 2:
			headd=head;
			for(int i=0;i<persons;i++)
			{
				display(headd,0);
				headd=headd->down;
			}
			headd=head;
			printf("Enter the id of the delivery boy you wanted to delete\t");
			scanf("%d",&temp);
			deletion_1(&head,temp);	
			printf("Delivery boy is deleted successfully\nWe have %d delivery boys\n",persons);		
			break;
			case 3:
			status(0,0,head);
			break;
			case 4:
			printf("Enter the id of the delivery boy whose status is to be known\t");
			scanf("%d",&temp);
			status(1,temp,head);
			break;
			case 5 :
			printf("Select the type of delivery\nBy entering your choice\n");
			printf("1)Assign manually\n2)Assigning by computer\n");
			scanf("%d",&option);
			while(option>2||option<=0)
			{
				if(option>2||option<=0)
				{
					printf("Please enter the valid choice\n");
					printf("1)Assign manually\n2)Assigning by computer\n");
					scanf("%d",&option);
				}
			}
			printf("press 1 to collect package from delivery office and deliver\npress 2 to collect a package\n");
			scanf("%d",&option1);
			while(option1>2||option1<=0)
			{
				if(option1>2||option1<=0)
				{
					printf("Please enter a valid choice\n");
					printf("press 1 to collect package from delivery office and deliver\npress 2 to collect a package\n");
					scanf("%d",&option1);
				}
			}
			if(option==1)
			{
				if(option1==2)
				{
					printf("Enter the x-co-ordinates of the location\t");
					scanf("%f",&abs);
					printf("Enter the y-co-ordinates of the location\t");
					scanf("%f",&ord);
				}
				else
				{
					abs=0;
					ord=0;
				}
				printf("Enter the id of the employee\t");
				scanf("%d",&inp);
				tempp=search(inp,head,&gar);
				if(tempp==NULL)
				{
					printf("No delivery boy exsist with the given id\n");
					break;
				}
				else
				{
					add=insertion(abs,ord,tempp);
					if(option1==2&&add==NULL)
					tempp->trips=tempp->trips+1;
					if(option1!=1&&add!=NULL)
					{
						printf("Delivery is successfully alloted\n");
					}
				}
				if(option1==1)
				{
					if(add==NULL)
					printf("As package is collected\n");
					printf("Now Enter the co-ordinates of the place where the package need to be delivered\n");
					printf("Enter the x-co-ordinates of the location\t");
					scanf("%f",&abs);
					printf("Enter the y-co-ordinates of the location\t");
					scanf("%f",&ord);
					if(add!=NULL)
					add=insertion_1(abs,ord,add);
					else if(add==NULL)
					add=insertion(abs,ord,tempp);
					if(add!=NULL)
					printf("Delivery is successfully alloted\n");
					
				}
			}
			if(option==2)
			{
				if(option1==2)
				{
					printf("Enter the x-co-ordinates of the location\t");
					scanf("%f",&abs);
					printf("Enter the y-co-ordinates of the location\t");
					scanf("%f",&ord);
				}
				else
				{
					abs=0;
					ord=0;
				}
				target=find_loc(abs,ord,head,&top);
				add=insertione(target,top,abs,ord);
				if(option1==2)
				{
					printf("Delivery is successfully alloted\n");
					printf("We alloted your request to delivery boy with id %d\n",top->id);
				}
				if(add==NULL&&option1==2)		
				top->trips=top->trips+1;
				if(option1==1)
				{
					if(add==NULL)
					printf("As package is collected\n");
					printf("Now Enter the co-ordinates of the place where the package need to be delivered\n");
					printf("Enter the x-co-ordinates of the location\t");
					scanf("%f",&abs);
					printf("Enter the y-co-ordinates of the location\t");
					scanf("%f",&ord);
					if(add!=NULL)
					add=insertion_1(abs,ord,add);
					else if(add==NULL)
					add=insertion(abs,ord,top);
					if(add!=NULL)
					printf("Delivery is successfully alloted\n");
					printf("We alloted your request to delivery boy with id %d\n",top->id);
				}
			}
			break;
			case 6:
			printf("Enter the id of the delivery boy\t");
			scanf("%d",&inp);
			tempp=search(inp,head,&gar);
			if(tempp==NULL)
			{
				printf("No delivery boy exsist with the given id\n");
				break;
			}
			else
			{
				display(tempp,1);
			}
			break;
			case 7:
			break;
			case 8:
			teem=head;
			for(int i=0;teem!=NULL;i++)
			{
				deletion_1(&head,teem->id);
				teem=head;
			}
			break;
			default:
			printf("Please enter a valid choice\n");
			break;
		}
	}
	
}
struct header * creation(int num,struct header ** temp,struct header ** prev)
{
	struct header * ptr1=NULL;
	for(int i=0;i<num;i++)
	{
		ptr1=(struct header *)malloc(sizeof(struct header));
		if(ptr1==NULL)
		{
			printf("Over flow of the data\nRestart the application\n");
			return NULL;
		}
		printf("Enter the name of the delivery boy\t");
		scanf(" %[^\n]s",ptr1->name);
		ptr1->trips=0;
		ptr1->loc1=0;
		ptr1->loc2=0;
		if(*prev==NULL)
		ptr1->id=100;
		else
		ptr1->id=(*prev)->id+1;
		printf("ID of this delivery boy is %d\n\n",ptr1->id);
		if(*temp==NULL)
		{
			*temp=ptr1;
			*prev=ptr1;
		}
		if(*prev!=NULL)
			(*prev)->down=ptr1;
		ptr1->down=NULL;
		ptr1->next=NULL;
		*prev=ptr1;
	}
	persons=persons + num;
	return *temp;
}
void display(struct header * head1,int flag)
{
	struct node * ptr=head1->next;
	printf("Name :\t%s\t",head1->name);
	printf("ID   :%d\n",head1->id);
	if(flag==1){
	printf("Total no.of orders received either to collect or deliver\t:%d\n",head1->trips);
	printf("\n");
	if(ptr==NULL)
	printf("No active orders\n");
	if(ptr!=NULL)
	printf("Co-ordinates of the order\t--no.of orders to be collected/delivered\n");
	while(ptr!=NULL)
	{
		printf("( %.2f, %.2f )                \t--%d\n",ptr->x,ptr->y,ptr->orders);
		ptr=ptr->link;
	}
}
}
struct header * search(int idd,struct header * headd,struct header ** prev)
{
	*prev=NULL;
	while(headd!=NULL)
	{
		if(headd->id==idd)
		return headd;
		else
		{
			*prev=headd;
			headd=headd->down;
		}
	}
	return NULL;
}
struct header * deletion(struct header *headd)
{
	struct node * temp=headd->next;
	if(temp!=NULL)
	{
		headd->next=temp->link;
		free(temp);
		temp=NULL;
	}
	if(temp==NULL)
	return NULL;
}
struct header * status(int flag,int idd,struct header * ptr)
{
	struct header * temp=NULL;
	if(flag==0)
	{
		printf("Status of the delivery boys are\n");
		while(ptr!=NULL)
		{
			if(ptr->next==NULL)
			{
				printf("The delivery boy with id : %d is not having any order to be delivered\n",ptr->id);
			}
			else
			{
				printf("Delivery boy with id : %d is currently delivering to the location (%.2f,%.2f)\n",ptr->id,ptr->next->x,ptr->next->y);
			}
			ptr=ptr->down;
		}
		
	}
	else
	{
		temp=search(idd,ptr,&gar);
		if(temp==NULL)
		{
			printf("No delivery boy is present in the records with the given %d id\n",idd);
			return NULL;
		}
		else
		{
			if(temp->next!=NULL)
			printf("Delivery boy is currently delivering to the location (%.2f,%.2f)\n",temp->next->x,temp->next->y);
			else
			printf("The delivery boy with id : %d is not having any order  to be delivered\n",temp->id);	
		}
	}
}	
struct node * insertion(float abs,float ord,struct header * ptr)
{
	struct node * temp=(struct node *)malloc(sizeof(struct node)); 
	if(temp==NULL)
	{
			printf("Over flow of the data\nRestart the application\n");
			return NULL;
	}
	struct node * first=ptr->next;
	struct node * temp1=NULL;
	float dis2,min;
	temp->x=abs;
	temp->y=ord;
	min=distance(ptr->loc1,ptr->loc2,abs,ord);
	if(min==0)
	{
		printf("Delivery boy is currently at the Given location\n");
		printf("So work is accomplished\n");
		free(temp);
		temp=NULL;
		return NULL;
	}
		while(first!=NULL)
		{
			dis2=distance(first->x,first->y,abs,ord);
			if(min>dis2)
			{
				min=dis2;
				temp1=first;
			}
			first=first->link;
		}
		if(temp1==NULL&&min==0)
		{
			printf("Delivery boy is currently at the Given location\n");
			printf("So work is accomplished\n");
			free(temp);
			temp=NULL;
			return NULL;
		}
		else if(ptr->next==NULL)
		{
			ptr->next=temp;
			temp->link=NULL;
			temp->orders=1;
		}
		else if(temp1==NULL)
		{
			temp->link=ptr->next;
			ptr->next=temp;
			temp->orders=temp->orders+1;
		}
		else if(min==0&&temp1!=NULL)
		{
			temp1->orders=temp1->orders+1;
			free(temp);
			temp=NULL;
			ptr->trips=ptr->trips+1;
			return temp1;
		}
		else
		{
			temp->link=temp1->link;
			temp1->link=temp;
			temp->orders=temp->orders+1;
		}
		ptr->trips=ptr->trips+1;
		return temp;
}	
float distance(float num1,float num2,float num3,float num4)
{
	float ans=sqrt(pow(num1-num3,2)+pow(num2-num4,2));
	return ans;
}	
struct node * insertion_1(float abs,float ord,struct node * add)
{
	struct node * temp=(struct node *)malloc(sizeof(struct node)); 
	if(temp==NULL)
	{
		printf("Over flow of the data\nRestart the application\n");
		return NULL;
	}
	temp->x=abs;
	temp->y=ord;
	temp->link=NULL;
	struct node * temp1=add;
	struct node * comp=add;
	float dis2,min;
	min=distance(add->x,add->y,abs,ord);
	struct node * ptr=add->link;
		while(ptr!=NULL)
		{
			dis2=distance(ptr->x,ptr->y,abs,ord);
			if(min>dis2)
			{
				min=dis2;
				temp1=ptr;
			}
			ptr=ptr->link;	
		}
	        if(min==0&&temp1==comp)
		{
			printf("Delivery boy is currently at the Given location\n");
			printf("So work is accomplished\n");
			free(temp);
			temp=NULL;
			return NULL;
		}
		else if(add->link==NULL)
		{
			add->link=temp;
			temp->orders=temp->orders+1;
			return temp;
		}
		else if(min==0&&temp1!=comp)
		{
			temp1->orders=temp1->orders+1;
		}
		else 
		{

			temp->link=temp1->link;
			temp1->link=temp;
			temp->orders=temp->orders+1;
		}
	
}	
struct node * find_loc(float abs,float ord,struct header * headd,struct header ** ans)
{
	float min1,dist2,min2;
	struct header * ptr=NULL;
	struct node * temp=NULL, *node=NULL;
	ptr=head;
	min1=(distance(ptr->loc1,ptr->loc2,abs,ord));
	*ans=ptr;
	if(min1==0)
	{
		*ans=ptr;
		return NULL;
	}
	while(ptr!=NULL)
	{
		temp=ptr->next;
		min2=(distance(ptr->loc1,ptr->loc2,abs,ord));
		if(min1>min2)
		{
			min1=min2;
			*ans=ptr;
			node=NULL;
			if(min1==0)
			{
				*ans=ptr;
				return NULL;
			}
		}
		while(temp!=NULL)
		{
			min2=(distance(temp->x,temp->y,abs,ord));
			if(min1>min2)
			{
				min1=min2;
				*ans=ptr;
				node=temp;
				if(min1==0)
				{
					*ans=ptr;
					return node;
				}
			}
			temp=temp->link;
		}
		ptr=ptr->down;
	}
	return node;
}
struct node * insertione(struct node * target,struct header * top,float x,float y)
{
	 struct node * temp=(struct node *)malloc(sizeof(struct node));
	 if(temp==NULL)
	 {
			printf("Over flow of the data\nRestart the application\n");
			return NULL;
	 }
	 temp->x=x;
	 temp->y=y;
	 temp->orders=1;
	 temp->link=NULL;
	 if(target==NULL&&top->loc1==x&&top->loc2==y)
	 {
	 	printf("Delivery boy is currently at the Given location\n");
		printf("So work is accomplished\n");
		free(temp);
		temp=NULL;
		return NULL;
	 }
	 else if(target==NULL)
	 {
		temp->link=top->next;
		top->next=temp;
	 }
	 else if(target->x==x&&target->y==y)
	 {
		target->orders=target->orders+1;
		free(temp);
		temp=NULL;
		top->trips=top->trips+1;
		return target;
	 }
	 
	 else
 	 {
		temp->link=target->link;
		target->link=temp;
       	 }
	 top->trips=top->trips+1;
	 return temp;
}
float * find_dis(struct header * headd)
{
	float *distan=(float *)malloc(sizeof(float)*(persons+1));
	if(distan==NULL)
	{
			printf("Over flow of the data\nRestart the application\n");
			return NULL;
	}
	for(int i=0;headd!=NULL;i++)
	{
		if(headd->next!=NULL)
		{
			*(distan+i)=distance(headd->loc1,headd->loc2,headd->next->x,headd->next->y);
		}
		else
		*(distan+i)=0;
		headd=headd->down;
	}
	*(distan+persons)=-1;
	return distan;
}	
void update(struct header * temp,float prev)
{
	struct node * ptr=temp->next;
	float tan=((temp->loc2)-(ptr->y))/((temp->loc1)-(ptr->x));
	float cos=sqrt( 1/(pow(tan,2)+1) );
	float sin=sqrt(1-pow(cos,2));
	if(distance(temp->loc1+5*cos,temp->loc2+5*sin,ptr->x,ptr->y)<prev)
	{
		temp->loc1=temp->loc1+5*cos;
		temp->loc2=temp->loc2+5*sin;
	}
	else
	{
		temp->loc1=temp->loc1-5*cos;
		temp->loc2=temp->loc2-5*sin;
	}
}
void* location()
{
	int size;
	FILE *fptr1;
	fptr1=fopen("/home/saish/history.txt","w");
	if(fptr1==NULL)
	{
		printf("FILE DOES NOT EXIST\n");
		return 0;
	}
	struct header * temp=head;
	struct header * ptr=NULL;
	float * distan=NULL;
	while(choice!=8)
	{
		distan=find_dis(head);
		temp=head;
		for(int i=0;temp!=NULL&&(*(distan+i))!=-1;i++)
		{
			if(temp->next!=NULL&&(*(distan+i))<=5)
			{
				//printf("Precent LOC1=%f,LOC2=%f\n",temp->loc1,temp->loc2);
				fprintf(fptr1,"Delivery boy with the id %d reached",temp->id);
				fprintf(fptr1," (%.2f,",temp->next->x);
				fprintf(fptr1,"%.2f)\n\n",temp->next->y);
				//printf("\nDelivery boy with the id %d reached (%.2f,%.2f)\n",temp->id,temp->next->x,temp->next->y);
				deletion(temp);
			}
			else if(temp->next!=NULL)
			{
				update(temp,*(distan+i));
				//printf("Precent LOC1=%f,LOC2=%f\n",temp->loc1,temp->loc2);
			}
			temp=temp->down;
		}
		if(choice==8)
		fclose(fptr1);
		free(distan);
		distan=NULL;
		sleep(5);	
	}
	
}
struct header * deletion_1(struct header ** headd,int idd)
{
	struct header * prev=NULL;
	struct header * ptr=search(idd,*headd,&prev);
	struct node * temp=ptr->next,*temp1=NULL;
	if(ptr==NULL)
	{
		printf("No delivery boy is present in the records with the given %d id\n",idd);
		return NULL;
	}
	else
	{
		while(temp!=NULL)
		{
			temp1=temp;
			free(temp1);
			temp1=NULL;
			temp=temp->link;
		}
		if(*headd==tail)
		{
				tail=NULL;
				*headd=NULL;
				free(ptr);
				ptr=NULL;
				persons=persons-1;
		}
		else if(ptr==*headd&&prev==NULL)
		{
			*headd=ptr->down;
			free(ptr);
			ptr=NULL;
			persons=persons-1;
		}
		else
		{
			if(ptr==tail)
			{
				tail=prev;
				prev->down=NULL;
				free(ptr);
				ptr=NULL;
				persons=persons-1;
			}
			else
			{
				prev->down=ptr->down;
				free(ptr);
				ptr=NULL;
				persons=persons-1;
			}
		}
	}
	
}