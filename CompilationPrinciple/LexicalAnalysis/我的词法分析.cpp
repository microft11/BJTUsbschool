#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#define LENGTH 32
using namespace std;

//判断当前字符串是否为关键字
bool isKey(string s){
    //关键字数组
    string keyArray[] = {"int","char","string","void","bool","float","double","float","true","false","return",
                        "if","else","while","for","default","do","public","static","switch","case","include"};
    //与当前字符串一一对比
    for(int i=0;i<sizeof(keyArray);i++){
        if(s==keyArray[i]){
            return true;
        }
        // 在C++中，#include 是用于包含头文件的预处理指令，它在编译之前由预处理器处理，而不是由编译器处理
        if("include"==keyArray[i]){
        	break;
		}
    }
    return false;
}

//判断当前字符是否是运算符
bool isOperator(char ch){
    if('+'==ch || '-'==ch || '*'==ch || '/'==ch || '='==ch || '<'==ch || '>'==ch || '!'==ch|| '&'==ch|| '|'==ch)
        return true;
    else
        return false;
}

//判断当前字符是否是分隔符
bool isSeparator(char ch){
    if(','==ch || ';'==ch || '{'==ch || '}'==ch || '('==ch || ')'==ch|| ':'==ch)
        return true;
    else
        return false;
}


int main( )
{
    //定义字符变量，保存从源程序中读取的单个字符
    char ch;
    //定义字符串，保存从源程序中连续读取的字符串
    string result;
    //存放每个获取的单词的值
    string resultArray[999];
    //记录获取单词的个数
    int resultNum=0;

    //代码存放的文件名
    string file = "input1.txt";

    ifstream infile;
    //将文件流对象与文件连接起来
    infile.open(file.data());
    //若失败,则输出错误消息,并终止程序运行
    assert(infile.is_open());

    //txt文本中读取空格符与换行符
    //infile >> noskipws;
    //读取文本中的一个字符
    infile>>ch;

    while (!infile.eof())
    {
        //ch是英文字母
        if(isalpha(ch)){
            result.append(1,ch);
            infile>>ch;
            //判断是否为关键字
            if(isKey(result)){
                resultArray[resultNum++]="(关键字,\""+result+"\")";
                result="";
            }
            //读入首字符为字母，继续读入字母、数字，组成标识符或者关键字
            while(isalpha(ch) || isdigit(ch)){
                result.append(1,ch);
                infile>>ch;
                if(isKey(result)){
	                resultArray[resultNum++]="(关键字,\""+result+"\")";
	                result="";						
                }
                if(result.length()==LENGTH){
                	break;
				}
            }
            //读入操作符或者分割符，正确保存标识符或者关键字
            if(isSeparator(ch) || isOperator(ch)){
                if(isKey(result)){
                    resultArray[resultNum++]="(关键字,\""+result+"\")";
                    result="";
                    continue;
                }
                else{
                    resultArray[resultNum++]="(1,\""+result+"\")";
                    result="";
                    continue;
                }

            }
            //读入不是字母、数字、运算符、标识符，继续读入直到遇到运算符或者分隔符
            else{
                result.append(1,ch);
                infile>>ch;
                while(!isSeparator(ch) && !isOperator(ch)){
                    result.append(1,ch);
                    infile>>ch;
                }
                resultArray[resultNum++]="(Error，标识符中有违规符号,\""+result+"\")";
                result="";
                continue;
            }
        }
        //读入数字
        else if(isdigit(ch)){
            result.append(1,ch);
            infile>>ch;
            //继续读入数字，组成常数
            while(isdigit(ch)){
                result.append(1,ch);
                infile>>ch;
            }
            //遇到操作符或者运算符，正常终止
            if(isOperator(ch) || isSeparator(ch)){
                resultArray[resultNum++]="(无符号整数,\""+result+"\")";
                result="";
                continue;
            }
            //也可以读小数
			else if('.'==ch){
            	result.append(1,ch);
            	infile>>ch;	
            	int num=0;
				while(isdigit(ch)){
					num++;
					result.append(1,ch);
            		infile>>ch;
				}
				if(num==0){
					resultArray[resultNum++]="(Error，小数点后没有数字,\""+result+"\")";
	                result="";
	                continue;
				}
	            if(isOperator(ch) || isSeparator(ch)){
	                resultArray[resultNum++]="(浮点数,\""+result+"\")";
	                result="";
	                continue;
	            }
				else{
	                result.append(1,ch);
	                infile>>ch;
	                while(!isSeparator(ch) && !isOperator(ch)&& !infile.eof()) {
	                    result.append(1,ch);
	                    infile>>ch;
	                }
	                resultArray[resultNum++]="(Error，浮点数后有未知符号,\""+result+"\")";
	                result="";
	                continue;
	            }			
			} 
            //读入其他错误字符
            else{
                result.append(1,ch);
                infile>>ch;
                while(!isSeparator(ch) && !isOperator(ch)&& !infile.eof()) {
                    result.append(1,ch);
                    infile>>ch;
                }
                resultArray[resultNum++]="(Error，整数后有错误符号,\""+result+"\")";
                result="";
                continue;
            }
        }
        //遇到运算符
        else if(isOperator(ch))
        {
            result.append(1,ch);
            infile>>ch;
            //判断是否存在<=、>=、!=、==、+=、-=、*=
            if("<"==result || ">"==result || "!"==result|| "="==result ||"+"==result ||"-"==result ||"*"==result){
                if('='==ch){
                    result.append(1,ch);
                    infile>>ch;
                }
            }
            if("+"==result){
            	if('+'==ch){
            		result.append(1,ch);
                    infile>>ch;
				}
			}
            if("-"==result){
            	if('-'==ch){
            		result.append(1,ch);
                    infile>>ch;
				}
			}
			if(">"==result){
            	if('>'==ch){
            		result.append(1,ch);
                    infile>>ch;
				}
			}
			if("<"==result){
            	if('<'==ch||'>'==ch){
            		result.append(1,ch);
                    infile>>ch;
				}
			}
			if("&"==result){
            	if('&'==ch){
            		result.append(1,ch);
                    infile>>ch;
				}
				else{
					resultArray[resultNum++]="(Error：逻辑与运算符号错误：\""+result+"\")";
                	result="";
				}
			}
			if("|"==result){
            	if('|'==ch){
            		result.append(1,ch);
                    infile>>ch;
				}
				else{
					resultArray[resultNum++]="(Error：逻辑或运算符号错误：\""+result+"\")";
                	result="";
				}
			}
            if("/"==result){
            	if('*'==ch){
            		result.append(1,ch);
                    infile>>ch;
            		while(1){
            			//这里一定要把文件指针往后移动两位，不然的话/*/形式的也会被无认为是注释（虽然应该不会有人这么写） 
            			result.append(1,ch);
                    	infile>>ch;
                    	char ch2 = result.at(result.length()-1);
                    	if('*'==ch2 && '/'==ch){
                    		result.append(1,ch);
                    		infile>>ch;
                    		resultArray[resultNum++]="(可以跨行的注释内容：\""+result+"\")";
                			result="";
                    		break;
						}
					}
					continue;
				}
				else if('='==ch){
					result.append(1,ch);
                    infile>>ch;
				}
			}
            //下一个读入符为字母、数字、分隔符，即正确
            if(isalpha(ch) || isdigit(ch) || isSeparator(ch)){
                resultArray[resultNum++]="(运算符,\""+result+"\")";
                result="";
                continue;
            }
            else{
                //将错误输入符一起读入，直到正确
                while(!isSeparator(ch) && !isalpha(ch) && !isdigit(ch) && !infile.eof()){
                    result.append(1,ch);
                    infile>>ch;
                }
                resultArray[resultNum++]="(Error,\""+result+"\")";
                result="";
                continue;
            }
        }
        //读取到分隔符
        else if(isSeparator(ch)){
            result.append(1,ch);
            resultArray[resultNum++]="(分隔符,\""+result+"\")";
            result="";
            infile>>ch;
        }
        //读取到未定义输入
        else{
            //出错处理
            result.append(1,ch);
            resultArray[resultNum++]="(Error，遇到了未定义输入（非字母数字，运算符，分隔符），且不在注释中,\""+result+"\")";
            result="";
            infile>>ch;

        }
    }
    //关闭文件输入流
    infile.close();

    //以 （单词类编码，值） 输出结果
    for(int i=0;i<resultNum;i++){
        cout<<resultArray[i]<<endl;
    }

    ofstream ofs;						//定义流对象
    ofs.open("text.txt",ios::out);		//以写的方式打开文件
    for(int i=0;i<resultNum;i++){
        ofs<<resultArray[i]<<endl;
    }
    ofs.close();

	
   	return 0;
}


