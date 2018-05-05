#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<vector>

using namespace std;

class tree
{
	struct node
	{
		char *name;
		vector<node*> children;
		node *parent;
		int level;
	};
	
	node * root;
	node * current;
	
	public:
	
	tree()
	{
		root = current = NULL;
		SetRoot();
	}
	
	void DisplayCurrent(){	cout << " " <<  current->name << endl;	}
	
	void SetRoot()
	{
		char s[30];
		cout << "\n Enter file root name: ";
		cin >> s;
		root = new node;
		root->name = new char[strlen(s)];
		strcpy(root->name,s);
		root->parent = NULL;
		root->level = 0;
		current = root;
	}

	node * search(char s[], node *t)
	{
		if(t == NULL)
			return t;
		
		if(!(strcmp(t->name,s)))
			return t;

		vector<node*> :: iterator i;
		node *p = NULL;
		for(i = t->children.begin(); i!= t->children.end(); i++)
		{
			p = search(s,(*i));
			if(p!=NULL)
				return p;
		}

		return p;
	}
		
	void SetCurrent(char s[])
	{
		node *t = search(s,root);
		
		if(t!=NULL)
		{
			current = t;
			cout << " File found.\n ";
			cout << current->name << endl;
		}

		else
			cout << " Not found.\n";
	}

	node * ReturnCurrent(){	return current;	}
	node * ReturnRoot(){	return root;	}
	node * ReturnParent(){	return current->parent;	}

	void AddChild()
	{
		node * a;
		a = new node;
		cout << " Enter child folder name: ";
		a->name = new char[30];
		cin >> a->name;
		a->parent = current;
		a->level = current->level + 1;
		current->children.push_back(a);
	}

	void spaces(int n)
	{
		n *= 3;
		while(n--)
			cout << ".";
	}
	
	void DisplayChildren()
	{
		vector<node*> :: iterator i;
		for(i = current->children.begin(); i!= current->children.end(); i++)
		{
			spaces((*i)->level);
			cout << (*i)->name << endl;
		}
	}

	void DisplayTree(node *t)
	{
		if(t == NULL)
			return;
		
		cout << endl;
		spaces(t->level);
		cout << t->name;
		if(t == current)
			cout << "  •";

		vector<node*> :: iterator i;
		for(i = t->children.begin(); i!=t->children.end(); i++)
			DisplayTree(*i);
	}

	void DeleteChildren(node *t)
	{
		if(t == NULL)
			return;

		vector<node*> :: iterator i;

		for(i = t->children.begin(); i != t->children.end(); i++)
			this->DeleteChildren(*i);
		
		delete t;
	}
	
	void Delete()
	{
		node * t = current;
		if(current == root)
		{
			cout << "\n Root cannot be deleted.\n";
			cin.get();
			cin.ignore();
			return;
		}

		current = root;
		
		this->DeleteChildren(t);
		
		node *p = t->parent;
		
		vector<node*> :: iterator i;
		for(i = p->children.begin(); i != p->children.end(); i++)
		{
			if((*i) == t)
				break;
		}

		p->children.erase(i);
	}
};

void key()
{
	cin.get();
	cin.ignore();
}

int main()
{
	tree a;
	int ch;
	char s[30];

	while(1)
	{
		system("clear");
		cout << " \n The root folder has been set.\n\n";
		cout << " 1. Add Child \n 2. Display Children \n 3. Set Current \n 4. Display Tree \n 5. Delete file \n\n Enter choice: ";
		cin >> ch;

		switch(ch)
		{
			case 1:
				a.AddChild();
				break;

			case 2:
				a.DisplayChildren();
				key();
				break;

			case 3:
				cout << " Enter folder name: ";
				cin >> s;
				a.SetCurrent(s);
				key();
				break;

			case 4:
				a.DisplayTree(a.ReturnRoot());
				key();
				break;
			
			case 5:
				a.Delete();
				break;
			
			default: break;
		}
	}
	
	return 0;
}












