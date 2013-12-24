#include<iostream>
#include<string.h>
#include<string>
#include<iomanip>
#include <stdlib.h>
#include<stdio.h>
using namespace std;
#define MAX_NUM  20    //�ļ�������Ŀ¼��������ֽ���



typedef struct MyFile         //�ļ��ṹ��
{
    char name[MAX_NUM];      //�ļ��� 
    struct MyFile *nextFile;  //ָ���ļ��б�����һ���ļ�
    string content;           //�ļ�����
} MyFile;

typedef struct MyDir          //Ŀ¼�ṹ��
{
    char name[MAX_NUM];      //Ŀ¼����
    MyDir *nextDir;           //���Ŀ¼
    MyDir *preDir;            //ǰ��Ŀ¼
    MyFile *fileChain;          //��Ŀ¼�µ��ļ�����ָ��
    MyDir *dirChain;            //��Ŀ¼�µ�Ŀ¼����ָ��
} MyDir;


class FileSystem //�ļ�ϵͳ��
{
	private:
    MyDir *currentDir; //��ǰĿ¼
    MyFile *tempfile; //���ڿ����ļ�ʱ����ʱ�ļ�
    MyDir *tempdir; //���ڿ���Ŀ¼ʱ����ʱĿ¼
    MyDir *root; //��Ŀ¼
    char password[MAX_NUM];   //�û�����
    char name[MAX_NUM];   //�û�����
    

 public:
     FileSystem();
    ~FileSystem();

    int newFile(); //�����ļ�
    int newDir(); //����Ŀ¼

    int deleteFile(MyFile *file);//ɾ���ļ�
    int deletefileJudge(); //ɾ���ļ�ǰ���߼��ж�
    int deleteDir(MyDir *d); //ɾ��Ŀ¼
    int deletedirJudge(); //ɾ��Ŀ¼ǰ���߼��ж�

    int openDir(); //��Ŀ¼
    int renameDir(); //������Ŀ¼
    int renameFile(); //�������ļ�

    MyDir *copyDir(MyDir *dir);//����Ŀ¼
    MyDir *copydirJudge(); //����Ŀ¼ǰ���߼��ж�
    MyFile *copyFile(MyFile *h); //�����ļ�
    MyFile *copyfileJudge(); //�����ļ�ǰ���߼��ж�

    int pasteDir(); //ճ��Ŀ¼
    int pasteFile(); //ճ���ļ�
    int showCurrentDir(); //��ʾ��ǰĿ¼����

    int show_path(MyDir *dir); //��ʾ·���Ĳ���ʵ��
    int showPath(); //��ʾ·��

    int goback(); //������һ��Ŀ¼
    int changePass();//�޸��û�����
    int setUser(char *, char *);//�����û���������

    MyDir *getCurrentdir(); //��õ�ǰĿ¼
};