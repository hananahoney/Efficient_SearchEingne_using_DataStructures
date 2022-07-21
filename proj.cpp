// proj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<cmath>
#include<fstream>
using namespace std;

int total_id_space = 1;
int line = 0;
template<typename T>
class AvlTree
{
	struct AvlNode
	{
		int element;
		string file_name = " ";
		int line_no = -1;
		AvlNode* left;
		AvlNode* right;
		int Height;
	};

	AvlNode* root;
	int Height(AvlNode* P)
	{
		if (P == NULL)
			return -1;
		else
			return P->Height;
	}
	int max(int a, int b)
	{
		if (a > b)
			return a;
		else
			return b;
	}
	AvlNode* SingleRightRotation(AvlNode* k1)
	{
		AvlNode* k2;

		k2 = k1->left;
		k1->left = k2->right;
		k2->right = k1;

		k1->Height = max(Height(k1->left), Height(k1->right)) + 1;
		k2->Height = max(Height(k2->left), Height(k2->right)) + 1;

		return k2;
	}
	AvlNode* SingleLeftRotation(AvlNode* k1)
	{
		AvlNode* k2;

		k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;

		k1->Height = max(Height(k1->left), Height(k1->right)) + 1;
		k2->Height = max(Height(k2->left), Height(k2->right)) + 1;


		return k2;
	}
	AvlNode* DoubleRightRotation(AvlNode* k3)
	{
		k3->left = SingleLeftRotation(k3->left);

		return (SingleRightRotation(k3));
	}
	AvlNode* DoubleLeftRotation(AvlNode* k1)
	{
		k1->right = SingleRightRotation(k1->right);

		return (SingleLeftRotation(k1));
	}
	AvlNode* insertact(int x, AvlNode* t)
	{

		if (t == NULL)
		{
			t = new AvlNode;
			t->element = x;
			t->left = t->right = NULL;
			t->Height = 0;
		}
		else if (x < t->element)
		{
			t->left = insertact(x, t->left);
			if (Height(t->left) - Height(t->right) == 2)
			{
				if (x < t->left->element)
				{
					t = SingleRightRotation(t);
				}
				else
					t = DoubleRightRotation(t);
			}
		}
		else if (x > t->element)
		{
			t->right = insertact(x, t->right);
			if (Height(t->right) - Height(t->left) == 2)
			{
				if (x > t->right->element)
				{
					t = SingleLeftRotation(t);
				}
				else
					t = DoubleLeftRotation(t);
			}
		}
		t->Height = max(Height(t->left), Height(t->right)) + 1;
		return t;
	}
	void inOrderact(AvlNode* temp)
	{
		if (temp != NULL)
		{
			inOrderact(temp->left);
			cout << temp->element << " ";
			inOrderact(temp->right);
		}
	}
	void insertac_data(AvlNode* r,int node_id,T da)
	{
		AvlNode* temp = NULL;
		temp = findact(r, node_id);
		temp->file_name = "insertion.txt";
		temp->line_no = line;
		if (line == 0)
		{
			ofstream file("insertion.txt", ios::out);
			file << da << "\n";
			file.close();
		}
		else
		{
			ofstream file("insertion.txt", ios::out | ios::app);
			file << da << "\n";
			file.close();
		}
		line++;
	}
	void avl_line_act( AvlNode* temp )
	{
		if (temp != NULL)
		{
			inOrderact(temp->left);
			cout << temp->element << " ";
			inOrderact(temp->right);
		}
	}
	AvlNode* findact(AvlNode* temp, int val)
	{
		if (temp == NULL)
			return NULL;
		else if (val < temp->element)
			return findact(temp->left, val);
		else if (val > temp->element)
			return findact(temp->right, val);
		else
			return temp;
	}
	AvlNode* deleteNode(AvlNode* p, int data)
	{

		if (p->left == NULL && p->right == NULL) {
			delete p;
			return NULL;
		}

		AvlNode* t;
		AvlNode* q;
		if (p->element < data) {
			p->right = deleteNode(p->right, data);
		}
		else if (p->element > data) {
			p->left = deleteNode(p->left, data);
		}
		else {
			if (p->left != NULL) {
				q = inpre(p->left);
				p->element = q->element;
				p->left = deleteNode(p->left, q->element);
			}
			else {
				q = insuc(p->right);
				p->element = q->element;
				p->right = deleteNode(p->right, q->element);
			}
		}

		if (Height(p->right) - Height(p->left) == 2)
		{
			if (data > p->right->element)
			{
				p = SingleLeftRotation(p);
			}
			else
				p = DoubleLeftRotation(p);
		}
		else if (Height(p->left) - Height(p->right) == 2)
		{
			if (data < p->left->element)
			{
				p = SingleRightRotation(p);
			}
			else
				p = DoubleRightRotation(p);
		}
		p->Height = max(Height(p->left), Height(p->right)) + 1;
		return p;
	}
	AvlNode* inpre(AvlNode* p) {
		while (p->right != NULL)
			p = p->right;
		return p;
	}

	AvlNode* insuc(AvlNode* p) {
		while (p->left != NULL)
			p = p->left;

		return p;
	}

public:
	AvlTree()
	{
		root = NULL;
	}
	AvlNode* getroot()
	{
		return root;
	}
	void setroot(AvlNode* t)
	{
		root = t;
	}
	void insert(int val)
	{
		root = insertact(val, root);
	}
	void inOrder()
	{
		inOrderact(root);
	}
	bool is_found( int valu )
	{
		AvlNode* temp = NULL;
		temp = findact(root, valu);
		if (temp)
			return true;
		else
			return false;
	}
	int found_data(int valu)
	{
		AvlNode* temp = NULL;
		temp = findact(root, valu);
		return temp->data;
	}
	void insert_data( T d , int node_id )
	{
		insertac_data(root,node_id,d);
	}
	void file_line(int key)
	{
		AvlNode* temp = findact(root, key);
		if (temp->file_name == " " && temp->line_no == -1)
		{
			cout << "No data inserted yet " << endl;
		}
		else
		{
			cout << "File Name : " << temp->file_name<<endl;
			cout << "Line No : " << temp->line_no+1 << endl;
		}
	}
	void del(int key)
	{
		cout << endl;
		AvlNode* temp = findact(root,key);
		if (temp->file_name == " " && temp->line_no == -1)
		{
			cout << "No data Entered Yet and it's gonna delete" << endl;
		}
		else
		{
			cout << endl<<"data stored is : ";
			string dat;
			ifstream file(temp->file_name,ios::in);
			for (int i = 0; i < temp->line_no; i++)
				file.ignore(50,'\n');

			getline(file,dat);
			file.close();
			cout << dat << endl;
		}

		root = deleteNode(root,key);
		cout << "updated AVL is : ";
		this->inOrder();
		cout << endl;
	}
	~AvlTree()
	{

	}
};

template<typename T>
class singlylinkedlist   //singly circular linked list
{
    struct node
    {
        int id;
		AvlTree<T> avl;
		int* finger_table;
        node* next;
    };
    node* head;
public:
    singlylinkedlist()
    {
        head = NULL;
    }
    void insert( int mid )  //machine id
    {
        node* newnode = new node;
        newnode->id = mid;
		newnode->finger_table = new int [log2(total_id_space + 1)];
        node* temp = head;
        if (temp == NULL)
        {
            newnode->next = newnode;
            head = newnode;
        }
        else if (temp->id >= newnode->id)
        {
            while (temp->next != head)
                temp = temp->next;

            temp->next = newnode;
            newnode->next = head;
            head = newnode;
        }  
        else
        {
            while (temp->next != head && temp->next->id < newnode->id)
                temp = temp->next;

            newnode->next = temp->next;
            temp->next = newnode;
        }
    }
    void display()
    {
        node* temp;
        temp = head;
        do {
			cout << endl;
            cout << "id : "<<temp->id<<endl;
			cout << "avl : ";
			temp->avl.inOrder();
			cout << endl;
			cout << "Routing table : ";
			for (int i = 0; i < log2(total_id_space + 1); i++)
				cout << temp->finger_table[i] << " ";

			cout << endl;
            temp = temp->next;
        } while (temp != head);
    }
	void make_avls()
	{
		node* temp;
		temp = head;
		do
		{
			temp->avl.insert(temp->id);
			int idt = temp->id+1;
			if (temp->next != head)
			{
				for (idt; idt <= temp->next->id; idt++)
				{
						temp->next->avl.insert(idt);
				}
			}
			else if (temp->next == head)
			{
				for (idt; idt <= total_id_space; idt++)
				{
					temp->next->avl.insert(idt);
				}
				idt = 0;
				for (idt; idt <= temp->next->id; idt++)
				{
					temp->next->avl.insert(idt);
				}
			}
			temp = temp->next;
		} while ( temp != head );

		this->make_fingertables();
	}
	void make_fingertables()		//routing table
	{
		node* temp1 = head;
		node* temp2 = head;
		do
		{
			for (int i = 1,j = 0; j < log2(total_id_space + 1) ; i *= 2,j++)
			{
				temp2 = head;
				do
				{
					int ide = -1;
					ide = temp1->id + i;
					if (ide >= total_id_space+1)
					{
						ide = ide - (total_id_space + 1);
					}
					else
						ide = ide;

					if (temp2->avl.is_found(ide))
					{
						temp1->finger_table[j] = temp2->id;
					}

					temp2 = temp2->next;

				} while (temp2 != head);
			}

			temp1 = temp1->next;

		} while ( temp1 != head );
	}
	void insert_data(int e , int startmachine,T da)
	{
		if (e >= 0 && e <= total_id_space && startmachine >= 0 && startmachine <= total_id_space)
		{
			node* temp = head;
			cout << endl << "Path followed : ";
			cout << startmachine;
			bool found = false;
			int next_machine = -1;
			while (temp->id != startmachine)	//approach to start machine
			{
				temp = temp->next;
			}
			found = temp->avl.is_found(e);

			while (!found)
			{
				bool check = true;
				cout << "->";
				if (temp->next != head)
				{
					for (int i = 0; i < (log2(total_id_space + 1)); i++)
					{
						if (temp->finger_table[i] <= e && temp->finger_table[i] > temp->id)
						{
							check = false;
							next_machine = temp->finger_table[i];
						}
					}
				}
				else if (temp->next == head)
				{
					for (int i = 0; i < (log2(total_id_space + 1)); i++)
					{
						if (temp->finger_table[i] <= e)
						{
							check = false;
							next_machine = temp->finger_table[i];
						}
					}
				}

				if (check)
				{
					next_machine = temp->next->id;
				}
				while (temp->id != next_machine)	//approach to start machine
				{
					temp = temp->next;
				}
				found = temp->avl.is_found(e);
				cout << temp->id;
			}
			temp->avl.insert_data(da,e);
			cout << endl;
			char choice;
			cout << "Would you like to print the AVL tree of this machine y/n : ";
			cin >> choice;
			if (choice == 'y' || choice == 'Y')
			{
				cout << "avl : ";
				temp->avl.inOrder();
				cout << endl;
			}
		}
		else
			cout << "Out of Range" << endl;
	}
	node* search(int e, int startmachine)
	{
		if (e >= 0 && e <= total_id_space && startmachine >= 0 && startmachine <= total_id_space)
		{
			node* temp = head;
			cout << endl << "Path followed : ";
			cout << startmachine;
			bool found = false;
			int next_machine = -1;
			while (temp->id != startmachine)	//approach to start machine
			{
				temp = temp->next;
			}
			found = temp->avl.is_found(e);

			while (!found)
			{
				bool check = true;
				cout << "->";
				if (temp->next != head)
				{
					for (int i = 0; i < (log2(total_id_space + 1)); i++)
					{
						if (temp->finger_table[i] <= e && temp->finger_table[i] > temp->id)
						{
							check = false;
							next_machine = temp->finger_table[i];
						}
					}
				}
				else if (temp->next == head)
				{
					for (int i = 0; i < (log2(total_id_space + 1)); i++)
					{
						if (temp->finger_table[i] <= e)
						{
							check = false;
							next_machine = temp->finger_table[i];
						}
					}
				}

				if (check)
				{
					next_machine = temp->next->id;
				}
				while (temp->id != next_machine)	//approach to start machine
				{
					temp = temp->next;
				}
				found = temp->avl.is_found(e);
				cout << temp->id;
			}
			return temp;
		}
		else
			cout << "Out of Range" << endl;
			
	}
	void prin_routing_table( int k )
	{
		node* tem = search(k, head->id);
		cout << endl;
		cout << "Routing table : ";
		for (int i = 0; i < log2(total_id_space + 1); i++)
			cout << tem->finger_table[i] << " ";

		cout << endl;
	}
	void print_avl_line(int key)
	{
		node* tem = search(key, head->id);
		cout << endl;
		cout << "avl : ";
		tem->avl.inOrder();
		cout << endl;

		tem->avl.file_line(key);
	}
	void del(int key)
	{
		node* tem = search(key,head->id);
		tem->avl.del(key);
	}
	bool delet( int key )
	{
		bool check = false;
		node* temp = head;
		do
		{
			if (temp->next->id == key)
			{
				check = true;
				break;
			}
			else
				temp = temp->next;

		} while (temp != head);
		if (check)
		{
			node* temp2 = NULL;
			temp2 = temp->next;
			temp->next = temp->next->next;
			delete temp2;
		}

		return check;
	}
};


int main()
{
    int size_id_space = -1;
	int no_of_machines = 0;
    char choice;
    cout << "Please Enter the size of identifier space in bits : ";
    cin >> size_id_space;
    for (int i = 0; i < size_id_space; i++)
    {
        total_id_space *= 2;
    }
    total_id_space -= 1;
    cout << "Please Enter the number of machines : ";
    cin >> no_of_machines;
    cout << "Would you like to assign ID to each machine press y/n : ";
    cin >> choice;
    singlylinkedlist<int> obj;       //object of singly circular linked list
    if ( choice == 'y' || choice == 'Y')
    {
        int id = -1;
        for ( int i = 0 ; i < no_of_machines ; i++ )
        {
            cout << "Please Enter the id of machine " << i + 1 << " : ";
            cin >> id;
            while (id < 0 || id > total_id_space)
            {
                cout << "Out of range Please enter id of machine "<<i+1<<" again : ";
                cin >> id;
            }
            obj.insert(id);
        }
    }
    else if( choice == 'n' || choice == 'N')
    {
		cout << "Auto Machine IDs : ";
        int diff = -1;
        diff = (total_id_space) / no_of_machines;
        for (int i = diff, j = 0; j < no_of_machines; i+=diff,j++)
        {
            obj.insert(i);
			cout << i << " ";
        }
		cout << endl;
    }
label:
	choice = 'y';
	while (choice == 'y' || choice == 'Y')
	{
		obj.make_avls();
		obj.display();
		cout << endl << "wanna insert data y/n : ";
		cin >> choice;
		while (choice == 'y' || choice == 'Y')
		{
			int key = -1, node_from = -1;
			int value = -1;					//type dependant
			cout << "Please Enter key of machine at which you wanna insert data : ";
			cin >> key;
			cout << "Please Enter value you wanna insert on machine : ";
			cin >> value;
			cout << "Please Enter the value of machine from which you wanna start lookup : ";
			cin >> node_from;
			obj.insert_data(key, node_from, value);

			cout << "Wanna insert more data y/n : ";
			cin >> choice;

		}
		/*	int e, lookup;
			cin >> e;
			cin >> lookup;
			obj.searche(e, lookup);*/
		cout << endl << "wanna del data y/n : ";
		cin >> choice;
		while (choice == 'y' || choice == 'Y')
		{
			int key = -1;
			cout << "Please Enter ID of that particular machine : ";
			cin >> key;
			obj.del(key);

			cout << endl << "Wanna del more data y/n : ";
			cin >> choice;
		}
		cout << endl << "Wanna print routing table of any machine y/n : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			int key = -1;
			cout << "Please Enter ID of that particular machine : ";
			cin >> key;
			obj.prin_routing_table(key);

		}
		cout << endl << "Wanna file name and data of any machine along with its AVL  y/n : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			int key = -1;
			cout << "Please Enter ID of that particular machine : ";
			cin >> key;
			obj.print_avl_line(key);

		}
		cout << endl << "Wanna add a new machine without disturbing ring DHT  y/n : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			int id;
			cout << "Please Enter ID of new machine : ";
			cin >> id;
			obj.insert(id);
		}
	}
	cout << endl << "Wanna del a machine without disturbing ring DHT  y/n : ";
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		int key = -1;
		bool check = false;
		cout << "Please id of that machine : ";
		cin >> key;
		check = obj.delet(key);
		if (check)
		{
			goto label;
		}
	}
	
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

