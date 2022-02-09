//Rasul Iskandarov 10.01.2022
#include <iostream>                                 
#include <string>
using namespace std;

struct Node* allTracks = NULL;
struct Node* recentTracks = NULL;

struct Node {
    string author;
    string music;
    struct Node* next;
    struct Node* prev;
};

void addMusic(struct Node** head, string author, string music)
{
    struct Node* current = *head;
    struct Node* newData = new Node;

    newData->author = author;
    newData->music = music;
    newData->next = NULL;

    if (*head != NULL) {
        while (current->next != NULL)
            current = current->next;

        current->next = newData;
        newData->prev = current;

        return;
    }
    else
    {
        newData->prev = NULL;
        *head = newData;
        return;
    }
}

void listAll(struct Node* node) {
    int index = 1;

    if (node == NULL)
    {
        cout << "Empty list." << endl << endl;
        return;
    }

    while (node != NULL) {
        cout << "| Music #"  << index << endl;
        cout << "| Author: " << node->author << endl;
        cout << "| Music:  " << node->music << endl << endl;

        index++;
        node = node->next;
    }
     return;
}

void playMusic(struct Node** head)
{
    int search;
    int index = 1;
    struct Node* node = *head;

    listAll(node);
    cout << "Choose index of music which you want to play:" << endl;
    cin >> search;

    while (node != NULL && index != search) {
        index++;
        node = node->next;
    }

    if (node != NULL)
    {
        addMusic(&recentTracks, node->author, node->music);
        cout << "Let's go! Music is playing...";
    }
    else
    {
        cout << "Chosen music not found." << endl << endl;
    }
}

void changeOrder(struct Node** head, int oldPosition, int newPosition)
{
    int index = 1;
    struct Node* mainNode = *head;
    struct Node* affectedNode = *head;

    while (mainNode != NULL && index != oldPosition) {
        index++;
        mainNode = mainNode->next;
    }

    if (mainNode == NULL)
    {
        cout << "Chosen positions (" << oldPosition << ") not found." << endl << endl;
        return;
    }

    index = 1;

    while (affectedNode != NULL && index != newPosition) {
        index++;
        affectedNode = affectedNode->next;
    }

    if (affectedNode == NULL)
    {
        cout << "Chosen positions (" << newPosition << ") not found." << endl << endl;
        return;
    }

    if (oldPosition > newPosition)
    {
        if (mainNode->prev != NULL)
            mainNode->prev->next = mainNode->next;

        if (mainNode->next != NULL)
            mainNode->next->prev = mainNode->prev;

        if (affectedNode->prev != NULL)
            affectedNode->prev->next = mainNode;

        mainNode->prev = affectedNode->prev;
        mainNode->next = affectedNode;
        affectedNode->prev = mainNode;
    }

    if (oldPosition < newPosition)
    {
        if (mainNode->prev != NULL)
            mainNode->prev->next = mainNode->next;

        if (mainNode->next != NULL)
            mainNode->next->prev = mainNode->prev;



        if (affectedNode->next != NULL)
            affectedNode->next->prev = mainNode;

        mainNode->next = affectedNode->next;
        affectedNode->next = mainNode;
        mainNode->prev = affectedNode;
    }

    while(mainNode->prev != NULL)
    {
        mainNode = mainNode->prev;
    }

    *head = mainNode;
}

void shuffle()
{
    int count = 1;
    int times = 0;
    struct Node* node = allTracks;

    if (node == NULL)
    {
        cout << "Empty list." << endl << endl;
        return;
    }

    while (node != NULL) {
        count++;
        node = node->next;
    }
    
    times = count;

    while (times>0)
    {
        int num1 = rand() % (count) + 1;
        int num2 = rand() % (count) + 1;

        if(num1 != num2 && num1 < count && num2 < count)
            changeOrder(&allTracks,num1,num2);

        times--;
    }
}

void main() {
    bool menu = true;
    int option = 0;
    string author;
    string music;

    addMusic(&allTracks, "Track 1", "Money");
    addMusic(&allTracks, "2 Cent", "Iron");
    addMusic(&allTracks, "3 West", "Money");
    addMusic(&allTracks, "4 Cent", "Iron");
    addMusic(&allTracks, "5 West", "Money");


    while (menu) {					

        cout << "\n";
        cout << "_________________________________________________\n";
        cout << "|\t\t\t\t\t\t|\n";
        cout << "|\tChoose Task Number\t\t\t|\n";
        cout << "|\t\t\t\t\t\t|\n";
        cout << "|\t1. Add Music\t\t\t\t|\n";
        cout << "|\t2. Play Music\t\t\t\t|\n";
        cout << "|\t3. Show all tracks\t\t\t|\n";
        cout << "|\t4. Shuffle Tracks\t\t\t|\n";
        cout << "|\t5. Show recent played tracks\t\t|\n";
        cout << "|\t6. Change the order of tracks\t\t|\n";
        cout << "|\t\t\t\t\t\t|\n";
        cout << "|\t! Enter other digit to exit program !\t|\n";
        cout << "_________________________________________________\n\n";

        cin >> option;

        cout << endl << endl;

        switch (option)
        {
            default:
                menu = false;
                cout << "Program Exiting...\n";
                break;

            case 1:
                cout << "Enter name of author" << endl;
                cin >> author;
                getline(cin,author);
                
                cout << "Enter name of music" << endl;
                getline(cin, music);

                addMusic(&allTracks, author, music);
                break;

            case 2:
                playMusic(&allTracks);
                break;

            case 3:
                cout << "List of all tracks:" << endl << endl;
                listAll(allTracks);
                break;

            case 4:
                shuffle();
                break;

            case 5:
                cout << "Recently Played tracks:" << endl << endl;
                listAll(recentTracks);
                break;

            case 6:

                int oldPosition, newPosition;

                listAll(allTracks);

                cout << "Choose index of music:" << endl;
                cin >> oldPosition;

                cout << endl << "Choose new index of music:" << endl;
                cin >> newPosition;

                cout << endl; 

                changeOrder(&allTracks, oldPosition, newPosition);

                break;
        }
    }
}