/* Binary Search Tree (BST) basic operations: Create,Insert,Delete,Search,Preorder Traversal,Postorder Traversal,Inorder Traversal and dot language */

#include <iostream>
#include <list>
using namespace std;

 

/* Defining node structure */

struct node

{

    int data;

    struct node *leftSubtree, *rightSubtree;

};

 

/* Creating a new node by assigning data, leftSubtree & leftSubtree as NULL*/

struct node *new_Node(int data)

{

    struct node *temp = (struct node *)malloc(sizeof(struct node));

    temp->data = data;

    temp->leftSubtree = temp->leftSubtree = NULL;

    return temp;

}

 

/* Binary Search Tree Preorder Traversal */

void printBST(struct node *rootNode)

{

    if (rootNode == NULL)

        return;

 

    /* data of rootNode */

    cout << rootNode->data << " ";

 

    /* data of leftSubtree */

    printBST(rootNode->leftSubtree);

 

    /* data of rightSubtree */

    printBST(rootNode->rightSubtree);

}

/* Binary Search Tree Postorder Traversal */

void printPostOrderBST(struct node *rootNode)

{

    if (rootNode == NULL)

        return;

    /* data of leftSubtree */

    printPostOrderBST(rootNode->leftSubtree);

 

    /* data of rightSubtree */

    printPostOrderBST(rootNode->rightSubtree);
    
    /* data of rootNode */

    cout << rootNode->data << " ";
}

/* Binary Search Tree Inorder Traversal */

void printInOrderBST(struct node *rootNode)

{

    if (rootNode == NULL)

        return;

    /* data of leftSubtree */

    printInOrderBST(rootNode->leftSubtree);

    /* data of rootNode */

    cout << rootNode->data << " ";

    /* data of rightSubtree */

    printInOrderBST(rootNode->rightSubtree);
    
    
}
 

/* Inserting a new node into BST */

struct node *insertNode(struct node *rootNode, int data)

{

    /*check if the BST is empty, if empty return the new Node */

    if (rootNode == NULL)

    {

        return new_Node(data);

    }

    else

    {

        /*

        check if data is less than the rootNode data.

        if yes, Traverse through the leftSubtree and insert the new node

        else  Traverse through the rightSubtree and insert the new node

        */

        if (data < rootNode->data)

            rootNode->leftSubtree = insertNode(rootNode->leftSubtree, data);

        else

            rootNode->rightSubtree = insertNode(rootNode->rightSubtree, data);

    }

    return rootNode;

}

 

struct node *findMinValue(struct node *rightSubtree)

{

    struct node *currNode = rightSubtree;

 

    /* Finding the leftmost leaf node of rightSubTree */

    while (currNode && currNode->leftSubtree != NULL)

        currNode = currNode->leftSubtree;

 

    return currNode;

}

 

/* Deleting the specified node & re-constructing BST */

struct node *deleteNode(struct node *rootNode, int key)

{

    /* searching for the node to be deleted */

    if (key < rootNode->data)

    {

        rootNode->leftSubtree = deleteNode(rootNode->leftSubtree, key);

    }

    else if (key > rootNode->data)

    {

        rootNode->rightSubtree = deleteNode(rootNode->rightSubtree, key);

    }

    else

    {

        /* If the rootNode has only 1 or 0 children on leftSubTree/rightSubTree */

        if (rootNode->rightSubtree == NULL)

        {

            struct node *tempNode = rootNode->leftSubtree;

            free(rootNode);

            return tempNode;

        }

        else if (rootNode->leftSubtree == NULL)

        {

            struct node *tempNode = rootNode->rightSubtree;

            free(rootNode);

            return tempNode;

        }

 

        /* If the rootNode has only 2 children */

        struct node *tempNode = findMinValue(rootNode->rightSubtree);

 

        /* positining the in-order successor in the position of the node to be deleted */

        rootNode->data = tempNode->data;

 

        /* Deleting the in-order successor node */

        rootNode->rightSubtree = deleteNode(rootNode->rightSubtree, tempNode->data);

    }

    return rootNode;

}

/* print dot language of BST with preorder form */

string printBSTdotLang(struct node *rootNode){
    string finalFile = "digraph bst{\n";
    struct node *currentNode = rootNode;
    int nVal=0;
    list<struct node*> listNodes;
    while(currentNode!=nullptr | !listNodes.empty()){
        if (currentNode!=nullptr){
            listNodes.push_back(currentNode);
            if(currentNode->leftSubtree!=nullptr){
                finalFile += to_string(currentNode->data);
                finalFile += " -> ";
                finalFile += to_string(currentNode->leftSubtree->data);
                finalFile += ";\n";
                
            }
            else{
                finalFile += "nil";
                finalFile += to_string(nVal);
                finalFile += " [shape=point];\n";
                finalFile += to_string(currentNode->data);
                finalFile += " -> nil";
                finalFile += to_string(nVal);
                finalFile += ";\n";
                nVal+=1;
            }
            currentNode = currentNode->leftSubtree;
        }
        else{
            struct node *iNode = listNodes.back();
            listNodes.pop_back();
            if(iNode->rightSubtree!=nullptr){
                finalFile += to_string(iNode->data);
                finalFile += " -> ";
                finalFile += to_string(iNode->rightSubtree->data);
                finalFile += ";\n";
            }
            else{
                finalFile += "nil";
                finalFile += to_string(nVal);
                finalFile += " [shape=point];\n";
                finalFile += to_string(iNode->data);
                finalFile += " -> nil";
                finalFile += to_string(nVal);
                finalFile += ";\n";
                nVal+=1;
            }
            currentNode = iNode->rightSubtree;
        }
    }
    finalFile += "}\n";
    return finalFile;
}
 

/* Search for a given data in BST */

int searchBST(node *rootNode, int item)

{

    int level = 0;

    struct node *tempNode = rootNode;

    /* traverse the tree until tempNode points to NULL */

    while (tempNode != NULL)

    {

        level++;

        if (tempNode->data == item)

        {

            cout << "\n Item found at level: " << level << "!!!";

            return 1;

        }

        /* checking leftSubtree */

        else if (tempNode->data > item)

        {

            tempNode = tempNode->leftSubtree;

        }

        /* checking rightSubtree */

        else

        {

            tempNode = tempNode->rightSubtree;

        }

    }

 

    cout << "\n Item doesn't exist in the BST !!";

    return 0;

}

 

/* Execution start point */

int main()

{

    int choice, item,checkifEleExists;

    // creating & assigning root Node as NULL

    struct node *rootNode = NULL;

    while (1)

    {

        cout << "\n1.Insert Element " << endl;

        cout << "2.Delete Element " << endl;

        cout << "3.Search Element" << endl;

        cout << "4.Preorder Traversal" << endl;
        
        cout << "5.PostOrder Traversal" << endl;
        
        cout << "6.InOrder Traversal" << endl;
        
        cout << "7.Quit without printing dot language code " << endl;
        cout << "Enter other values (above 7) to print BST as dot language in console and exit successfully" << endl;

        cout << "Enter your choice : ";

        cin >> choice;

        switch (choice)

        {

            /* creating a BST by inserting nodes */

        case 1:

            cout << "Enter the number to be inserted : ";

            cin >> item;

            /* check if item already exists in BST */

            checkifEleExists = searchBST(rootNode, item);

            if(!checkifEleExists)

            {

              cout<<"Hence, inserting the item!!";

              rootNode = insertNode(rootNode, item);

            }

            else {

            cout<<"element already exists!!";

            }

            break;

            /* deleting a specific element if tree is not empty & element exists*/

        case 2:

            if (rootNode == NULL)

            {

                cout << "Tree is empty, nothing to delete" << endl;

                continue;

            }

            cout << "Enter the number to be deleted : ";

            cin >> item;

             /* check if item exists in BST */

            checkifEleExists = searchBST(rootNode, item);

            if(checkifEleExists)

            {

              cout<<"Hence, deleting the item!!";

              rootNode = deleteNode(rootNode, item);

            }

            break;

            /* searching a specific element in tree if BST is not empty */

        case 3:

            cout << "Enter the item to be Searched :" << endl;

            cin >> item;

            searchBST(rootNode, item);

            break;

            /* preorder traversal of BST */

        case 4:

            cout << "Preorder Traversal of BST:" << endl;

            printBST(rootNode);

            break;
            
        case 5:
            cout << "PostOrder Traversal of BST:" <<endl;
            
            printPostOrderBST(rootNode);
            break;
            
        case 6:
            cout << "InOrder Traversal of BST:" << endl;
            
            printInOrderBST(rootNode);
            
            break;
        
        /* Quit */

        case 7:
            exit(1);

        default:
            cout << "program exited successfully and below is dot language code " << endl;
            string statement = printBSTdotLang(rootNode);
            cout << statement;
            
            exit(2);

        }

    }
}