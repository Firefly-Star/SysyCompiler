### 目前可以识别的产生式:

    CompUnit      ::= FuncDef;

    Decl          ::= ConstDecl | VarDecl;
    ConstDecl     ::= "const" BType ConstDef {"," ConstDef} ";";
    BType         ::= "int";
    ConstDef      ::= IDENT "=" ConstInitVal;
    ConstInitVal  ::= ConstExp;
    VarDecl       ::= BType VarDef {"," VarDef} ";";
    VarDef        ::= IDENT | IDENT "=" InitVal;
    InitVal       ::= Exp;

    FuncDef       ::= FuncType IDENT "(" ")" Block;
    FuncType      ::= "int";

    Block         ::= "{" {BlockItem} "}";
    BlockItem     ::= Decl | Stmt;
    Stmt          ::= LVal "=" Exp ";"
                    | [Exp] ";"
                    | Block
                    | "if" "(" Exp ")" Stmt ["else" Stmt]
                    | "while" "(" Exp ")" Stmt
                    | "break" ";"
                    | "continue" ";"
                    | "return" [Exp] ";";

    Exp           ::= LOrExp;
    LVal          ::= IDENT;
    PrimaryExp    ::= "(" Exp ")" | LVal | Number;
    Number        ::= INT_CONST;
    UnaryExp      ::= PrimaryExp | UnaryOp UnaryExp;
    UnaryOp       ::= "+" | "-" | "!";
    MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
    AddExp        ::= MulExp | AddExp ("+" | "-") MulExp;
    RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
    EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp;
    LAndExp       ::= EqExp | LAndExp "&&" EqExp;
    LOrExp        ::= LAndExp | LOrExp "||" LAndExp;
    ConstExp      ::= Exp;