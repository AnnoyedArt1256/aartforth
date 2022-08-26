#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <stdio.h> // legacy c lib because me stupid

#define var_mem 24576 // 24k var and array mem
#define word_mem 2048 // word mem 16k

std::string strings[16384];
std::string strings_temp[16384];

std::string remq(std::string a) {
    std::string str;
    for (int o = 0; a[o]!='\"'&&a[o]!='\0'; o++) str = str+a[o];
    return str;
}

int len(std::string str) {  
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++) length++;  
    return length;     
}  

void split(std::string str, char seperator) {
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= len(str))  
    {  
        if (str[i] == seperator || i == len(str))  {  
            endIndex = i;  
            std::string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
    }     
}  

int isNumber(std::string text) {
    if (text=="-") return 0;
    int j;
    j = len(text);
    while(j--) {
        if ((text[j] >= 48 && text[j] <= 48+9) || text[j] == 45) continue;
        return 0;
    }
    return 1;
}


int custom_word = 0;
int word_def_length = 0;

struct word {
    std::string name;
    int pos;
};

std::stack<int> stack;
std::stack<int> word_ret;

std::stack<int> loop_ret;
std::stack<int> loop_index;
std::stack<int> loop_control;
struct word words[word_mem];
struct word words_temp[word_mem];

std::string var_name[var_mem];
int var_content[var_mem];
int is_array[var_mem];
int var_length = 0;

int pc = 0;

int getVarPos(std::string a) {
    for (int i = 0; i < var_mem; i++) if (var_name[i]==a) return i;
    return -1;
}

int op(std::string win) {
    // exit program
    if (win=="bye") {
        return 2;
    }
    
    // custom words
    if (win==":") {
        pc++;
        
        struct word word_on_array;
        word_on_array.name = strings[pc];
        word_on_array.pos = pc;
        words[word_def_length] = word_on_array;
        word_def_length++;  
        
        while (strings[pc]!=";") {
            pc++;
        };
        return 0;
    } 
    std::string temp[word_mem];
    for (int k=0;k<word_mem;k++) {
        temp[k] = words[k].name;
    }
    for (int k=0;k<word_mem;k++) {
        if (temp[k]==win) {
            word_ret.push(pc);
            pc = words[k].pos;
            return 0;
        }
    }
    
    if (win==";") {
        pc = word_ret.top();
        word_ret.pop();
        return 0;
    }
    
    // pushing numbers
    if (isNumber(win)) {
        stack.push(std::stoi(win));
        return 0;
    }    
    
    // basic math
    if (win=="+") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1+op2);
        return 0;
    }   
    if (win=="-") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1-op2);
        return 0;
    }   
    if (win=="*") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1*op2);
        return 0;
    }   
    if (win=="/") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1/op2);
        return 0;
    }   
    if (win=="mod") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1%op2);
        return 0;
    }   

    // output
    if (win==".") {
        int op1 = stack.top();
        stack.pop();
        printf("%d ",op1);
        return 0;
    } 
    if (win=="emit") {
        int op1 = stack.top();
        stack.pop();
        printf("%c",op1);
        return 0;
    }
    if (win=="cr") {
        printf("\n");
        return 0;
    }
    if (win==".\"") {
        std::string print_str;
        pc++;
        while (strings[pc]==remq(strings[pc])) {
            print_str += remq(strings[pc])+" ";
            pc++;
        }
        print_str += remq(strings[pc])+" ";
        std::cout<<print_str;
        return 0;
    }
    
    // stack manipulation
    if (win=="dup") {
        int op1 = stack.top();
        stack.push(op1);
        return 0;
    }
    if (win=="drop") {
        stack.pop();
        return 0;
    }
    if (win=="swap") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op2);
        stack.push(op1);
        return 0;
    }
    if (win=="over") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1);
        stack.push(op2);
        stack.push(op1);
        return 0;
    }
    if (win=="rot") {
        int op3 = stack.top();
        stack.pop();
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op2);
        stack.push(op1);
        stack.push(op3);
        return 0;
    }
    
    // conditionals
    if (win=="=") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1==op2?-1:0);
        return 0;
    }
    if (win==">") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1>op2?-1:0);
        return 0;
    }
    if (win=="<") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1<op2?-1:0);
        return 0;
    }
    
    if (win=="and") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1&op2);
        return 0;
    }
    if (win=="or") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1|op2);
        return 0;
    }    
    if (win=="xor") {
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        stack.push(op1^op2);
        return 0;
    }
    if (win=="invert") {
        int op1 = stack.top();
        stack.pop();
        stack.push(~op1);
        return 0;
    }
    

    // if statements
    if (win=="if") {
        int op1 = stack.top();
        stack.pop();
        int if_true = 0;
        int if_false = 0;
        pc++;
        if_true = pc;
        while (strings[pc]!="else"&&strings[pc]!="then") pc++;
        if (strings[pc]=="else") {
            pc++;
            if_false = pc;
            while (strings[pc]!="then") pc++;
        }
        if (op1==-1) {
            pc = if_true-1;
        } else if (if_false>0) {
            pc = if_false-1;
        }
        return 0;
    }
    if (win=="else") {
        while (strings[pc]!="then") pc++;
        return 0;
    }
    if (win=="then") {
        return 0;
    }
    
    
    // loops
    if (win=="do") {
        loop_ret.push(pc);
        int op2 = stack.top();
        stack.pop();
        int op1 = stack.top();
        stack.pop();
        loop_index.push(op2);
        loop_control.push(op1);
        return 0;
    }
    if (win=="loop") {
        int op1 = loop_index.top();
        loop_index.pop();
        loop_index.push(op1+1);
        if (loop_index.top()<loop_control.top()) {
            pc = loop_ret.top();
        } else {
            loop_control.pop();
            loop_index.pop();
            loop_ret.pop();
        }
        return 0;
    }
    if (win=="i") {
        stack.push(loop_index.top());
        return 0;
    }
    if (win=="leave") {
        loop_control.pop();
        loop_index.pop();
        loop_ret.pop();     
        while (strings[pc]!="loop") pc++;
        return 0;
    }
    
    // variables
    if (win=="variable") {
        pc++;
        var_name[var_length] = strings[pc];
        var_content[var_length] = 0;
        is_array[var_length] = 0;
        var_length++;
        return 0;
    }
    if (win=="!") {
        int address = stack.top();
        stack.pop();
        int value = stack.top();
        stack.pop();
        var_content[address] = value;
        return 0;
    }
    if (win=="+!") {
        int address = stack.top();
        stack.pop();
        int value = stack.top();
        stack.pop();
        var_content[address] += value;
        return 0;
    }
    if (getVarPos(strings[pc])>=0) {
        stack.push(getVarPos(strings[pc]));
        return 0;
    }
    if (win=="@") {
        int op1 = stack.top();
        stack.pop();
        stack.push(var_content[op1]);
        return 0;
    }
    if (win=="?") {
        int op1 = stack.top();
        stack.pop();
        printf("%d ",var_content[op1]);
        return 0;
    }
    
    // arrays
    if (win=="cells"&&strings[pc+1]=="allot") {
        int op1 = stack.top();
        stack.pop();
        is_array[var_length-1] = 1;
        var_length += op1+1;
        pc++;
        return 0;
    }
    if (win=="cells") { // it does nothing because me stupid
        return 0;
    }
    if (win=="rand") {
        int op1 = stack.top();
        stack.pop();
	stack.push(rand()%(op1+1));	
	return 0;
    }
    return 1;
}

int run_forth(std::string input) {
    custom_word = 0;
    word_def_length = 0;
    memcpy(words_temp,words,sizeof(struct word)*word_mem);
    for (int i=0;i<16384;i++) {
        strings[i] = strings_temp[i];
    }
    split(input,' ');
    for (pc=0;len(strings[pc])>0;pc++) {
        int ret_code = op(strings[pc]);
        if (ret_code==2) {
            return 2;
        };
        if (ret_code==1) {
            std::cout<<"\nERROR: "<<strings[pc]<<"?";
            break;  
        };
    }
    return 0;
}

int main() {
    std::string prog;
    std::cout<<"AArtForth C version by AArt1256 made in 2022!";
    while (1) {
 	std::cout<<"\n> ";
        getline(std::cin, prog, '\n');
        if (run_forth(prog)==2) return 0;
        std::cout<<"\nok";
   }
    return 0;
}