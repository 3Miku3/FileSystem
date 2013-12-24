#include<iostream>
#include<string.h>
#include<string>
#include<iomanip>
#include <stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<iomanip>
#include"FileSystem.h"
using namespace std;
string error[] = {"/","\\", ":","<",">","|","*","&"} ;  //�����еķǷ��ַ�
FileSystem::FileSystem() {   
    
    currentDir = NULL;
    tempfile = NULL;
    tempdir = NULL;
}
FileSystem::~FileSystem() {      //����
    

    MyDir *d = root;        //ָ���Ŀ¼��ָ��
    MyFile *f = currentDir->fileChain; //��ǰĿ¼�µ��ļ�����ָ��
    while (f != 0) {               //�����ļ����ͷ���Դ
        if (f->nextFile == 0) {
            this->deleteFile(f);
            f = 0;     
            break;    //�����һ���ļ�Ϊ�գ���ɾ������ļ� �������ڴ�
        }
        while (f->nextFile->nextFile != 0)
            f = f->nextFile;   
        this->deleteFile(f->nextFile);
        f->nextFile = 0;
        f = currentDir->fileChain;//�������һ���ļ���Ϊ�գ���ɾ���¸��ļ��������ڴ�
    }
    while (d != 0) {      //�����ļ��У��ͷ���Դ
        if (d->nextDir == 0) {
            this->deleteDir(d);
            d = 0;
            break;
        }
        while (d->nextDir->nextDir != 0)
            d = d->nextDir;
        this->deleteDir(d->nextDir);
        d->nextDir = 0;
        d = root;
    }
}

int FileSystem::newFile() {

    MyFile *p = NULL;
    p = new MyFile;

    if (p == 0) {
        cout << "CREATE           -FALSE";
        return 0;
    }
    cin>>p->name;
    /*�������*/
    string tempname(p->name) ;
    for(int i = 0 ;i< 8 ;++i)
    {
        if(tempname.find(error[i],0)!=string::npos)//���ַ������±�Ϊ0����ʼ����error[i],���û�ҵ�������һ���ر�ı�־c++����npos��ʾ
        {
            cout << "RENAME            -FALSE"<<endl;
            return 0 ;
        }
    }

    /*����ʱ���������
     * 1. Ŀ¼��û���ļ�
     * 2. Ŀ¼�����ļ������ļ�������ͻ
     * 3. Ŀ¼�����ļ������ļ���������ͻ
     * */
    /*�������ͬ������*/
    if (currentDir->fileChain == NULL) {
        p->nextFile = currentDir->fileChain;
        currentDir->fileChain = p;
    } else {
        MyFile *q = new MyFile;
        q = currentDir->fileChain;
        while (q != NULL) {
            if (strcmp(p->name, q->name)==0) {
                cout << "FILE EXISTS             -FALSE" << endl;
                return 0;
            }
            q = q->nextFile;
        }

        /*��������ṹ*/
        p->nextFile = currentDir->fileChain;
        currentDir->fileChain = p;
        MyDir *h = currentDir;

       
    }
    
    cout <<"CREATE             -OK" << endl;
    return 1;
}

int FileSystem::newDir() {
    MyDir *p, *h;
    p = new MyDir;
    cin >> p->name;

    /*�������*/
    string tempname(p->name) ;
    for(int i = 0 ;i< 8 ;++i)
    {
        if(tempname.find(error[i],0)!=string::npos)
        {
            cout << "RENAME              -FALSE"<<endl;
            return 0 ;
        }
    }


    p->dirChain = NULL;
    p->fileChain = NULL;
    p->nextDir = NULL;
    if (currentDir->dirChain == NULL)
        h = NULL;
    else
        h = currentDir->dirChain;

    /*����ʱ���������
     * 1. Ŀ¼��û����Ŀ¼
     * 2. Ŀ¼������Ŀ¼��������ͻ
     * 3. Ŀ¼������Ŀ¼����������ͻ
     * */
    /*�������ͬ��Ŀ¼*/

    while (h != NULL) {
        if (strcmp(h->name, p->name)==0) {
            cout << "DIR EXISTS           -FALSE" << endl;
            return 0;
        }
        h = h->nextDir;
    }

    /*��������ṹ*/
    p->preDir = currentDir;
    p->nextDir = currentDir->dirChain;
    currentDir->dirChain = p;

    cout << "CREATE                -OK" << endl;
    return 1;
}
int FileSystem::deleteFile(MyFile *f) {
    delete f;
    f = NULL;
    return 1;
}

int FileSystem::deletefileJudge() {
    char temp[MAX_NUM];

    cin >> temp;   //����Ҫɾ�����ļ�������
    MyFile *f;
    MyFile *above = NULL;
    f = currentDir->fileChain;

    /*
     * �жϸ�Ŀ¼��������Ҫɾ�����ļ�
     * */

    while (f != NULL) {
        if (!strcmp(f->name, temp))  
            break;  
        above = f;
        f = f->nextFile;
    }           //��ѯҪɾ�����ļ�
    if (f == NULL) {
        cout << "NO FILE              -FALSE" << endl;
        return 0;
    }
    
    MyDir *d = currentDir;
    
    /*
     * ɾ��ʱ����
     * 1. ��Ҫɾ�����ļ�ǡ����Ŀ¼�ļ������е�ͷ�ڵ�
     * 2. ��Ҫɾ�����ļ��������м�
     * */

    if (f == currentDir->fileChain)//ɾ���ļ����
        currentDir->fileChain = currentDir->fileChain->nextFile;
    else
        above->nextFile = f->nextFile;
    delete f;
    f = NULL;
    cout << "DELETE             -OK" << endl;
    return 1;
}
int FileSystem::deleteDir(MyDir *d) {
    delete d;
    d = NULL;
    return 1;
}

int FileSystem::deletedirJudge() {
    char n[MAX_NUM];

    MyDir *p, *pre = NULL;
    p = root;
    p = currentDir->dirChain;
    cin >> n; //ɾ�����ļ���

    /*��������Ҫɾ����Ŀ¼*/
    while (p != NULL) {
        if (strcmp(p->name, n)==0)
            {pre = p;break;}
        p = p->nextDir;
    }

    if (p == NULL) {
        cout << "DELETE            -FALSE" << endl;
        return 0;
    }

    /*ɾ��Ŀ¼ʱ��Ҫ����
     * 1. ��Ŀ¼���ڸ�Ŀ¼��Ŀ¼�����λ��
     * 2. ��Ŀ¼���Ƿ�����Ŀ¼�������ļ�
     * */
    
    if (p == currentDir->dirChain)
        currentDir->dirChain = currentDir->dirChain->nextDir;
    else
        p->preDir->nextDir = p->nextDir;

    pre = currentDir;
    while (pre != NULL) //�޸�ɾ��Ŀ¼�����Ŀ¼��С
    {
       
        pre = pre->preDir;
    }
    
    MyDir *d = p->dirChain;
    MyFile *f = p->fileChain;
    if (f != 0) {
        while (p->fileChain->nextFile != NULL)//ɾ����Ŀ¼�µ��ļ�
        {
            f = p->fileChain;
            while (f->nextFile->nextFile != NULL)//Ѱ�����һ���ļ����
                f = f->nextFile;
            this->deleteFile(f->nextFile);
            f->nextFile = NULL;
        }
        if (p->fileChain->nextFile == NULL) {
            this->deleteFile(p->fileChain);
            p->fileChain = NULL;
        }
    }
    if (d != NULL) {
        while (p->dirChain->nextDir != NULL)//ɾ����Ŀ¼�µ�Ŀ¼
        {
            d = p->dirChain;
            while (d->nextDir->nextDir != NULL)//Ѱ�����һ���ļ����
                d = d->nextDir;
            this->deleteDir(d->nextDir);//�ݹ���ô˺���
            d->nextDir = NULL;
        }
        if (p->dirChain->nextDir == NULL) {
            this->deleteDir(p->dirChain);
            p->dirChain = NULL;
        }
    }
    delete p,d,f;

    cout << "DELETE           -OK" << endl;
    return 1;

}

int FileSystem::openDir() {
    char name[MAX_NUM];
    MyDir *p;
    p = currentDir->dirChain;

    cin >> name;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {
            currentDir = p;
            return 1;
        }
        p = p->nextDir;
    }
    cout << "NO DIR             -FALSE" << endl;
    return 0;
}


int FileSystem::renameDir() {
    MyDir *h;
    char n1[MAX_NUM], n2[MAX_NUM];
    cin >> n1;
    cin >> n2;
    h = currentDir->dirChain;
    while (h != NULL) {
        if (strcmp(h->name, n2)==0) {
            cout << "DIR EXIST        -FALSE" << endl;
            return 0;
        }
        h = h->nextDir;
    }
    h = currentDir->dirChain;
    while (h != NULL) {
        if (strcmp(h->name, n1)==0)
            break;
        h = h->nextDir;
    }
    if (h == NULL) {
        cout << "NO DIR         -FALSE" << endl;
        return 0;
    }
    strcpy(h->name, n2);
    cout << "RENAME            -OK" << endl;
    return 1;
}

int FileSystem::renameFile() {
    MyFile *h;
    char n1[MAX_NUM], n2[MAX_NUM];
    cin >> n1;
    cin >> n2;
    h = currentDir->fileChain;
    while (h != NULL) {
        if (!strcmp(h->name, n2)) {
            cout << "FILE EXISTS           -FALSE" << endl;
            return 0;
        }
        h = h->nextFile;
    }
    h = currentDir->fileChain;
    while (h != NULL) {
        if (!strcmp(h->name, n1))
            break;
        h = h->nextFile;
    }
    if (h == NULL) {
        cout << "NO FILE            -FALSE" << endl;
        return 0;
    }
    strcpy(h->name, n2);
    cout << "RENAME             -OK" << endl;
    return 1;
}

MyDir *FileSystem::copyDir(MyDir *d) {
    MyFile *fh;
    MyDir *dh, *dir;
    dir = new MyDir;
    dir->dirChain = NULL;
    dir->fileChain = NULL;
    dir->nextDir = NULL;
    dir->preDir = NULL;
    fh = d->fileChain;
    dh = d->dirChain;

    while (fh != NULL) {
        MyFile *f;
        f = copyFile(fh);
        f->nextFile = dir->fileChain;
        dir->fileChain = f;
        fh = fh->nextFile;
    }

    while (dh != NULL) {
        MyDir *d1, *d2;
        d1 = copyDir(dh);
        d1->preDir = dir;
        dir->dirChain = d1;
        d2 = dh->nextDir;
        while (d2 != NULL) {
            d1->nextDir = copyDir(d2);

            d2 = d2->nextDir;
            d1 = d1->nextDir;
            d1->preDir = dir;
        }

        dh = dh->dirChain;
    }

    strcpy(dir->name, d->name);
    return dir;
}

MyDir *FileSystem::copydirJudge() {
    MyDir *h;
    char n[MAX_NUM];
    cin >> n;
    h = currentDir->dirChain;
    while (h != NULL) {
        if (!strcmp(h->name, n))
            break;
        h = h->nextDir;
    }
    if (h == NULL) {
        cout << "NO DIR            -FALSE" << endl;
        return 0;
    }
    tempdir = copyDir(h);
    cout << "COPY           -OK" << endl;
    return tempdir;
}

MyFile *FileSystem::copyFile(MyFile *h) {
    MyFile *f;
    f = new MyFile;
    strcpy(f->name, h->name);
    f->content = h->content;
    return f;
}

MyFile *FileSystem::copyfileJudge() {
    MyFile *h;
    char n[MAX_NUM];
    cin >> n;
    h = currentDir->fileChain;

    while (h != NULL) {
        if (!strcmp(h->name, n))
            break;
        h = h->nextFile;
    }
    if (h == NULL) {
        cout << "NO FILE             -FALSE" << endl;
        return NULL;
    }
    tempfile = copyFile(h);
    cout << "COPY             -OK" << endl;
    return tempfile;
}

int FileSystem::pasteDir() {
    MyDir *h, *d1;
    h = currentDir->dirChain;

    if (tempdir == NULL) 
	{
        cout << "NO SOURCE            -FALSE" << endl;
        return 0;
    }
    else if (h == NULL)
	   {
        cout << "PASTE              -OK" << endl;
        return 1;
        
        d1 = copyDir(tempdir);
        currentDir->dirChain = d1;
        d1->preDir = currentDir;
        }
        else  {
        while (h != NULL) {
            if (!strcmp(h->name, tempdir->name))
                break;
            h = h->nextDir;
                          }
        
            cout << "DIR EXISTS          -FALSE" << endl;
            return 0;
       
            d1 = copyDir(tempdir);
            d1->nextDir = currentDir->dirChain;
            currentDir->dirChain = d1;
            d1->preDir = currentDir;
            
             }
    
    cout << "PASTE              -OK" << endl;
    return 1;
}

int FileSystem::pasteFile() {
    MyFile *h = currentDir->fileChain;
	MyFile *pTemp = h;
    if (tempfile == NULL) {
        cout << "NO SOURCE              -FALSE" << endl;
        return 0;
    }
    /*�����ǰĿ¼û���ļ�*/
    if (h == NULL) {
        currentDir->fileChain = copyFile(tempfile);
		 cout << "PASTE                -OK" << endl;
    }
	else {
        while (h != NULL) {          //����Ƿ���ں͸����ļ�����
            if (!strcmp(h->name, tempfile->name)) {   
                cout << "FILE EXISTS                -FALSE" << endl;
                return 0;
            }
            //break;
            h = h->nextFile;
        }
	      /*��������ճ��*/              
        currentDir->fileChain = copyFile(tempfile);
		currentDir->fileChain->nextFile = pTemp;
        //currentDir->fileChain->nextFile = h;
		 cout << "PASTE                -OK" << endl;
    return 1;
    }
return 0;
   
}



int FileSystem::show_path(MyDir *d)//ʵ����ʾ��ǰ·���ĺ���
{
    if (d->preDir == NULL)
        cout << root->name;
    if (d->preDir != NULL) {
        this->show_path(d->preDir);//�ݹ���ô˺���
        cout << d->name;
    }
    cout << "/";
    return 1;
}

int FileSystem::showCurrentDir() {
    MyDir *d = currentDir->dirChain;
    MyFile *f = currentDir->fileChain;
    if (d == NULL && f == NULL) { 
        cout << "EMPTY" << endl;
        return 0;
    }
    cout << "CONTENT:" << endl;

    if (d != NULL) {       //��ʾ�ļ����б�
        cout << "\t" << "D_NAME" << "\t" << endl;
        while (d != NULL) {                         
            cout << "\t" << d->name << "\t" << endl;
            d = d->nextDir;
        }
        cout << endl;
    }

    if (f != NULL) {                    //��ʾ�ļ��б�
        cout << "\t" << "F_NAME" << "\t" <<  endl;
        while (f != NULL) {
            cout << "\t" << f->name << "\t"  <<  endl;
            f = f->nextFile;
        }
    }
    return 1;
}

int FileSystem::showPath()//��ʾ��ǰ�ļ���·��
{
	 
     show_path(currentDir);
     return 1;
}

int FileSystem::goback() {
    if (currentDir->preDir == NULL) {
        cout << "ROOT DIR          -FALSE" << endl;
        return 0;
    }
    currentDir = currentDir->preDir;
    return 1;
}

int FileSystem::setUser(char *n, char *c) { //�û��趨
    MyDir *root = new MyDir;
    strcpy(root->name, n);
    strcpy(password, c);

    this->root = root;  //�ļ�ϵͳ��ʼ��
    currentDir = root;
    currentDir->preDir = NULL;
    currentDir->dirChain = NULL;
    currentDir->fileChain = NULL;
    currentDir->nextDir = NULL;
    return 1;
}

int FileSystem::changePass() {
	//char newname[30];
	char newpass[30];
	 FILE *passwd;//�ļ�ָ��
    if ((passwd = fopen("user.ini", "w+")) == NULL) {
        printf("File client.txt could not be opened\n");
        fclose(passwd);
        return 0;
    } else {
            
			cout << "�����������룺"<<endl;
			cin>>newpass;
			fprintf(passwd, "%s %s\n",root->name, newpass);
            fclose(passwd);
        return 1;

       }
}


MyDir *FileSystem::getCurrentdir() {  //��ȡ��ǰĿ¼
    return currentDir;
}