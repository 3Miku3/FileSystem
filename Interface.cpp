#include"Interface.h"
#include<iostream>
#include<string>
#include"FileSystem.h"
#include<Windows.h>
using namespace std;
void help() {
    cout << "***************************************************************************" << endl;
    cout << "* 1.mk + <string>                         �½�һ���ļ�,�ļ���Ϊ<string>   *" << endl;
    cout << "* 2.rm + <string>                         ɾ���ļ���Ϊ<string>���ļ�      *" << endl;
    cout << "* 3.rename + <string> + <string>          �������ļ�,�ڶ���string�������� *" << endl;
    cout << "* 4.cp + <string>                         �����ļ�,�ļ���Ϊ<string>       *" << endl;
    cout << "* 5.paste                                 ճ���ļ�                        *" << endl;
    cout << "* 6.mkdir + <string>                      �½�Ŀ¼,Ŀ¼��Ϊ<string>       *" << endl;
    cout << "* 7.rmdir + <string>                      ɾ��Ŀ¼,Ŀ¼��Ϊ<string>       *" << endl;
    cout << "* 8.renamedir + <string> + <string>       ������Ŀ¼,�ڶ���string�������� *" << endl;
    cout << "* 9.cpdir + <string>                      ����Ŀ¼,Ŀ¼��Ϊ<string>       *" << endl;
    cout << "* 10.pastedir                             ճ��Ŀ¼                        *" << endl;
    cout << "* 11.ls                                   ��ʾĿ¼����������              *" << endl;
    cout << "* 12.cd +<string>                         ��Ŀ¼��һ��Ŀ¼����һ��Ŀ¼  *" << endl;
    cout << "* 13.cd..                                 ������һ��Ŀ¼                  *" << endl;
	cout << "* 14.pwd                                  ��ʾ��ǰĿ¼                    *" << endl;
	cout << "* 15.passwd                               �޸��û�����                    *" << endl;
    cout << "* 16.clear                                ����                            *" << endl;
    cout << "* 17.exit                                 ע��                            *" << endl;
    cout << "***************************************************************************" << endl
        << endl;

}


/*�û�����������飨���ļ������ݱȽϣ�*/
int login(char username[30], char password[30]) {
    char name[30];
    char pass[30];
    FILE *Verify;//�ļ�ָ��
    if ((Verify = fopen("user.ini", "r")) == NULL) {
        printf("File client.txt could not be opened\n");
        fclose(Verify);
        return 0;
    } else {
        while (!feof(Verify)) {
            fscanf(Verify, "%s%s", name, pass);
            if ((strcmp(username, name) == 0) && (strcmp(password, pass) == 0)) {
                fclose(Verify);
                return 1;
            }
        }
    }
    fclose(Verify);
    return 0;
}

int fsOperate(char name[30], char pass[30]) {
    FileSystem fs;
    fs.setUser(name, pass);
    while (1) {
        system("CLS");
        help();
        while (1) {
            cout << endl;
            string choice;

            fs.showPath();
            cin >> choice;
            if (choice == "mkdir")
                fs.newDir();
            else if (choice == "mk")
                fs.newFile();
            else if (choice == "rmdir")
                fs.deletedirJudge();
            else if (choice == "rm")
                fs.deletefileJudge();
            else if (choice == "renamedir")
                fs.renameDir();
            else if (choice == "rename")
                fs.renameFile();
            else if (choice == "cd")
                fs.openDir();
            else if (choice == "ls")
                fs.showCurrentDir();
            else if (choice == "cpdir")
                fs.copydirJudge();
            else if (choice == "cp")
                fs.copyfileJudge();
            else if (choice == "pastedir")
                fs.pasteDir();
            else if (choice == "paste") 
                fs.pasteFile();
			else if (choice=="pwd")
				fs.getCurrentdir();
			else if (choice=="passwd")
				fs.changePass();
            else if (choice == "cd..")
                fs.goback();
            else if (choice == "clear") {
                system("CLS");
                help();
            } else if (choice == "exit") {
                system("CLS");
                cout << "�û�: " << name << "����ע��...."
                    << endl;
                 Sleep(3);
                return 0;
            } else if (choice == "help") {
                help();
            } else if (choice == "mkdir?")
                cout << "������Ŀ¼ ����ʽΪ mkdir [dirname]" << endl;
            else if (choice == "mk?")
                cout << "�������ļ�����ʽΪ mk[filename]" << endl;
            else if (choice == "rmdir?")
                cout << "ɾ����Ŀ¼����ʽΪ rmdir [dirname]" << endl;
            else if (choice == "rm?")
                cout << "ɾ���ļ��������ʽΪ rm [filename]" << endl;
            else if (choice == "renamedir?")
                cout << "Ŀ¼������ " << endl;
            else if (choice == "rename?")
                cout << "�ļ������� " << endl;
            else if (choice == "cd?")
                cout << "����Ŀ¼����ʽΪ cd [dirname]" << endl;
            else if (choice == "ls?")
                cout << "��ʾĿ¼�����б�" << endl;
            else if (choice == "cpdir?")
                cout << "������Ŀ¼, ��ʽΪ cpDir [dirname]" << endl;
            else if (choice == "cy?")
                cout << "�����ļ�,��ʽΪ cp [filename]" << endl;
            else if (choice == "pastedir?")
                cout << "ճ���Ѹ��Ƶ�Ŀ¼" << endl;
            else if (choice == "paste?")
                cout << "ճ���Ѹ��Ƶ��ļ�" << endl;
            else if (choice == "clear?")
                cout << "����" << endl;
            else if (choice == "cd..?")
                cout << "���ص�ǰĿ¼����һ��Ŀ¼" << endl;
			else if (choice == "pwd?")
				cout << "��ʾ��ǰĿ¼"<<endl;
			else if (choice == "passwd?")
				cout << "�޸��û�����"<<endl;
            else if (choice == "exit?")
                cout << "ע���ļ�ϵͳ" << endl;
            else
                cout << "������Ч��" << endl;
        }
    }

}
void run(){
    int choice = 0;
    char name[30], pass[30];
    system("CLS");
    Sleep(2);
    while (true) {
        system("CLS");
        cout << "\t\t*****************************************\t" << endl;
        cout << "\t\t*             ��  ��  ϵ  ͳ          \t*" << endl;
        cout << "\t\t*               1. ��¼               \t*" << endl;
        cout << "\t\t*               2. ����              \t*" << endl;
        cout << "\t\t*               3. �˳�               \t*" << endl;
        cout << "\t\t*****************************************\t" << endl;
        cout << "\t\t��ѡ��: " ;
        cin >> choice;
        switch (choice) {

                    /*ѡ���¼*/
            case 1: {
                        cout << "�������û���:";
                        cin >> name;
                        cout << "����������:";
                        cin >> pass;
                        if (login(name, pass) == 1) {
                            cout << "       --��¼�ɹ�.." << endl;
                            fsOperate(name, pass);

                        } else{
                            cout << "           --��¼ʧ�ܣ����򿪷�����Ҫ�˺�����..." << endl;
                             Sleep(2000);

                        }}
                        break;
						/*ѡ�����*/
            case 2:{
            	      system("CLS");
                        cout << "\t\t*********************************************************" << endl;
                        cout << "\t\t*                        �����ĵ�                     \t*" << endl;
                        cout << "\t\t*   ���ʹ�ø�ϵͳ������helpʱ��ʾ��������İ����ĵ���\t*" << endl;
                        cout << "\t\t*        ����ĳ������+��ʱ��ʾ���������ʹ��˵��      \t*" << endl;
                        cout << "\t\t*********************************************************" << endl;
                        system("Pause");
            	     }break;
                      /*ѡ���˳�*/
            case 3: {
                        system("CLS");
                        cout << "        --�˳��ļ�ϵͳ.." << endl;
                         Sleep(3);
                        exit(0);
                    }
                    break;
                    /*����ѡ��*/
            default:
                    
                    break;
        }
    }

}