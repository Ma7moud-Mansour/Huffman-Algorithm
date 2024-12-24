#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class cNode
{
public:
	int val;
    char charr;
    string Code;
	cNode* pRight;
	cNode* pLeft;
	cNode* pNext;
	
	cNode()
	{
		val = 0;
		pRight = NULL;
		pLeft = NULL;
		pNext = NULL;
	}
};

class cList
{
public:
	cNode* pHead;
	cNode* pTail;

    cList()
    {
        pHead = NULL;
        pTail = NULL;
    }
    void attach(cNode* pnn)
    {
        if (pHead == NULL)
        {
            pHead = pTail = pnn;
        }
        else
        {
            cNode* pTrav = pHead;
            cNode* pBack = NULL;
            while (pTrav != NULL && pnn->val > pTrav->val)
            {
                pBack = pTrav;
                pTrav = pTrav->pNext;
            }
            pnn->pNext = pTrav;
            if (pBack != NULL)
            {
                pBack->pNext = pnn;
            }
            else
            {
                pHead = pnn;
            }
            if (pBack == pTail)
            {
                pTail = pnn;
            }
        }
    }
    void display()
    {
        cNode* temp = pHead;
        cout << "===============THIS IS COUNT OF EVERY LETTER==================" << endl;
        while (temp != NULL)
        {
            cout << temp->val << "" << temp->charr << " ";
            temp = temp->pNext;
        }
        cout << endl << "=============================================================="<< endl;
    }
    cNode* popfirst()
    {  
        cNode* pTemp;
        pTemp = pHead;
        pHead = pHead->pNext;
        return pTemp;
    }

    //DISPLAY FUNCTION FOR TREE VIEW
    void display(cNode* ptrav, int F)
    {
        if (ptrav == NULL)
        {
            return;
        }
        for (int i = 0; i < F; i++)
        {
            cout << '\t';
        }
        cout << ptrav->val;
        cout << ptrav->charr << endl;
        F++;
        display(ptrav->pLeft, F);
        display(ptrav->pRight, F);
    }

    //DISPLAY FUNCTION FOR CODING LETTERS
    void display2(cNode* ptrav, string code)
    {
        if (ptrav == NULL)
        {
            return;
        }
        ptrav->Code = code;
        display2(ptrav->pLeft, code+"0");
        display2(ptrav->pRight, code+"1");
    }


    //DISPLAY BINARY CODE
    void displayCode(cNode* ptrav)
    {
        if (ptrav == NULL)
        {
            return;
        }
        if (ptrav->pRight == NULL && ptrav->pLeft == NULL)
        {
            cout << ptrav->charr << "->" << ptrav->Code << endl;
        }
        
        displayCode(ptrav->pLeft);
        displayCode(ptrav->pRight);
    }
};

void main()
{
    cList List;
    string file = "file.txt";
    string line;
    char L[256], Ct[256];
    char Letter = 0;
    int ct = 0;
    /*
    ===================================================
    ===========READ FILE AND COUNT LETTERS=============
    ===================================================
    */
    for (int i = 0; i < 256; i++)
    {
        L[i] = Letter;
        ifstream inFile(file);
        if (inFile.is_open()) 
        {
            while (getline(inFile, line)) 
            {
                for (int k = 0; k < line.length(); k++)
                {
                    if (Letter == line[k])
                    {
                        ct++;
                    }
                }
            }
        }
        else{ cout << "Error: Could not open file " << file << endl;}
        Ct[i] = ct;
        if (ct != 0)
        {
            cNode* pnn = new cNode;
            pnn->val = ct;
            pnn->charr = Letter;
            List.attach(pnn);
        }
        //===============
        ct=0;
        Letter++;
    }
    List.display();
    //--------FINISHED-----------


    /*
    ===================================================
    ===============MAKE A BINARY TREE==================
    ===================================================
    */
    while (List.pHead != List.pTail)
    {
        cNode* pnn = List.popfirst();
        cNode* pnn2 = List.popfirst();
        cNode* Dad = new cNode;
        Dad->val = pnn->val + pnn2->val;
        Dad->pLeft = pnn;
        Dad->pRight = pnn2;
        List.attach(Dad);
    }
    cout << "==================THIS IS OUR TREE DISPLAY====================" << endl;
    List.display(List.pHead, 0);
    cout << "==============================================================" << endl;
    //--------------FINISHED------------------


    /*
    ===================================================
    ===============MAKE A BINARY CODE==================
    ===================================================
    */
    cout << "==================THIS IS OUR CODE DISPLAY====================" << endl;
    List.display2(List.pHead, "\0");
    List.displayCode(List.pHead);
    cout << "==============================================================" << endl;
    cout << "THANK YOU FOR YOUR TIME \nAND SPECIAL THANKS TO OUR PROFFESOR DR/AHMED FAROUK \nBY MAHMOUD ABDELKAREEM ";
}