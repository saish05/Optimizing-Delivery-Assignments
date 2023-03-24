# include<iostream>
#include<string.h>
using namespace std;

class node
{
  public:
  float data;
  node*link;
  
  node()
  {
      data=0;
      link=NULL;
  }
  
  node(float data)
  {
      this->data=data;
      this->link=NULL;
  }
    
};

class queue
{
    private:
    node*front;
    node*rear;
    
    public:
    int flag=0;
    
    queue()
    {
        front=NULL;
        rear=NULL;
    }
    
    void enqueue(float data)
    {
        node*temp= new node(data);
        
        if(front==NULL && rear==NULL)
        {
            front=temp;
            rear=temp;
        }
        
        else
        {
            rear->link=temp;
            rear=temp;
        }
       flag=flag+1;

    }
    
    float dequeue()
    {
        try
        {
        if(front==NULL && rear==NULL)
        {
            throw(front);
        }
        }
        
        catch(...)
        {
            cout<<"under flow condition"<<endl;
            return(0);
        }
        
        node*temp=front;
        float d=front->data;
        if(front==rear)
        {
            front=NULL;
            rear=NULL;
        }
        else
        {
            front=front->link;
            delete(temp);
            temp=NULL;
        }
        flag=flag-1;
         return(d);
        
    }
    
    int isempty()
    {
       if(front==NULL && rear==NULL)
        {
            return(1);
        } 
        return(0);
    }
    
    float getfrontdata()
    {
        return(front->data);
    }
    
};

class stack 
{
   
   queue q1,q2;
   
   public:
   
   void push(float data)
   {
       q2.enqueue(data);
       
       while(q1.isempty() != 1)
       {
           q2.enqueue(q1.dequeue());
       }
       
       queue temp;
       temp=q1;
       q1=q2;
       q2=temp;
       
   }
   
   float pop()
   {
       return(q1.dequeue());
   }
    
   float top()
   {
       return(q1.getfrontdata());
   }
   
   int isempty()
   {
    return(q1.isempty());       
   }
   
};

int precedence(char c)
{
if(c=='^')
return(4);
else if(c=='/' || c=='*')
return(3);
else if(c=='+' || c=='-')
return(2);
else
return(0);
}

int operator1(char c)
{
if(c=='/' || c=='*' || c=='+' || c=='-' || c=='^' || c=='(' || c==')')
return(0);
else 
return(1);

}



void menu()
{
   
stack s;    
int i=0;
int j=0;
string p;

cout<<"enter the string"<<endl;
cin>>p;

string q;

while(p[i]!='\0')
{

if(operator1(p[i]))
{
q[j]=p[i];
i=i+1;
j=j+1;
}
else if(p[i]=='(')
{
s.push(p[i]);
i=i+1;

}
else
{
if(precedence(p[i])>precedence(s.top()) )
{
s.push(p[i]);
i=i+1;
}
else if(p[i]==')')
{
while(s.top() !='(')
{
q[j]=s.pop();
j=j+1;
}
i=i+1;
s.pop();
}

else
{
q[j]=s.pop();
j=j+1;
}

}


}

while(s.isempty()!= 1)
{
q[j]=s.pop();
j=j+1;
}
q[j]='\0';

cout<<q<<endl;


    
    
    
    
}


int main()
{
   /* queue q;
    
    q.enqueue(10);
    q.enqueue(15);
    q.enqueue(60);
    
    cout<<q.dequeue()<<endl;
    cout<<q.dequeue()<<endl;
    cout<<q.dequeue()<<endl;
    cout<<q.dequeue()<<endl;
    //cout<<q.dequeue()<<endl; */
    
  /*  stack s;
    
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    */
    
    menu();
    return(0);
};