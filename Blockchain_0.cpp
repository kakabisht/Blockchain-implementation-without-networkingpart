#include <iostream>
#include <stdlib.h>
#include<time.h>
#include <string.h> 
using namespace std;

class Node{
    public:
    int ammount;
    string sender;
    string receiver;
    double id;
    string timestamp;
    string hash;
    Node *next;
    
    Node()//default constructor
    {
        ammount=0;
        sender="Owner";
        receiver="Fixed by Owner";
        timestamp="NULL";
        id=rand() % 100;//Unique id for each block 
        next=NULL;
    }

    Node(int n,string s, string r, string time )//constructor
    {
        ammount=n;
        sender=s;
        receiver =r;
     //   int t = stoi(time);
        timestamp=time;
        id=rand() % 100;//Unique id for each block 
        next=NULL;
    }
};


class Blockchain : public Node
{   
    private:
    Node *listptr,*temp;
    //ptr is used to point at the current node and temp is used for temporary usages such as iterations , ammount storage for a small time.
    public: 
    Blockchain()//
    {
        listptr=NULL;
        temp=NULL;
        //initializing the values to NULL , to avoid segmentation error
    }
    void Create(int , string, string);
    void Display();
    void HashDisplay();
    int Isempty();
    int len();
    void Insert();
    void Search();
    void ProofofWork();
    void Mining();
    void Correctblock(Blockchain, Blockchain);
}lk1,lk2 ;


void Blockchain :: Create(int num, string sender , string receiver)
{
    time_t my_time = time(NULL); 
    timestamp=ctime(&my_time);

    Node *newnode = new Node(num,sender,receiver,timestamp);
    if(listptr == NULL)
        listptr = temp = newnode;
    else
        {
            temp -> next = newnode;//temp currently points towards current block
            temp = temp->next;
        }
    
}

int Blockchain :: Isempty()
{
    if(listptr == NULL)
        return 0;
    else
        return 1;
    
}

void Blockchain:: Display()
{
    Node * current_node = listptr ;         /*    temp points to first node*/
    if ( Isempty()==0 )
    {
            cout<<"List is empty";
    }
    else
    {
       cout<<"\n";
        while (current_node != NULL) //iterate till it reaches last block
        {
            cout <<"\n |\t"<< current_node->ammount <<" Sent to "<<current_node->receiver<<" by "<<current_node->sender<<" ,Transaction ID "<<current_node->id<<" ,at "<<current_node->timestamp<<" \t| "<< " ---> ";
            current_node = current_node->next;         /*    move temp to the next node */
        }
        cout<< "NULL"; 
        cout<<"\n";  
    }
}

void Blockchain:: HashDisplay()
{
    Node * current_node = listptr ;         /*    temp points to first node*/
    if ( Isempty()==0 )
    {
            cout<<"List is empty";
    }
    else
    {
        
       cout<<"\n";
        while (current_node != NULL) //iterate till it reaches last block
        {
            std::hash<string> shashVal;
            string final =current_node->sender+current_node->receiver;//hash value of Sender and receiver 
            std::hash<int> ihashVal;
            int fin=current_node->id;//hash value of id 
            cout <<"\n |\t"<< current_node->ammount <<" Hash value of transaction "<<shashVal(final)+ihashVal(fin)<< " ,at time "<<current_node->timestamp<<" \t| "<< " ---> ";
            current_node = current_node->next;         /*    move temp to the next node */
        }
        cout<< "NULL"; 
        cout<<"\n";  
    }
}



void Blockchain::Insert()
{
    Node *current_node=listptr;
    while (current_node->next!=NULL)
        current_node=current_node->next;

    int num;
    string sender,receiver,timestamp;
    cout<<"\n Enter the ammount , \n Sender Digital signature \n Receiver Digital signature \n  ";
    cin>>num;
    cin>>sender;
    cin>>receiver;
    time_t my_time = time(NULL); 
    timestamp=ctime(&my_time);

    Node *newnode = new Node(num,sender,receiver,timestamp);
    cout <<"\n |\t"<< newnode->ammount <<" Sent to "<<receiver<<" by "<<sender<<" ,Transaction ID "<< id<<" ,at "<<timestamp<<" \t| "<< " ---> ";

    newnode->next=NULL;
    current_node->next=newnode;    
 
}

int Blockchain ::len()
{
    int count=0;
    Node * current_node = listptr ;         /*    temp points to first node*/
    if ( Isempty()==0 )
    {
            cout<<"List is empty";
    }
    else
    {
        while (current_node != NULL)
        {
            count+=1;
            current_node = current_node->next;         /*    move temp to the next node */
        }
    }
    return count;
}
void Blockchain :: Search()
{
    int val;
    cout<<"\n Enter  ID  to search  in List \n";
    cin>>val;
    int find=0;
    int count=0;
    Node *current_node=listptr;
    while (current_node->next!=NULL)
    {
        if (current_node->id==val)
        {
            find=1;
            break;
        }
        count+=1;
        current_node=current_node->next;

    }
    if(find ==1)
        cout<<"\n Transaction is  present at "<<count;
    else
        cout<<"\n Transaction not present";
}

void Blockchain ::ProofofWork(){

    //Assuming that there are two Blockchains , one starts with 1 while another one starts with zero assuming 

    Node * current_node = listptr ;         /*    temp points to first node*/
    if ( Isempty()==0 )
    {
            cout<<"List is empty";
    }
    else
    {
       cout<<"\n";
        while (current_node != NULL) 
        {
            std::hash<string> shashVal;
            string final =current_node->sender+current_node->receiver;
            if (final[0]==1)
            {
                cout<<"Block A";
            }
            else if (final[1]==0)
            {
                cout<<"Block B";
            }
            else           
                cout<<"Block no pattern";
                break;
        }
    }
}
void Blockchain :: Mining()
{
    /* Mining means transaction verification from the node server ,
        Now this can't be done in Data Structures , This is the double spending problem  
        What the best way we can do in DS as of now is put it in an order 
    
        Assuming that two transactions happen from the same sender named ash , 
        We put those two transactions in an order to check if he has balance to do these two transfer or not ,
        most importantly that he is not sending the same  money to both the receivers 

        Assuming that they both have 100 rupees right now in their accounts , So they can't make a transaction more than 100 

    */
    Node *current_node=listptr;
    string senderMin;
    cout<<"\n Enter  Sender name  to check  \n";
    cin>>senderMin;
    int find=0;
    int count=0;
    while (current_node->next!=NULL)
    {
        if (current_node->sender==senderMin)
        {
            if(current_node->ammount <100 )
            {
                count+=1;        
                cout<<"Not enough credit , required credit: \t"<<current_node->ammount -100;
            }
            break;
        }
        current_node=current_node->next;

    }
    if (count==0)//If transactions is valid the
    {
            Node *newnode = new Node(current_node->ammount,current_node->sender,current_node->receiver,current_node->timestamp);

    }
   

    Correctblock(lk1,lk2);
}

void Blockchain::Correctblock(Blockchain l1, Blockchain l2)
{
    int x,y;
    x=l1.len();
    y=l2.len();
    if(x>y)
    {
        cout<<"Blockchain A is longer hence , block will be added into ";
        l1.Display() ;
    }
    else
    {
        cout<<"Blockchain B is longer hence , block will be added into ";
        l2.Display();
    
    }
    
}
int main()
{
    Blockchain lk;
    int k=0;
    string fsender="Owner",freceiver="Choice of Owner";
    int num ;string sender,receiver;
    cout<<"Welcome to Blockchain implementation by Hridyesh ";
    lk.Create(num=100,fsender,freceiver);
    do
    {
        int ch;
        cout<<"Press \n 1.Add Blocks in block chain  \n 2.Display the blocks without hash function  \n 3.Display the HASH Blocks   \n 4.Length of Block chain   \n 5.Search Transaction  \n 6.Proof of Work \n 7.Mining \n";

        cin>>ch;

        switch (ch)
        {
            case 1:
                    cout<<"\n Enter the ammount , \n Sender Digital signature \n Receiver Digital signature \n  ";
                    cin>>num;
                    cin>>sender;    
                    cin>>receiver;
                    lk.Create(num,sender,receiver);
                    break;
            case 2:
                    lk.Display();
                    break;
            case 3:
                    lk.HashDisplay();
                    break;
            case 4: 
                    cout<<"Length of Link List is"<<lk.len();
                    break;
            case 5:
                    lk.Search();
                    break;
            case 6:
                    lk.ProofofWork();
                    break;
            case 7:
                    lk.Mining();
                    break;
            default:
                    break;
        }
        cout<<"\n To continue press 0 \n";
        cin>>k;  

    } while (k==0);
    return 0;
}

