#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <stack>
#include <iostream>
#include <string.h>
 #include <stdio.h>

using namespace std ;

class DSA{
	public:
		DSA();
		~DSA();
		bool isNumber(char);
		bool isOperator(char);		
		int Rank(char);
		bool precedence(char, char);
		void convertToPostfix(string&);
		void Trans();
	private:
		vector<char> postfix;			
		vector<string> trans;
};
DSA::DSA(){
};
DSA::~DSA(){
};

bool DSA::isNumber(char cur)
{
    switch (cur) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
	case '7':
	case '8':
	case '9':
	case '0':	
        return true;
    default:
        return false;
    }
}

bool DSA::isOperator(char cur)
{
    switch (cur) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '!':
	case '~':
	case '<<':
	case '>>':
	case '&':
	case '|':
	case '^':
	case '&&':
	case '||':
	case 'p':
	case 'm':	
        return true;
    default:
        return false;
    }
}

int DSA::Rank(char op)
{
	int rank = -1; 
	
	if(op=='!' || op == '~' || op == 'p' || op == 'm')
		rank = 1;
	if(op == '+' || op == '-') 
		rank = 3;
	if(op == '*' || op == '/' || op == '%')
		rank = 2;	
	if(op == '<<' || op == '>>') 
		rank = 4;	
	if(op == '&') 
		rank = 5;	
	if(op == '^') 
		rank = 6;
	if(op == '|') 
		rank = 7;
	if(op == '&&') 
		rank = 8;
	if(op == '||') 
		rank = 9;
	return rank;
}

bool DSA::precedence(char leftOperator, char rightOperator)
{
	int L = Rank(leftOperator);
	int R = Rank(rightOperator);
	if (L <= R)
		return true;
	else
		return false;	
    return true;
}
void DSA::convertToPostfix(string& infix)
{
//	vector<char> postfix;
    //stringstream postfix; 
    stack<char> stack;
    stack.push('('); 
	for(size_t i = 0, L = infix.size(); i < L; ++i) {
        char cur = infix[i];
        char text = cur;
        if (isspace(cur)) {
        }
        int k = i; int s = i;
        	
        if(i==0){
        	if (text == '+'){
					infix[i] = 'p';	}
			else if (text == '-'){
					infix[i] = 'm';	
					}	
		}	
        if(i>0){
        	
			if(isOperator(infix[i-1])){
					if (text == '+'){
					infix[i] = 'p';	}
					else if (text == '-'){
					infix[i] = 'm';	
					}
			}
			else if (infix[i-1] == '('){
				do{
					char pre = infix[k-1];
					if ( isOperator(pre) ) {
						if (text == '+'){
						infix[i] = 'p';	}
						else if (text == '-'){
						infix[i] = 'm';}
						break;	
					}
					else if (isNumber(pre)){
						break;
					}
					else if(k=1&&pre=='(') {
						if (text == '+'){
						infix[i] = 'p';	}
						else if (text == '-'){
						infix[i] = 'm';}
						break;
					}
					k--;
				}while(k>=0);
			}
		else if (infix[i-1] == ')'){	
			do{
					char pre = infix[s-1];
					if ( isOperator(pre) ) {
						if (text == '+'){
						infix[i] = 'p';	}
						else if (text == '-'){
						infix[i] = 'm';}
						break;	
					}
					else if (isNumber(pre)){
						break;
					}
					s--;
				}while(s>=1);
			}
		}	
	}	
	
   for(size_t i = 0, M = infix.size(); i < M; ++i) { 
  int check = 0;
   char now = infix[i];
    	if (isspace(now)) {
        } 	   
    if(i>0){
    	if(infix[i] == '!'|| infix[i] =='~'||infix[i]=='p'||infix[i]=='m'){
			if(infix[i-1] == '!'|| infix[i-1] =='~'||infix[i-1]=='p'||infix[i-1]=='m'){
			infix.insert(i,"(");	 
			for(size_t j = 0, M = infix.size(); j < M; ++j) { 
			if(infix[j] == '(')
				check ++;
			if(infix[j] == ')')
				check --;		
			if(check == 1){
				if(infix[j] == '+'||infix[j] == '-'||infix[j] == '*'||infix[j] == '/'||infix[j] == '%'||infix[j] == '&&'||infix[j] == '||'||infix[j] == '^'||infix[j] == '&'||infix[j] == '<<'||infix[j] == '>>'){
					infix.insert(j,")");
					j++;		
									}
				else if(j == infix.size()-1){
					infix.push_back(')');
				} 					
			}
			}
			i++;
			}
		}        	
	}
	/*for(vector<string>::iterator it = infix.begin();it != infix.end();it++){
		cout<<*it;
	}*/
}
	
    for(size_t i = 0, S = infix.size(); i < S; ++i) {
        const char current = infix[i];

        if (isspace(current)) {
        }
        else if(isNumber(current) || '.' == current) {
            //postfix << current;
            postfix.push_back(current);
            cout<<endl<<"Current : ";
        for(vector<char>::iterator it = postfix.begin(); it != postfix.end();it++){
        	if(*it == 'p'){
			cout <<'+'; 
			}
			else if(*it == 'm'){
			cout <<'-'; 
			}
			else if(*it != 'p'&& *it != 'm'){
			cout <<*it; 
			}
			}   
        }
        else if('(' == current) {
            stack.push(current);
            if (current == 'p'){
            	cout<<endl<<"Push : "<<'+'<<endl;
			} 
			else if (current == 'm'){
				cout<<endl<<"Push : "<<'-'<<endl;
			}
			else if (current != 'p' && current != 'm'){
            cout<<endl<<"Push : "<<current<<endl;
			}
        }

        else if(isOperator(current)) {
            char rightOperator = current;      
           while(!stack.empty() && isOperator(stack.top())&&precedence(stack.top(), rightOperator)) {
           		if(stack.top() == 'p'){
           		postfix.push_back('p');
           	
		//	   	if (stack.top() == 'p'){
            	cout<<endl<<"Pop : "<<'+'<<endl;
		//	} 
		/*	else if (stack.top() == 'm'){
				cout<<endl<<"Pop : "<<'-'<<endl;
			}*/
		/*	else if (stack.top() != 'p' && stack.top() != 'm'){
            cout<<endl<<"Pop : "<<stack.top()<<endl;
			}*/           			
           			cout<<endl<<"Current : ";
        			for(vector<char>::iterator it = postfix.begin(); it != postfix.end();it++){
        			if(*it == 'p'){
						cout <<'+'; 
						}
					else if(*it == 'm'){
						cout <<'-'; 
						}
					else if(*it != 'p'&& *it != 'm'){
						cout <<*it; 
						}
					}		 
           		//postfix << ' ' << '+';	
           		stack.pop();
				   }
				else if(stack.top() == 'm'){
				postfix.push_back('m');
           		//postfix << ' ' << '-';
        /*   		if (stack.top() == 'p'){
            	cout<<endl<<"Pop : "<<'+'<<endl;
			} */
		//	else if (stack.top() == 'm'){
				cout<<endl<<"Pop : "<<'-'<<endl;
		//	}
		/*	else if (stack.top() != 'p' && stack.top() != 'm'){
            cout<<endl<<"Pop : "<<stack.top()<<endl;
			} */          		
           		cout<<endl<<"Current : ";
        		for(vector<char>::iterator it = postfix.begin(); it != postfix.end();it++){
        			if(*it == 'p'){
					cout <<'+'; 
					}
				else if(*it == 'm'){
					cout <<'-'; 
					}
				else if(*it != 'p'&& *it != 'm'){
					cout <<*it; 
					}
				}	    	
           		stack.pop();
				   }
				else if(stack.top() != 'm'&&stack.top() != 'p'){  
				 	postfix.push_back(' ');
					postfix.push_back(stack.top());
				/*	if (stack.top() == 'p'){
            	cout<<endl<<"Pop : "<<'+'<<endl;
			} */
		/*	else if (stack.top() == 'm'){
				cout<<endl<<"Pop : "<<'-'<<endl;
			}*/
		//	else if (stack.top() != 'p' && stack.top() != 'm'){
            cout<<endl<<"Pop : "<<stack.top()<<endl;
		//	}           		
           	
					cout<<endl<<"Current : ";
	        	for(vector<char>::iterator it = postfix.begin(); it != postfix.end();it++){
        			if(*it == 'p'){
					cout <<'+'; 
					}
					else if(*it == 'm'){
					cout <<'-'; 
					}
					else if(*it != 'p'&& *it != 'm'){
					cout <<*it; 
					}
					} 
                	//postfix << ' ' << stack.top();
                	stack.pop();}
            }
            postfix.push_back(' ');
            //postfix << ' ';
            if (rightOperator == 'p'){
            	cout<<endl<<"Push : "<<'+'<<endl;
			} 
			else if (rightOperator == 'm'){
				cout<<endl<<"Push : "<<'-'<<endl;
			}
			else if (rightOperator != 'p' && rightOperator != 'm'){
            cout<<endl<<"Push : "<<rightOperator<<endl;
			}
            stack.push(rightOperator);
        }
        // We've hit a right parens
        else if(')' == current) {
        	cout <<endl<<"Encounter ')' "<<endl;
            // While top of stack is not a left parens
            while(!stack.empty() && '(' != stack.top()) {
            	postfix.push_back(' ');
            	postfix.push_back(stack.top());
            	if (stack.top() == 'p'){
            	cout<<endl<<"Pop : "<<'+'<<endl;
			} 
			else if (stack.top() == 'm'){
				cout<<endl<<"Pop : "<<'-'<<endl;
			}
			else if (stack.top() != 'p' && stack.top() != 'm'){
            cout<<endl<<"Pop : "<<stack.top()<<endl;
			}           		
           	
            	cout<<endl<<"Current : ";
            for(vector<char>::iterator it = postfix.begin(); it != postfix.end();it++){
        		if(*it == 'p'){
				cout <<'+'; 
				}
				else if(*it == 'm'){
				cout <<'-'; 
				}
				else if(*it != 'p'&& *it != 'm'){
				cout <<*it; 
				}
			} 
                //postfix << ' ' << stack.top();
                stack.pop();
            }
            if (stack.empty()) {
                throw std::runtime_error("missing left paren");
            }
            // Discard the left paren
            stack.pop();
            postfix.push_back(' ');
            //postfix << ' ';
        } else {
            throw std::runtime_error("invalid input character");
        }
    }
    while(!stack.empty() && '(' != stack.top()) {
    	postfix.push_back(' ');
        postfix.push_back(stack.top());
        if (stack.top() == 'p'){
            	cout<<endl<<"Pop : "<<'+'<<endl;
			} 
			else if (stack.top() == 'm'){
				cout<<endl<<"Pop : "<<'-'<<endl;
			}
			else if (stack.top() != 'p' && stack.top() != 'm'){
            cout<<endl<<"Pop : "<<stack.top()<<endl;
			}           		
           	
        cout<<endl<<"Current : ";
        for(vector<char>::iterator it = postfix.begin(); it != postfix.end();it++){
        	if(*it == 'p'){
			cout <<'+'; 
			}
			else if(*it == 'm'){
			cout <<'-'; 
			}
			else if(*it != 'p'&& *it != 'm'){
			cout <<*it; 
			}
			}  
        //postfix << ' ' << stack.top();
        stack.pop();
    }
    if (stack.empty()) {
        throw std::runtime_error("missing left paren");
    }
    stack.pop();

    if (!stack.empty()) {
        throw std::runtime_error("missing right paren");
    }
    cout <<endl<<"Postfix Exp: ";
        for(vector<char>::iterator it = postfix.begin(); it != postfix.end();it++){
        	if(*it == 'p'){
			cout <<'+'; 
			}
			else if(*it == 'm'){
			cout <<'-'; 
			}
			else if(*it != 'p'&& *it != 'm'){
			cout <<*it; 
			}
			} 		
}
void DSA::Trans(){
	string num = "1234567890";
	string space = " ";
	std::string s = std::string(postfix.begin(), postfix.end());
	s = s+ " ";
	do{
	int end = s.find_first_of(space);	
	string find = s.substr(0,end-1);	
	trans.push_back(find);
	s.erase(s.begin(),s.begin()+end);
	}while( s.size()!=0);
	cout<<"Trans : ";
	for(vector<string>::iterator it = trans.begin();it!=trans.end();it++){
		cout <<*it;
	}
}

int main()
{
	DSA A;
    for (;;) {
        if (!cout.good()) break;
        cout << "Enter Infix Expression: ";
        string infix;
        //infix = "3*5-2/6";//"(21*(21&&81)))";
        getline(std::cin, infix);
        if (infix.empty()) break;
        A.convertToPostfix(infix);
        A.Trans();
		cout << "'\n";	
    }
    return 0;
}
