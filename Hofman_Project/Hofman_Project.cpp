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
int isfound(char c, cList& L) {
    cNode* ptrav = L.pHead;
    while (ptrav != NULL) {
        if (ptrav->charr == c) {
            return 1;
        }
        ptrav = ptrav->pNext;
    }
    return 0;
}
void main()
{
    cList List, COD;
    string file = "Trail.bmp";
    string line;
    char L[256], Ct[256];
    char Letter = 0;
    int ct = 0;
    /*
    ===================================================
    ===========READ FILE AND COUNT LETTERS=============
    ===================================================
    */
    ifstream inFile(file, ifstream::binary);
    if (inFile.is_open())
    {
        int m = 0;
        char c;
        inFile.seekg(0, inFile.end);
        int h = inFile.tellg();
        inFile.seekg(0, inFile.beg);
        for (int i = 0; i < h; i++)
        {
            inFile.read(&c, 1);
            if (isfound(c, List))
            {
                cNode* ptrav = List.pHead;
                while (ptrav != NULL)
                {
                    if (ptrav->charr == c)
                    {
                        ptrav->val++;
                    }
                    ptrav = ptrav->pNext;
                }
            }
            else
            {
                cNode* pnn = new cNode;
                pnn->val = 1;
                pnn->charr = c;
                List.attach(pnn);
            }
        }
        inFile.close();
    }
    else { cout << "Error: Could not open file " << file << endl; }
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

    string cd;
    char temp = 0;
    int count = 7;
    int cnt = 0;
    int Bitt;
    ifstream inFile2(file, ifstream::binary);
    ofstream MyFile("Hash.txt", ofstream::binary);
    if (inFile2.is_open())
    {
        inFile2.seekg(0, inFile2.end);
        int h = inFile2.tellg();
        cout << h;
        inFile2.seekg(0, inFile2.beg);
        char ch;
        for (int i = 0; i < h; i++)
        {
            inFile2.read(&ch, 1);
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
                    MyFile.write(&temp, 1);
                    temp = 0;
                }
            }
            cd.clear();
        }
        if (count != 7)
        {
            MyFile.write(&temp, 1);
        }
        char Hash = (7 - count);
        MyFile.write(&Hash, 1);
        inFile2.close();
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
    ofstream DC("DC.bmp", ofstream::binary);
    ifstream HashFile("Hash.txt", ifstream::binary);
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
                    if (temp2 == ptrav->Code)
                    {
                        if (i == 2825)
                        {
                            int y = 1;
                        }
                        if (ptrav->charr == 26)
                        {
                            int x = 1;
                        }
                        DC.write(&ptrav->charr, 1);
                        temp2 = "";
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
        HashFile.close();
        DC.close();
    }
    ifstream DC2("DC.bmp", ifstream::binary);
    ifstream Tr("Trail.bmp", ifstream::binary);
    Tr.seekg(0, Tr.end);
    int h = Tr.tellg();
    Tr.seekg(0, Tr.beg);
    char c1, c2;
    for (int i = 0; i < h; i++)
    {
        DC2.read(&c1, 1);
        Tr.read(&c2, 1);
        if (c1 != c2)
        {
            cout << i;
        }
    }
}