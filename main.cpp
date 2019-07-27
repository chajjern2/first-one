#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<string>

using namespace std; 

class transactions
	{
	public:
		int id;
		string name;
		float FinalPrice;
		int quantity;
		int Tflag;
		transactions(){
			Tflag=0;
		}
	};

class products
{
public:
	int id;
	string name;
	string category;
	float price;
	float discount;
	int quantity;
	float FinalPrice;
	int flag;
	products(){
		discount=0.0;
		flag=1;
	}

};

class consumers
{
public:
	int cusid;
	string name;
	int age;
	int gender;
	float walletmoney;
	transactions transaction[4];
	consumers(){
		walletmoney=5000;
	}

};

void dsplyProd(products product[100], int &j)
{
	for (int c=0;c<j;c++){
			if (product[c].flag==1){	
				cout<<"\nProduct ID:"<<product[c].id<<"\nProduct Name:"<<product[c].name<<"\nCategory:"<<product[c].category<<"\nProduct MRP:"<<product[c].price<<"\nQuantity Available:"<<product[c].quantity;
				product[c].FinalPrice=product[c].price-(product[c].price*product[c].discount/100);
				if (product[c].discount!=0)
				{ cout<<endl<<product[c].discount<<"% DISCOUNT!";
					cout<<"\nDiscounted Price:"<<product[c].FinalPrice<<endl;
				}
				if (c%3==2)
				{
				cout<<"Press any key to see more products (if any)";
				getch();
				}
			}
	}
}

void dsplyOOSProd(products product[100], int&j)
{
	int flag=0;
	for (int c=0;c<j;c++){
		if (product[c].flag==1 && product[c].quantity<5){	
				flag=1;
				cout<<"\nProduct ID:"<<product[c].id<<"\nProduct Name:"<<product[c].name<<"\nCategory:"<<product[c].category<<"\nProduct MRP:"<<product[c].price<<"\nQuantity Available:"<<product[c].quantity;
				product[c].FinalPrice=product[c].price-(product[c].price*product[c].discount/100);
				if (product[c].discount!=0)
				{ cout<<endl<<product[c].discount<<"% DISCOUNT!";
					cout<<"\nDiscounted Price:"<<product[c].FinalPrice<<endl;
				}
				if (c%3==2)
				{
				cout<<"Press any key to see more products(if any)";
				getch();
				}
			}
	}
	if(flag==0)
		cout<<"\nEverything is enough in stock\n";
	getch();
}

void TCopy(consumers consumer[200], int&b)
{
	consumer[b].transaction[0]=consumer[b].transaction[1];
	consumer[b].transaction[1]=consumer[b].transaction[2];
}


void AddToTransactionList(consumers consumer[200], int&b, products product[100], int&d, int quant)
{
	if (consumer[b].transaction[0].Tflag==0)
	{
		consumer[b].transaction[0].Tflag=1;
		consumer[b].transaction[0].id=product[d].id;
		consumer[b].transaction[0].name=product[d].name;
		consumer[b].transaction[0].quantity=quant;
		consumer[b].transaction[0].FinalPrice=product[d].FinalPrice;
	}
	else if (consumer[b].transaction[1].Tflag==0)
	{
		consumer[b].transaction[1].Tflag=1;
		consumer[b].transaction[1].id=product[d].id;
		consumer[b].transaction[1].name=product[d].name;
		consumer[b].transaction[1].quantity=quant;
		consumer[b].transaction[1].FinalPrice=product[d].FinalPrice;
	}
	else if (consumer[b].transaction[2].Tflag==0)
	{
		consumer[b].transaction[2].Tflag=1;
		consumer[b].transaction[2].id=product[d].id;
		consumer[b].transaction[2].name=product[d].name;
		consumer[b].transaction[2].quantity=quant;
		consumer[b].transaction[2].FinalPrice=product[d].FinalPrice;
	}
	else if (consumer[b].transaction[1].Tflag==1 && consumer[b].transaction[2].Tflag==1 && consumer[b].transaction[0].Tflag==1)
	{
		TCopy(consumer, b);
		consumer[b].transaction[2].Tflag=1;
		consumer[b].transaction[2].id=product[d].id;
		consumer[b].transaction[2].name=product[d].name;
		consumer[b].transaction[2].quantity=quant;
		consumer[b].transaction[2].FinalPrice=product[d].FinalPrice;
	}

}


void login(consumers consumer[200], int&i, products product[100], int&j)
{
	string name,dummy;
	int chce;
	char chc;
	
	system("cls");
	cout<<"Enter Your Name:";
	getline(cin, dummy);
	getline(cin, name);
	int b=0;
	for (;b<i; b++){
		if(name==consumer[b].name)
		{
			cout<<"Correct Password";
			do{
			system("cls");
			cout<<"\nHello "<<consumer[b].name<<"!\nID:"<<consumer[b].cusid<<"\nYour Wallet Balance:"<<consumer[b].walletmoney;
			cout<<"\n\n1.Buy Items\n2.Add WalletMoney\n3.View Last Three Transactions\n4.Edit Your Info\n5.LogOut\n";
			cin>>chce;
			if (chce==1)
			{
			dsplyProd(product, j);
			cout<<"\n\nEnter ID of product you want to buy:\n";
			int ToBuy;
			cin>>ToBuy;
			cout<<"Quantity?\n";
			int quant;
			cin>>quant;
			cout<<"Confirm this purchase? Enter 1 to confirm\n";
			int YorN;
			cin>>YorN;
			if (YorN == 1){
			for (int d=0; d<j; ++d){
				if (ToBuy==product[d].id){
					if(product[d].quantity>=quant)
					{
					product[d].quantity = product[d].quantity - quant;
					consumer[b].walletmoney=consumer[b].walletmoney-(quant*product[d].FinalPrice);
					cout<<"\nTransaction successful\n"<<consumer[b].walletmoney<<" is your current wallet balance.\n";
					AddToTransactionList(consumer, b, product, d, quant);
					break;
					}
					else
						cout<<"\n\nERROR:Product quantity present in stock is not enough!\nOnly "<<product[d].quantity<<" available.";
				}
			}
			}
			else
				cout<<"\nTransaction Cancelled!";
			getch();
			cout<<"\n\n1. Return to Previous Menu\n2.Logout\n";
			cin>>chc;
			if(chc=='2')
				break;
			}
			else if (chce==2)
			{
					string passwordAttempt,dummy;
					cout<<"\nEnter auth password:";
					getline(cin, dummy);
					getline(cin, passwordAttempt);
					int ch;
					if (passwordAttempt=="admin")
					{
					system("cls");
					cout<<"\nEnter Amount of money you want to add:";
					float moneyadded;
					cin>>moneyadded;
					if (moneyadded<=5000 && consumer[b].walletmoney+moneyadded<=10000)
					{
						consumer[b].walletmoney=consumer[b].walletmoney+moneyadded;
						cout<<"\nMoney was successfully added to your wallet!\nYour new Wallet Balance is "<<consumer[b].walletmoney;
					}
					else if(moneyadded>5000 || consumer[b].walletmoney+moneyadded>10000)
						cout<<"\nERROR:You can add max. 5000 at a time and your max. Wallet balance can be 10,000!\n"; 
					getch();
					cout<<"\n\n1. Return to Previous Menu\n2.Press anything else to logout\n";
					cin>>chc;
					}
					else 
						cout<<"\nWrong password!\n";
			}
			else if(chce==3)
			{
				for (int x=0;x<3;x++)
				{
					if(consumer[b].transaction[x].Tflag==1){
						cout<<"\n\nProduct ID:"<<consumer[b].transaction[x].id<<"\nProduct Name:"<<consumer[b].transaction[x].name<<"\nProduct's Final Price:"<<consumer[b].transaction[x].FinalPrice<<"\nQuantity Purchased:"<<consumer[b].transaction[x].quantity<<"\nAmount Paid:"<<consumer[b].transaction[x].FinalPrice*consumer[b].transaction[x].quantity<<endl;
					}
				}
				cout<<"\n\nPress any key to get back to previous menu";
						getch();
			}

			else if(chce==4)
			{
				system("cls");
				cout<<"\n1.Name:"<<consumer[b].name<<"\n2.Age:"<<consumer[b].age<<"\n3.Gender:";
				if(consumer[b].gender==2)
					cout<<"Female";
				else if(consumer[b].gender==1)
					cout<<"Male";
				cout<<"\nInput number of what you want to Edit:";
				int choice;
				cin>>choice;
				cout<<"\n\nInput New Value:";
				switch(choice)
				{
				case 1: getline(cin, dummy);
						getline(cin, consumer[b].name);
						break;
				case 2: cin>>consumer[b].age;
						break;
				case 3: cout<<"\n(1-Male 2-Female)\n";
						cin>>consumer[b].gender;
						break;
				default: cout<<"Invalid choice!";
				}
				cout<<"\n1.Return to previous menu\n2.LogOut\n";
				cin>>chc;
			}

			else if(chce==5)
				break;
	} while (chc==1);
	}
	}
}

void rgstr(consumers consumer[200], int &i)
{
	cout<<"\nEnter ID:"; 
	cin>>consumer[i].cusid;
	cout<<"Name:";
	cin.ignore();
	getline(cin,consumer[i].name);
	cout<<"Age:";
	cin>>consumer[i].age;
	cout<<"Gender\n(1-male 2-female):";
	cin>>consumer[i].gender;
	cout<<"Press any key to get to main menu";
}

void addprod(products product[100], int &j)
{
	cout<<"\nEnter ID:";
	cin>>product[j].id;
	cout<<"\nEnter Name:";
	cin.ignore();
	getline(cin, product[j].name);
	cout<<"\nEnter Category:";
	cin.ignore();
	getline(cin,product[j].category);
	cout<<"\nEnter Price:";
	cin>>product[j].price;
	cout<<"\nEnter Discount(in %):";
	cin>>product[j].discount;
	cout<<"\nEnter Quantity:";
	cin>>product[j].quantity;
	cout<<endl;
}

void editProd(products product[100], int &j)
{
	dsplyProd(product, j);
	cout<<"\n\nEnter ID of product you want to edit(enter 0 to exit):";
	int q;
	int v=0;
	cin>>q;
	for(;v<j; v++){
		if (product[v].id==q && q!=0){
			break;
		}

	}

	cout<<"\nWhat do you want to edit:\n1.ID\n2.Name\n3.Category\n4.Price\n5.Discount\n6.Quantity\n";
	int ch;
	cin>>ch;
	cout<<"\n\n\nEnter the new value\n";
	switch(ch)
	{
	case 1: cin>>product[v].id;
			break;
	case 2: cin.ignore();
			getline(cin, product[v].name);
			break;
	case 3: cin.ignore();
			getline(cin, product[v].category);
			break;
	case 4: cin>>product[v].price;
			break;
	case 5: cin>>product[v].discount;
			break;
	case 6: cin>>product[v].quantity;
			break;
	}

}

void DelProd(products product[100], int &j)
{
	dsplyProd(product, j);
	cout<<"\n\nEnter ID of product you want to delete:";
	int q;
	int v=0;
	cin>>q;
	for(;v<j; v++){
		if (product[v].id==q){
			break;
		}
	}
		product[v].flag=0;
}

void ProdCat(products product[100], int &j)
{
	string passwordAttempt,dummy;
	cout<<"\nEnter auth password:";
	getline(cin, dummy);
	getline(cin, passwordAttempt);
	int ch;
	if (passwordAttempt=="admin")
	{
		do{system("cls");
		cout<<"PASSWORD CORRECT\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PRODUCT CATALOGUE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n1.Add Product\n2.Edit Product\n3.Delete Product\n4.View Product List\n5.Product out of stock or less in quantity\n6.Log Out\n";
		cin>>ch;
		switch(ch)
		{
		case 1: addprod(product, j);
				j++;
				break;
		case 2: editProd(product, j);
				break;
		case 3: DelProd(product, j);
				break;
		case 4: dsplyProd(product, j);
				break;
		case 5: dsplyOOSProd(product, j);
				break;
		case 6: cout<<"Press any key to logout";
			    break;
		}
		} while (ch!=6);
	}
	else cout<<"\nWrong password!\n";

}

void objcreation(consumers consumer[200], products product[100], int&j, int&i)
{
	consumer[i].name="naman";
	consumer[i].age=18;
	consumer[i].cusid=6;
	consumer[i].gender=1;
	++i;
	consumer[i].name="rashya";
	consumer[i].age=20;
	consumer[i].cusid=16;
	consumer[i].gender=1;
	++i;
	consumer[i].name="saijal";
	consumer[i].age=20;
	consumer[i].cusid=26;
	consumer[i].gender=1000;
	++i;
	product[j].id=1;
	product[j].category="drink";
	product[j].name="pepsi";
	product[j].discount=20;
	product[j].price=100;
	product[j].quantity=1000;
	++j;
	product[j].id=2;
	product[j].category="drink";
	product[j].name="coke";
	product[j].discount=10;
	product[j].price=100;
	product[j].quantity=1000;
	++j;
	product[j].id=3;
	product[j].category="drink";
	product[j].name="ThumbsUp";
	product[j].discount=20;
	product[j].price=5;
	product[j].quantity=1;
	++j;
	product[j].id=4;
	product[j].category="Ice Cream";
	product[j].name="Vanilla";
	product[j].discount=50;
	product[j].price=100;
	product[j].quantity=1000;
	++j;
	product[j].id=5;
	product[j].category="Ice Cream";
	product[j].name="Butterscotch";
	product[j].discount=20;
	product[j].price=120;
	product[j].quantity=1000;
	++j;
}



void main()
{
	int i=0;
	int j=0;
	int ch1;
	consumers consumer[200];
	products product[100];
	objcreation(consumer, product, j, i);
	do{
	system("cls");
	cout<<"SUPERMARKET MANAGMENT SYSTEM\n1.Login\n2.Register\n3.Product Catalogue\n4.Exit\n";
	cin>>ch1;
	switch(ch1)
	{
	case 1: login(consumer, i, product, j);
			  break;
	case 2: rgstr(consumer,i);
			i++;
			  break;
	case 3: ProdCat(product, j);
			  break;
	case 4: cout<<"Press any key to exit";
			  break;
	}
	getch();
	} while (ch1>=1 && ch1<=3);

}