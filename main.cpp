#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// You will need tthese forward references.
class Expr;
class Stmt;

// Runtime Global Variables
int pc;              // program counter
vector<string> lexemes;
vector<string> tokens;
vector<string>::iterator lexitr;
vector<string>::iterator tokitr;
map<string, string> symbolvalues;   // map of variables and their values
map<string, string> symboltable; // map of variables to datatype (i.e. sum t_integer)
vector<Stmt *> insttable;      // table of instructions
map<string,int> precMap;


// Runtime Global Methods
void dump(); 				// prints vartable, instable, symboltable


// Classes Stmt and Expr
// You are allowed to add methods if needed. You should NOT need to add member variables.

class Expr{ // expressions are evaluated!
public:
	virtual string toString() = 0;
	virtual ~Expr(){}
};

class StringExpr : public Expr{
public:
    virtual string eval() = 0;
};

class IntExpr : public Expr{
public:
    virtual int eval() = 0;
};

class StringConstExpr : public StringExpr{
private:
    string value;
public:
    StringConstExpr(string val){}
    ~StringConstExpr(){}
    string eval(){}
    string toString(){}
};

class StringIDExpr : public StringExpr{
private:
    string id;
public:
    StringIDExpr(string val){}
    ~StringIDExpr(){}
    string eval(){}
    string toString(){}
};

class StringPostFixExpr : public Expr{
private:
    vector<string> expr;
    vector<string> exprtoks;
public:
    StringPostFixExpr(){}
    StringPostFixExpr(string x, string t){}
    ~StringPostFixExpr(){}
    string eval(){}
    string toString(){}
};

class IntConstExpr : public IntExpr{
private:
    int value;
public:
    IntConstExpr(int val){}
    ~IntConstExpr(){}
    int eval(){}
    string toString(){}
};

class IntIDExpr : public IntExpr{
private:
    string id;
public:
    IntIDExpr(string val){}
    ~IntIDExpr(){}
    int eval(){}
    string toString(){}
};

class IntPostFixExpr : public IntExpr{
private:
    vector<string> expr;
public:
    IntPostFixExpr(){}
    IntPostFixExpr(string x){expr.push_back(x);}
    ~IntPostFixExpr(){}
    int eval(){}
    string toString(){}
};

class Stmt{ // statements are executed!
private:
	string name;
public:
	Stmt(){}
	virtual ~Stmt(){};
	virtual string toString() = 0;
	virtual void execute() = 0;
};

class AssignStmt : public Stmt{
private:
	string var;
	Expr* p_expr;
public:
	AssignStmt();
	~AssignStmt();
	string toString();
	void execute();
};

class InputStmt : public Stmt{
private:
	string var;
public:
	InputStmt();
	~InputStmt();
	string toString();
	void execute();
};

class StrOutStmt : public Stmt{
private:
	string value;
public:
	StrOutStmt();
	~StrOutStmt();
	string toString();
	void execute();
};

class IntOutStmt : public Stmt{
private:
	int value;
public:
	IntOutStmt();
	~IntOutStmt();
	string toString();
	void execute();
};

class IDOutStmt : public Stmt{
private:
	string var;
public:
	IDOutStmt();
	~IDOutStmt();
	string toString();
	void execute();
};

class IfStmt : public Stmt{
private:
	Expr* p_expr;
	int elsetarget;
public:
	IfStmt();
	~IfStmt();
	string toString();
	void execute();
};

class WhileStmt : public Stmt{
private:
	Expr* p_expr;
	int elsetarget;
public:
	WhileStmt();
	~WhileStmt();
	string toString();
	void execute();
};

class GoToStmt : public Stmt{
private:
	int target;
public:
	GoToStmt();
	~GoToStmt();
	void setTarget();
	string toString();
	void execute();
};

class Compiler{
private:
	//Added funcs
	//checks tok and calls correct build statement

	//DONE I think
	void buildStmt() {
		if (*tokitr == "t_if") {
			buildIf();
		}
		else if (*tokitr == "t_while") {
			buildWhile();
		}
		//Might need to check if correct
		else if (*tokitr == "t_id") {
			buildAssign();
		}
		else if (*tokitr == "t_input") {
			buildInput();
		}
		else if (*tokitr == "t_output") {
			buildOutput();
		}

	}
	//if(..) then ... end if ...
	// if(x > 0)
	//?- can there be multiple elses?
	//?- what is gotos role in if statement.
	void buildIf() {

	}
	//
	void buildWhile() {
		tokitr++; lexitr++;//pass while
		tokitr++; lexitr++;//pass left paren
		Expr* expr = buildExpr();
		tokitr++; lexitr++;//pass right paren
		tokitr++; lexitr++;//pass loop
		while (*tokitr != "t_loop") {
			buildStmt();
		}
		if (*tokitr == "t_end") {

		}



	}



	//DONE
	void buildAssign() {
		string id = *lexitr;
		tokitr++; lexitr++; // move past id
		tokitr++; lexitr++; // move past =
		Expr* expr = buildExpr();
		AssignStmt* asstmt = new AssignStmt();
		insttable.push_back(asstmt);
		tokitr++; lexitr++; //TODO SEE IF buildExpr() knocks it up one or not
	}

	//Done
	void buildInput() {
		tokitr++; lexitr++; // move past input
		tokitr++; lexitr++; // move past left paren
		InputStmt* input = new InputStmt(*lexitr); // create input stmt
		insttable.push_back(input);  // add to insttable table
		tokitr++; lexitr++; // move past id
		tokitr++; lexitr++; //move past right paren
	}

	//DONE
	void buildOutput() {
		tokitr++; lexitr++; // move past output
		tokitr++; lexitr++; // move past left paren
		if(*tokitr == "t_string") {
			StrOutStmt* output = new StrOutStmt(*lexitr);
			insttable.push_back(output);
		}
		else if(*tokitr == "t_integer") {
			IntOutStmt* output = new IntOutStmt(*lexitr);
			insttable.push_back(output);
		}
		else if(*tokitr == "t_id") {
			IDOutStmt* output = new IDOutStmt(*lexitr);
			insttable.push_back(output);
		}
		tokitr++; lexitr++;//past out
		tokitr++; lexitr++;//past right paren
	}
	Expr* buildExpr();

	// headers for populate methods may not change
	void populateTokenLexemes(istream& infile);
	void populateSymbolTable(istream& infile);
public:
	Compiler(){}
	// headers may not change
	Compiler(istream& source, istream& symbols){
		// build precMap - include logical, relational, arithmetic operators

		populateTokenLexemes(source);
		populateSymbolTable(symbols);
	}

	// The compile method is responsible for getting the instruction
	// table built.  It will call the appropriate build methods.
	bool compile() {
	}

	// The run method will execute the code in the instruction
	// table.
	void run(){}
};


int main(){
	ifstream source("data.txt");
	ifstream symbols("vars.txt");
	if (!source || !symbols) exit(-1);
	Compiler c(source, symbols);
	c.compile();
	// might want to call dump to check if everything built correctly
	// dump();
	c.run();
	return 0;
}