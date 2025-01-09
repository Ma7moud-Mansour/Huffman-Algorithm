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
        cout << endl << "==============================================================" << endl;
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
        display2(ptrav->pLeft, code + "0");
        display2(ptrav->pRight, code + "1");
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

    void CodeList(cNode* ptrav, cList& COD)
    {
        if (ptrav == NULL)
        {
            return;
        }
        if (ptrav->pRight == NULL && ptrav->pLeft == NULL)
        {
            cNode* pnn = new cNode;
            pnn->charr = ptrav->charr;
            pnn->Code = ptrav->Code;
            COD.attach(pnn);
        }

        CodeList(ptrav->pLeft, COD);
        CodeList(ptrav->pRight, COD);
    }

    void DisplayCodeList(cNode* ptrav)
    {
        while (ptrav != NULL)
        {
            cout << ptrav->charr << ',' << ptrav->Code << endl;
            ptrav = ptrav->pNext;
        }
    }
};

void main()
{
    cList List, COD;
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
            int m = 0;
            while (getline(inFile, line))
            {
                for (int k = 0; k < line.length(); k++)
                {
                    if (Letter == line[k])
                    {
                        ct++;
                    }
                }
                m++;
            }
            if (i == 10)
            {
                ct = m - 1;
            }
        }
        else { cout << "Error: Could not open file " << file << endl; }
        Ct[i] = ct;
        if (ct != 0)
        {
            cNode* pnn = new cNode;
            pnn->val = ct;
            pnn->charr = Letter;
            List.attach(pnn);
        }
        //===============
        ct = 0;
        Letter++;
        inFile.close();
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
    //================================================END OF PHASE ONE====================================================
    // 
    //====================================================PHASE #2========================================================

        //Create List For Every Letter And His Code
    List.CodeList(List.pHead, COD);

    /*
    ===================================================
    ==================COMPERSSION======================
    ===================================================
    */

    //HASHING

    string cd, Hash;
    int temp = 0;
    int count = 7;
    int cnt = 0;
    int Bitt;
    ifstream inFile(file, ios::binary);
    if (inFile.is_open())
    {
        inFile.seekg(0, inFile.end);
        int h = inFile.tellg();
        cout << h;
        inFile.seekg(0, inFile.beg);
        char ch;
        for (int i = 0; i < h; i++)
        {
            inFile.read(&ch, 1);
            cNode* ptrav;
            ptrav = COD.pHead;
            while (ptrav != NULL)
            {
                if (ptrav->charr == ch)
                {
                    cd = ptrav->Code;
                    break;
                }
                ptrav = ptrav->pNext;
            }
            for (int i = 0; i < cd.length(); i++)
            {
                if (cd[i] == '1')
                {
                    temp = temp | (1 << count);
                }
                count--;
                if (count < 0)
                {
                    count = 7;
                    Hash += temp;
                    temp = 0;
                }
            }
            cd.clear();
        }
        if (count != 7)
        {
            Hash += temp;
        }
        Hash += (7 - count);
    }
    else { cout << "Error: Could not open file " << file << endl; }

    ofstream MyFile("Hash.txt");
    if (MyFile.is_open())
    {
        MyFile << Hash;
        MyFile.close();
    }
    else { cout << "Error: Could not open file " << file << endl; }
    // END OF HASHING

    /*
    ===================================================
    =================DeCOMPERSSION=====================
    ===================================================
    */
    string temp2;
    int cut = 0;
    ifstream inFilee(file);
    if (inFilee.is_open())
    {
        int i = 0;
        while (getline(inFilee, line))
        {
            if (i != 0)
            {
                cut++;
            }
            for (int k = 0; k < line.length(); k++)
            {
                cut++;
            }
            cut++;
        }
    }
    ofstream DC("DC.txt");
    int ctt = 0;
    ifstream HashFile("Hash.txt", ios::binary);
    if (HashFile.is_open())
    {
        HashFile.seekg(0, HashFile.end);
        int h = HashFile.tellg();
        HashFile.seekg(0, HashFile.beg);
        char ch;
        char x;
        for (int i = 0; i < h; i++)
        {
            HashFile.read(&ch, 1);
            ct = 8;
            if (i == h - 2)
            {
                HashFile.read(&x, 1);
                unsigned char a = x;
                ct = int(a);
            }
            for (int k = 7; k >= 0 && ct > 0; k--, ct--)
            {
                if ((ch & (1 << k)) != 0)
                {
                    temp2 += '1';
                }
                else
                {
                    temp2 += '0';
                }
                cNode* ptrav;
                ptrav = COD.pHead;
                while (ptrav != NULL)
                {
                    if (temp2 == ptrav->Code && ctt <= cut)
                    {
                        DC << ptrav->charr;
                        temp2 = "";
                        ctt++;
                        break;
                    }
                    ptrav = ptrav->pNext;
                }
            }
            if (i == h - 2)
            {
                break;
            }
        }
        DC << endl;
    }
}