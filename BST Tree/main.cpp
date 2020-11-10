#include "main.h"
#include<iostream>
#include"BST.h"
#include"BSTNode.h"
#include<string>

using namespace std;

int main() {

	//BSTNode<int>* root = nullptr;
	//BST<int> bst;
	//bst.insert(bst.root, 10);
	//bst.insert(bst.root, 20);
	//bst.insert(bst.root, 5);
	//bst.insert(bst.root, 12);
	//bst.insert(bst.root, 7);
	//bst.insert(bst.root, 2);
	//bst.inorder();

	////test funkcji inorder
	//cout << "Wypisz drzewo w porz¹dku 'in order' " << endl;
	//bst.inorder(bst.root);

	////test funkcji search
	//cout << "Czy w drzewie jest wartoœæ 5? Jeœli tak, wyœwietl t¹ wartoœæ" << endl;
	//cout << bst.search(bst.root, 5)->key << endl;

	////test funkcji iterative search
	//cout << "Czy w drzewie jest wartoœæ 5? Jeœli tak, wyœwietl t¹ wartoœæ" << endl;
	//cout << bst.iterative_search(bst.root, 5)->key << endl;

	////test funkcji minimum
	//cout << "Jaka wartoœæ wêz³a w drzewie jest najmniejsza?" << endl << bst.minimum(bst.root)->key << endl;

	////test funkcji maksimum
	//cout << "Jaka wartoœæ wêz³a w drzewie jest najwiêksza?" << endl << bst.maximum(bst.root)->key << endl;

	////test ustawieñ parenta
	//cout << "Rodzicem wêz³a '10' jest: " << bst.search(bst.root, 10)->parent << endl;
	//cout << "Rodzicem wêz³a '5' jest: " << bst.search(bst.root, 5)->parent->key << endl;
	//cout << "Rodzicem wêz³a '12' jest: " << bst.search(bst.root, 12)->parent->key << endl;
	//cout << "Rodzicem wêz³a '7' jest: " << bst.search(bst.root, 7)->parent->key << endl;


	////test funkcji successor
	//cout << "Poprzednikiem wêz³a o wartoœci 5 jest:  " << bst.successor(bst.iterative_search(bst.root,7))->key << endl;
	//cout << "Poprzednikiem wêz³a o wartoœci 2 jest:  " << bst.successor(bst.iterative_search(bst.root, 2))->key << endl;
	//cout << "Poprzednikiem wêz³a o wartoœci 12 jest:  " << bst.successor(bst.iterative_search(bst.root, 12))->key << endl;

	////test usuwania
	//cout << "Usuñ z drzewa wêze³ o wartoœci 5 i wypisz nowe drzewo" << endl;
	//bst.remove(bst.root, bst.search(bst.root, 5));
	//bst.inorder(bst.root);



	//cout << "Usuñ z drzewa wêze³ o wartoœci 12 i wypisz nowe drzewo" << endl;
	//bst.remove(bst.root, bst.search(bst.root, 12));
	//bst.inorder(bst.root);

	//cout << "Usuñ z drzewa wêze³ o wartoœci 7 i wypisz nowe drzewo" << endl;
	//bst.remove(bst.root, bst.search(bst.root, 7));
	//bst.inorder(bst.root);

	//cout << "Usuñ z drzewa wêze³ o wartoœci 20 i wypisz nowe drzewo" << endl;
	//bst.remove(bst.root, bst.search(bst.root, 20));
	//bst.inorder(bst.root);

	//cout << "Usuñ z drzewa wêze³ o wartoœci 10 i wypisz nowe drzewo" << endl;
	//bst.remove(bst.root, bst.search(bst.root, 10));
	//bst.inorder(bst.root);

	//bst.insert(1);
	//bst.insert(1);
	//bst.insert(8);
	//bst.insert(4);
	//bst.insert(12);
	//bst.insert(8);
	//bst.insert(9);
	//bst.insert(4);
	//bst.insert(2);
	//bst.insert(14);
	//bst.insert(4);
	//bst.insert(3);
	//bst.insert(90);
	//bst.insert(32);
	//bst.inorder();
	//cout << endl;

	//BST<int> bst2 = bst;
	//bst2.inorder();

	//bst.remove(bst.search(3));
	//bst.remove(bst.search(90));
	//bst.remove(bst.search(4));

	//bst.inorder();
	//cout << endl;
	//bst2.inorder();

	BST<int> bst;
	int tablica[] = { 3,5,12,13,6,1,9,4,2,16,8,20 };
	for (int i = 0; i < 11; i++) {
		bst.insert(tablica[i]);
	}
	//bst.inorder();
	//puts("");

	BST<int> bst2 = bst;
	bst2.inorder();
	bst.remove(bst.search(3));
	bst.remove(bst.search(5));
	bst.remove(bst.search(12));
	bst.remove(bst.search(16));
	bst.inorder();
	bst2.inorder();



	return 0;
}