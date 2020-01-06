// ProiectMihaescu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class nod // retine un caracter dintr-un cuvant
{
public:
	char value;
	bool isWord;
	nod* left, * equal, * right; 
	nod(char value = 0)
	{
		this->value = value;
		left = NULL;
		equal = NULL;
		right = NULL;
		isWord = 0;
	}
	nod(char value, nod* left, nod* equal, nod* right)
	{
		this->value = value;
		this->left = left;
		this->equal = equal;
		this->right = right;
	}

};


void addWord(nod **root,string &cuvant, int poz) 
{
	
	//Functia cauta cel mai mare prefix comun al tuturor cuvintelor si adauga restul cuvantului in functie de nodurile deja completate
	
	if ((*root) == NULL) // daca nodul nu a fost creat, il cream si ii atribuim valoarea cuvant[poz]
		(*root) = new nod(cuvant[poz]);
	
	if (cuvant[poz] == (*root)->value) // daca avem acelasi caracter
	{									
		if (poz + 1 < cuvant.size()) // daca inca nu am ajuns la capatul cuvantului
			addWord(&(*root)->equal, cuvant, poz + 1);
		else
			(*root)->isWord = 1;
	}
	else
	{
		if (cuvant[poz] < (*root)->value) // daca valoarea din nodul actual este mai mare decat caracterul pe care vrem sa-l adaugam, apelam functia pentru nodul din stanga 
		{
			addWord(&(*root)->left, cuvant, poz);
		}
		else {
			if (cuvant[poz] > (*root)->value)// altfel pentru nodul din dreapta
			{ 
				addWord(&(*root)->right, cuvant, poz);
			}
		}
	}

}

bool findWord(string &cuvant, nod** root, int poz) {
	/*
	Functioneaza la fel ca addWord, doar ca atunci cand nodul curent este null, inseamna ca nu a gasit cuvantul in dictionar,
	altfel, daca ajunge la capatul cuvantului, returneaza variabila isWord
	*/

	if ((*root) == NULL)
		return 0;

	if ((*root)->value == cuvant[poz]) {
		if (poz+1 < cuvant.size())
			findWord(cuvant, &(*root)->equal, poz + 1);
		else
			return (*root)->isWord;
	}
	else {
		if ((*root)->value < cuvant[poz]) {
			findWord(cuvant, &(*root)->right, poz);
		}
		else
		{
			if ((*root)->value > cuvant[poz]) {
				findWord(cuvant, &(*root)->left, poz);
			}
		}
	}
}



void notInDictionary(nod* root)
{
	//cauta cuvintele care nu sunt in dictionar
	string buff, token;
	cin.ignore(100, '\n');
	getline(cin, buff); //citeste o linie in buff
	istringstream iss(buff); // deschide un stringstream cu continutul din buff
	while (getline(iss, token, ' ')) // in token pune fiecare cuvant din buff
	{
		if (!findWord(token, &root, 0)) // cauta token in TST si daca nu exista il afiseaza
		{
			cout << token << '\n';

		}
	}
	
}

int main()
{
	nod* root = NULL;
	string testIn, buff;
	cout << "Nume fisier intrare(exemplu test.in):";
	cin >> testIn; // numele fisierului de intrare
	ifstream fin(testIn);
	while (fin >> buff)
		addWord(&root, buff, 0); // citeste dictionarul din fisier

	
	notInDictionary(root);//citeste un string de la tastatura si il sparge in cuvinte, cautand fiecare cuvant in trie, 
							//afisand cuvintele care nu sunt in dictionar






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
