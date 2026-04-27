#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <string>
using namespace std;

// GROUP:
// ANDRE, AIDAN, JOSEPH, DAVID

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

class Expr{
public:
	virtual string toString() = 0;
	virtual ~Expr(){}
};

class StringExpr : public Expr{
public:
    virtual string eval() = 0; // pure virtual method which is an abstract class
};

class IntExpr : public Expr{
public:
    virtual int eval() = 0; // pure virtual method which is an abstract class
};

class StringConstExpr : public StringExpr{
private:
    string value;
public:
    StringConstExpr(string val) {
	    value = val;
    }
    ~StringConstExpr() {
	    // leave blank
    }
    string eval() {
	    return value;
    }
    string toString() {
	    return value;
    }
};

class StringIDExpr : public StringExpr{
private:
    string id;
public:
    StringIDExpr(string val) {
	    id = val;
    }
    ~StringIDExpr() {

    }
    string eval() {
		return symbolvalues[id];
    }
    string toString() {
		return id;
    }
};

class StringPostFixExpr : public StringExpr{
private:
    vector<string> expr;
    vector<string> exprtoks;
public:
    StringPostFixExpr(){}
    StringPostFixExpr(vector<string> x) {
		for (int i = 0; i < x.size(); i++) {
			expr.push_back(x[i]);
		}
    }
    ~StringPostFixExpr() { // since we're using pointers, need to clear it so no dangling memory.
	    expr.clear();
    }
	string eval() {
    	vector<string> tempStringStack;

    	for (const string& token : expr) {
    		if (token == "+" || token == "==" || token == "!=" || token == "<" || token == ">" || token == "<=" || token == ">=" || token == "and" || token == "or") {
    			string b = tempStringStack.back();
    			tempStringStack.pop_back();
    			string a = tempStringStack.back();
    			tempStringStack.pop_back();
    			if (token == "+") {
                    tempStringStack.push_back(a + b);
                }
                else if (token == "==") {
                    if (a == b) {
                        tempStringStack.push_back("true");
                    }
                    else {
                        tempStringStack.push_back("false");
                    }
                }
                else if (token == "!=") {
                    if (a != b) {
                        tempStringStack.push_back("true");
                    }
                    else {
                        tempStringStack.push_back("false");
                    }
                }
                else if (token == "<") {
                    if (a < b) {
                        tempStringStack.push_back("true");
                    }
                    else {
                        tempStringStack.push_back("false");
                    }
                }
                else if (token == ">") {
                    if (a > b) {
                        tempStringStack.push_back("true");
                    }
                    else {
                        tempStringStack.push_back("false");
                    }
                }
                else if (token == "<=") {
                    if (a <= b) {
                        tempStringStack.push_back("true");
                    }
                    else {
                        tempStringStack.push_back("false");
                    }
                }
                else if (token == ">=") {
                    if (a >= b) {
                        tempStringStack.push_back("true");
                    }
                    else {
                        tempStringStack.push_back("false");
                    }
                }
                else if (token == "and") {
                    if (a == "true" && b == "true") {
                        tempStringStack.push_back("true");
                    }
                    else {
                        tempStringStack.push_back("false");
                    }
                }
                else if (token == "or") {
                    if (a == "true" || b == "true") {
                        tempStringStack.push_back("true");
                    }
                    else {
                        tempStringStack.push_back("false");
                    }
                }
            }
            else {
                if (symbolvalues.find(token) != symbolvalues.end()) {
                    tempStringStack.push_back(symbolvalues[token]);
                }
                else {
                    tempStringStack.push_back(token);
                }
            }
    	}
    	if (!tempStringStack.empty()) {
    		return tempStringStack.back();
    	}
    	return "";
    }
	string toString() {
	    string result = "";
    	for (int i = 0; i < expr.size(); ++i) {
    		result += expr[i];
    	}
    	return result;
    }
};

class IntConstExpr : public IntExpr{
private:
    int value;
public:
    IntConstExpr(int val) {
    	value = val;
    }
    ~IntConstExpr() {
    	// leave blank
    }
    int eval() {
	    return value;
    }
    string toString() {
		return to_string(value);
    }
};

class IntIDExpr : public IntExpr{
private:
    string id;
public:
    IntIDExpr(string val) {
		id = val;
    }
    ~IntIDExpr() {
	    // leave blank
    }
    int eval() {
		return stoi(symbolvalues[id]);
    }
    string toString() {
		return id;
    }
};

class IntPostFixExpr : public IntExpr{ // evaluates the post fix form
private:
    vector<string> expr;
	int applyOperator(int a, int b, string oper) {
		if (oper == "+") {
			return a + b;
		}
		else if (oper == "-") {
			return a - b;
		}
		else if (oper == "*") {
			return a * b;
		}
		else if (oper == "/") {
			return a / b; // int division!
		}
		else if (oper == "and") {
			return a && b;
		}
		else if (oper == "%") {
			return a % b;
		}
		else if (oper == "or") {
			return a || b;
		}
		else if (oper == "<") {
			return a < b;
		}
		else if (oper == ">") {
			return a > b;
		}
		else if (oper == "<=") {
			return a <= b;
		}
		else if (oper == ">=") {
			return a >= b;
		}
		else if (oper == "==") {
			return a == b;
		}
		else if (oper == "!=") {
			return a != b;
		}
		return 0;
	}
public:
    IntPostFixExpr() {
    }
    IntPostFixExpr(vector<string> x) {
	    for (int i = 0; i < x.size(); i++) {
		    expr.push_back(x[i]);
	    }
    }
    ~IntPostFixExpr(){}
    int eval() {
	    vector<int> tempNumHolder; // create the stack use the import statement!!
    	int result = 0;
    	for (const string& token : expr) {
    		if (isdigit(token[0])) {
    			tempNumHolder.push_back(stoi(token));
    		}
    		else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "and" || token == "or" || token == "<" || token == ">" || token == "<=" || token == ">=" || token == "==" || token == "!=") {
				int b = tempNumHolder.back(); // becomes the right hand side of operand
    			tempNumHolder.pop_back();
    			int a = tempNumHolder.back();
    			tempNumHolder.pop_back();
				tempNumHolder.push_back(applyOperator(a, b, token));
    		}
    		else {
    			tempNumHolder.push_back(stoi(symbolvalues[token]));
    		}
    	}
    	return tempNumHolder.back();
    }
	string toString() {
	    string result = "";
    	for (int i = 0; i < expr.size(); ++i) {
    		result += expr[i];
    	}
    	return result;
    }
};

class Stmt // statements are executed!
{
    private:
        string name;
    public:
        Stmt(string n)
        {
            name = n;
        }
        virtual ~Stmt(){}
        virtual string toString() = 0;
        virtual void execute() = 0;
};

class AssignStmt : public Stmt
{
    private:
        string var;
        Expr* p_expr;
    public:
        AssignStmt(string v, Expr*& p) : Stmt("AssignStmt")
        {
            var = v;
            p_expr = p;
        }
        ~AssignStmt(){}
        string toString()
        {
            return "AssignStmt " + var + " " + (*p_expr).toString();
        }
        void execute()
        {
            if (symboltable[var] == "t_integer")
            {
                symbolvalues[var] = to_string(dynamic_cast<IntExpr*>(p_expr)->eval());
            }
            else
            {
                symbolvalues[var] = (*dynamic_cast<StringExpr*>(p_expr)).eval();
            }
            pc++;
        }
};

class InputStmt : public Stmt
{
    private:
        string var;
    public:
        InputStmt(string v) : Stmt("InputStmt")
        {
            var = v;
        }
        ~InputStmt(){}
        string toString()
        {
            return "InputStmt " + var;
        }
        void execute()
        {
        	cout << "Input Value " + var + ": " << endl;
            cin >> symbolvalues[var];
            pc++;
        }
};

class StrOutStmt : public Stmt
{
    private:
        string value;
    public:
        StrOutStmt(string v) : Stmt("StrOutStmt")
        {
            value = v;
        }
        ~StrOutStmt(){}
        string toString()
        {
            return "StrOutStmt " + value;
        }
        void execute()
        {
            cout << value << endl;
            pc++;
        }
};

class IntOutStmt : public Stmt
{
    private:
        int value;
    public:
        IntOutStmt(int v) : Stmt("IntOutStmt")
        {
            value = v;
        }
        ~IntOutStmt(){}
        string toString()
        {
            return "IntOut " + to_string(value);
        }
        void execute()
        {
            cout << value << endl;
            pc++;
        }
};

class IDOutStmt : public Stmt
{
    private:
        string var;
    public:
        IDOutStmt(string v) : Stmt("IDOutStmt")
        {
            var = v;
        }
        ~IDOutStmt(){}
        string toString()
        {
            return "IDOutStmt " + var;
        }
        void execute()
        {
            cout << symbolvalues[var] << endl;
            pc++;
        }
};

class IfStmt : public Stmt
{
    private:
        Expr* p_expr;
        int elsetarget;
    public:
        IfStmt(Expr*& e, int t) : Stmt("IfStmt")
        {
            p_expr = e;
            elsetarget = t;
        }
        ~IfStmt(){}
        string toString()
        {
            return "IfStmt " + (*p_expr).toString() + " " + to_string(elsetarget);
        }
        void execute()
        {
            IntExpr* intExpr = dynamic_cast<IntExpr*>(p_expr);
            StringExpr* stringExpr = dynamic_cast<StringExpr*>(p_expr);

            if (intExpr != nullptr)
            {
                if (intExpr->eval() == 1)
                {
                    pc++;
                }
                else
                {
                    pc = elsetarget;
                }
            }
            else if (stringExpr != nullptr)
            {
                if (stringExpr->eval() == "true")
                {
                    pc++;
                }
                else
                {
                    pc = elsetarget;
                }
            }
            else
            {
                pc++;
            }
        }
        void setElsetarget(int val)
        {
            elsetarget = val;
        }
};

class WhileStmt : public Stmt
{
    private:
        Expr* p_expr;
        int elsetarget;
    public:
        WhileStmt(Expr*& e, int t) : Stmt("WhileStmt")
        {
            p_expr = e;
            elsetarget = t;
        }
        ~WhileStmt(){}
        string toString()
        {
            return "WhileStmt " + (*p_expr).toString() + " " + to_string(elsetarget);
        }
        void execute()
        {
            IntExpr* intExpr = dynamic_cast<IntExpr*>(p_expr);
            StringExpr* stringExpr = dynamic_cast<StringExpr*>(p_expr);

            if (intExpr != nullptr)
            {
                if (intExpr->eval() == 1)
                {
                    pc++;
                }
                else
                {
                    pc = elsetarget;
                }
            }
            else if (stringExpr != nullptr)
            {
                if (stringExpr->eval() == "true")
                {
                    pc++;
                }
                else
                {
                    pc = elsetarget;
                }
            }
            else
            {
                pc++;
            }
        }
        void setElsetarget(int val)
        {
            elsetarget = val;
        }
};

class GoToStmt : public Stmt
{
    private:
        int target;
    public:
        GoToStmt(int t) : Stmt("GoToStmt")
        {
            target = t;
        }
        ~GoToStmt(){}
        void setTarget(int t)
        {
            target = t;
        }
        string toString()
        {
            return "GoToStmt " + to_string(target);
        }
        void execute()
        {
            pc = target;
        }
};

class Compiler{
private:
	//Added funcs
	//checks tok and calls correct build statement
	void runThroughIf() {
		while (*tokitr != "t_else" && *tokitr != "t_end") {
			buildStmt();
		}
	}
	void buildStmt() {
		if (*tokitr == "t_if") {
			buildIf();
		}
		else if (*tokitr == "t_while") {
			buildWhile();
		}
		else if (*tokitr == "t_id") {
			buildAssign();
		}
		else if (*tokitr == "t_input") {
			buildInput();
		}
		else if (*tokitr == "t_output") {
			buildOutput();
		}
		else {
			cout << *lexitr << endl;
			lexitr++;
			cout << *lexitr << endl;
			cout << "ERROR IN buildstmt";
			exit(1);
		}

	}
	void buildIf() {
		bool end = false;
		bool elseTargetFound = false;
		tokitr++; lexitr++; //pass if
		tokitr++; lexitr++; //pass l paren

		Expr* expr = buildExpr();
		GoToStmt* goToStmt = new GoToStmt(0);

		IfStmt* ifStmt = new IfStmt(expr,0);
		insttable.push_back(ifStmt);

		tokitr++; lexitr++;//pass r paren
		tokitr++; lexitr++;//pass then

		while (!end) {
			runThroughIf();
			if (*tokitr == "t_else") {
				int elseTarget = insttable.size() + 1;
				elseTargetFound = true;
				ifStmt->setElsetarget(elseTarget);
				insttable.push_back(goToStmt);
				tokitr++; lexitr++; //move past else
			}
			else if (*tokitr == "t_end") {
				end = true;
			}
		}
		int endDex = insttable.size();
		goToStmt->setTarget(endDex);

		if (!elseTargetFound) {
			ifStmt->setElsetarget(endDex);
		}
		tokitr++; lexitr++;//pass end
		tokitr++; lexitr++;// pass if
	}

	//Done i think
	void buildWhile() {
		tokitr++; lexitr++;//pass while
		tokitr++; lexitr++;//left parent

		int start = insttable.size();
		GoToStmt* goToStmt = new GoToStmt(start);

		Expr* expr = buildExpr();
		WhileStmt* whileStmt = new WhileStmt(expr,0);
		insttable.push_back(whileStmt);

		tokitr++; lexitr++;//pass r parrent
		tokitr++; lexitr++;//pass loop

		while (*tokitr != "t_end") {
			buildStmt();
		}

		int endDex = insttable.size() + 1;
		whileStmt->setElsetarget(endDex);

		insttable.push_back(goToStmt);

		tokitr++; lexitr++;//end
		tokitr++; lexitr++;//loop
	}

	//DONE
	void buildAssign() {
		string id = *lexitr;
		tokitr++; lexitr++; // move past id
		tokitr++; lexitr++; // move past =
		Expr* expr = buildExpr();
		AssignStmt* asstmt = new AssignStmt(id, expr);
		insttable.push_back(asstmt);
		tokitr++; lexitr++; //pass semi
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
		if(*tokitr == "t_text") {
			StrOutStmt* output = new StrOutStmt(*lexitr);
			insttable.push_back(output);
		}
		else if(*tokitr == "t_number") {
			IntOutStmt* output = new IntOutStmt(stoi(*lexitr));
			insttable.push_back(output);
		}
		else if(*tokitr == "t_id") {
			IDOutStmt* output = new IDOutStmt(*lexitr);
			insttable.push_back(output);
		}
		tokitr++; lexitr++;//past out
		tokitr++; lexitr++;//past right paren
	}
	Expr* buildExpr() {
		vector<string> outputQueue;
		vector<string> stack; // hold operators
		bool hasInt = false;
		bool hasStr = false;
		auto peekTok = tokitr;
		auto peekLex = lexitr;
		++peekTok;
		++peekLex;
		string firstToken = *tokitr;
		string firstLexeme = *lexitr;

		if (firstToken == "t_text" && *peekTok == "s_rparen") { // handles if ("hello")
			string val = *lexitr;
			tokitr++; lexitr++;
			return new StringConstExpr(val);
		}
		if (firstToken == "t_number" && *peekTok == "s_rparen") { // handles if (12)
			string val = *lexitr;
			++tokitr; lexitr++;
			return new IntConstExpr(stoi(val));
		}
		if (firstToken == "t_id" && *peekTok == "s_rparen") { // handles if (x)
			string varName = *lexitr;
			++tokitr; lexitr++;
			if (symboltable.find(varName) != symboltable.end()) {
				if (symboltable[varName] == "t_string") {
					return new StringIDExpr(varName);
				} else {
					return new IntIDExpr(varName);
				}
			}
		}
		while (*tokitr != "s_rparen" && *tokitr != "s_semi") {
			string token = *tokitr;
			string lexeme = *lexitr;
			if (token == "t_number") {
				hasInt = true;
				outputQueue.push_back(lexeme);
			}
			else if (token == "t_text") {
				hasStr = true;
				outputQueue.push_back(lexeme);
			}
			else if (token == "t_id") {
				if (symboltable.find(lexeme) != symboltable.end()) {
					if (symboltable[lexeme] == "t_string") {
						hasStr = true;
					} else {
						hasInt = true;
					}
					outputQueue.push_back(lexeme);
				}
			}
			else if (token == "s_lparen") {
				stack.push_back(lexeme);
			}
			else if (precMap.find(lexeme) != precMap.end()) {
				while (!stack.empty() && precMap[stack.back()] >= precMap[lexeme]) {
					outputQueue.push_back(stack.back());
					stack.pop_back();
				}
				stack.push_back(lexeme);
			}
			++tokitr; ++lexitr;
		}
		while (!stack.empty()) {
			outputQueue.push_back(stack.back());
			stack.pop_back();
		}
		if (hasStr) {
			return new StringPostFixExpr(outputQueue);
		} else {
			return new IntPostFixExpr(outputQueue);
		}
		return nullptr;
	};

	void populateTokenLexemes(istream& infile) {
		string token;
		string lexeme;

		while (infile >> token) {
			if (token == "t_text") {
				getline(infile, lexeme); // grab rest of line
				if (!lexeme.empty() && lexeme[0] == ' ') {
					lexeme = lexeme.substr(1); // remove leading space
				}
			} else {
				infile >> lexeme;
			}

			tokens.push_back(token);
			lexemes.push_back(lexeme);
		}
	}
	void populateSymbolTable(istream& infile) {
		string variable;
		string dataType;
		while (infile >> dataType >> variable) {
			symboltable[variable] = dataType;
		}
	}
public:
	Compiler(){}
	Compiler(istream& source, istream& symbols){
		precMap["or"] = 5;
		precMap["and"] = 4;
		precMap["<"] = 3;
		precMap[">"] = 3;
		precMap["<="] = 3;
		precMap[">="] = 3;
		precMap["!="] = 3;
		precMap["=="] = 3;
		precMap["+"] = 2;
		precMap["-"] = 2;
		precMap["*"] = 1;
		precMap["/"] = 1;
		precMap["%"] = 1;
		populateTokenLexemes(source);
		populateSymbolTable(symbols);
	}

	bool compile() {
		tokitr = tokens.begin();
		lexitr = lexemes.begin();
		bool VDECdone = false;

		if (*tokitr == "t_var") {
			tokitr++; lexitr++; //pass var
			while (!VDECdone) {
				bool comma = true;
				if (*tokitr == "t_string") {
					while (comma) {
						tokitr++; lexitr++; //pass string/comma
						symbolvalues[*lexitr] = "";
						tokitr++; lexitr++;//pass 'x'
						if (*tokitr == "s_comma") {
							comma = true;
						}
						else {
							comma = false;
						}
					}
					tokitr++; lexitr++; // pass semi
				}
				else if (*tokitr == "t_integer") {
					bool comma = true;
					while (comma) {
						tokitr++; lexitr++; //pass string/comma
						symbolvalues[*lexitr] = "0";
						tokitr++; lexitr++;//pass 'x'
						if (*tokitr == "s_comma") {
							comma = true;
						}
						else {
							comma = false;
						}
					}
					tokitr++; lexitr++; // pass semi
				}
				else {
					VDECdone = true;
				}
			}
		}
		tokitr++; lexitr++; // moves past main
		while (*tokitr != "t_end") {
			buildStmt();
		}
		return true;
	}

	// The run method will execute the code in the instruction
	// table.
	void run() {
		pc = 0;

		while (pc < insttable.size()) {
			insttable[pc]->execute();
		}
	}
};


void dump() {
	// Prints vartable, instruction table, symboltable
	cout << "--------------------------" << endl;
	cout << "---DUMP METHOD CALLED, NOW PRINTING---" << endl;
	cout << "--------------------------" << endl;

	cout << "---PRINTING INSTRUCTION TABLE---" << endl;
	for ( int i = 0; i < insttable.size(); i++ ) {
		cout << "--------------------------" << endl;
		cout << "~Instruction~" << endl;
		if (insttable[i]) {
			cout << "Instruction #" << i << ":" << endl;
			cout << insttable[i]->toString() << endl;
		}
		else {
			cout << "Null Instruction" << endl;
		}
	}

	cout << "---PRINTING SYMBOL TABLE AND VALUES---" << endl;
	for ( map<string, string>::iterator itr = symboltable.begin(); itr != symboltable.end(); itr++ ) {

		string tempId = itr->first; // Extracts variable name -> tempId
		string dataType = itr->second; // Extracts variable type -> dataType

		cout << "--------------------------" << endl;
		if (dataType == "t_integer") {
			cout << "Integer " << tempId << " = " << symbolvalues[tempId] << endl;
		}
		else if (dataType == "t_string") {
			cout << "String " << tempId << " = " << symbolvalues[tempId] << endl;
		}
	}
}


int main() {
    ifstream source("../ValidTests/dataFiles/sourceOne.txt");
    ifstream symbols("../ValidTests/varFiles/symbolOne.txt");

    if (!source || !symbols) {
        cout << "FAILED: Could not open files." << endl;
        return 1;
    }

    tokens.clear();
    lexemes.clear();
    symbolvalues.clear();
    symboltable.clear();
    insttable.clear();
    pc = 0;

    Compiler c(source, symbols);

    if (c.compile()) {
        cout << "COMPILE PASSED" << endl;
        dump();
        cout << "---PROGRAM OUTPUT---" << endl;
        c.run();
        cout << "---RUN FINISHED---" << endl;
    }
    else {
        cout << "COMPILE FAILED" << endl;
    }

    return 0;
}